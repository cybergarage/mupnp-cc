/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: ClockMain.cpp
*
*	Revision;
*
*	09/18/03
*		- first revision
*	05/21/04
*		- Added support for MinGW using TimeUtil::Wait.
*	07/27/05
*		- Added support for T-Engine.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "ClockDevice.h"
#include <uhttp/util/TimeUtil.h>

#include <string>
#include <iostream>

#if defined(HAVE_GTK)
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <gdk_imlib.h>
#include <X11/Xlib.h>
#elif !defined(TENGINE)
#include <ctype.h>
#include "InputUtil.h"
#endif

#if defined(TENGINE)
#if defined(PROCESS_BASE) /* Process based */
#include <basic.h>
#define MBEG	int main( W ac, TC *av[] )
#define MEND	0
#define DIR	"/SYS/bin/"
#else /* T-Kernel based */
#include <basic.h>
#include <tk/tkernel.h>
#include <sys/pinfo.h>
#define MBEG	ER main( INT ac, UB *av[] )
#define MEND	E_SYS
#define DIR	"/SYS/bin/"
#endif
#endif

using namespace std;
using namespace CyberLink;
using namespace uHTTP;

char clockImgFileName[] = "images/clock.jpg";
char szTitle[] = "CyberLink Clock Device";

ClockDevice *clockDev;

////////////////////////////////////////////////////////// 
//  InitApp
////////////////////////////////////////////////////////// 

void InitApp()
{
	clockDev = new ClockDevice();
	clockDev->start();
}

void ExitApp()
{
	clockDev->stop();
	delete clockDev;
}

/////////////////////////////////////////////////////////////////////////////////
//
// for Gtk
//
/////////////////////////////////////////////////////////////////////////////////

#if defined(HAVE_GTK)

GtkWidget *window;
GtkWidget *drawingArea;

GdkImlibImage *clockIm = (GdkImlibImage *)NULL;
GdkPixmap *clockPixmap = (GdkPixmap *)NULL;
GdkPixmap *dispPixmap = (GdkPixmap *)NULL;

GdkFont *font10;
GdkFont *font20;
GdkFont *font60;

/////////////////////////////////////////////////////////////////////////////////
// configure
/////////////////////////////////////////////////////////////////////////////////

gint configure(GtkWidget *widget, GdkEventConfigure *event)
{
	gint w, h;
	w = widget->allocation.width;
	h = widget->allocation.height;
	
	if (dispPixmap)
		gdk_pixmap_unref(dispPixmap);
	dispPixmap = gdk_pixmap_new(widget->window, w, h, -1);
	
	if (clockPixmap == NULL) {
		gdk_imlib_render(clockIm, w, h);
		clockPixmap = gdk_imlib_move_image(clockIm);
	}	
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// expose
/////////////////////////////////////////////////////////////////////////////////

gint expose(GtkWidget *widget, GdkEventExpose *event)
{
	Clock clock;
	std::string dateStr;
	std::string timeStr;
	clock.getDateString(dateStr);
	clock.getTimeString(timeStr);
		
	GdkGC *gc = widget->style->fg_gc[GTK_WIDGET_STATE(widget)];
	
	gdk_draw_pixmap(
		dispPixmap,
		gc,
		clockPixmap,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);
	
	//// Date String ////
	
	gdk_draw_string(dispPixmap, font20, gc, 45, 60, dateStr.c_str());
	
	//// Time String ////
	
	int timeStrX = 60;
	int timeStrY = 80;
	int timeStrWidth = 180;
	int timeStrOffset = 55;
	gdk_draw_string(dispPixmap, font60, gc, 100, 110, timeStr.c_str());

	//// Sec String ////

	int DEFAULT_SECOND_BLOCK_HEIGHT = 8;
	int sec = clock.getSecond();
	int secBarBlockSize = timeStrWidth / 60;
	int secBarBlockY = timeStrY + timeStrOffset;
	for (int n=0; n<sec; n++) {
		int x = timeStrX + (secBarBlockSize*n);
		gdk_draw_rectangle(dispPixmap, gc, TRUE, x, secBarBlockY, (secBarBlockSize - 1), DEFAULT_SECOND_BLOCK_HEIGHT);
	}

	if (sec != 0 && (sec % 10) == 0) {
		int x = timeStrX + (secBarBlockSize*sec);
		char secStr[8];
		sprintf(secStr, "%02d", sec);
		gdk_draw_string(dispPixmap, font10, gc, x + secBarBlockSize, secBarBlockY, secStr);
	}
		
	gdk_draw_pixmap(
		widget->window,
		gc,
		dispPixmap,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);
		
	return TRUE;
}

gint ClockUpdate(GtkWidget *widget)
{
	clockDev->update();
	
	GdkEventExpose e;
	
	e.type = GDK_EXPOSE;
	e.window = widget->window;
	e.area.x = 0;
	e.area.y = 0;
	e.area.width = widget->allocation.width;
	e.area.height = widget->allocation.height;
	e.send_event = 0;
	e.count = 0;
	
	configure(widget, NULL);
	expose(widget, &e);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// destroy
/////////////////////////////////////////////////////////////////////////////////

void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

/////////////////////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	gdk_imlib_init ();
	
	clockIm = gdk_imlib_load_image(clockImgFileName);
	
	char **fontNames;
	int nFonts;
	fontNames = XListFonts(GDK_DISPLAY(), "*courier-bold-r-*-*-*10-*", 300, &nFonts);
	if (0<nFonts)
		font10 = gdk_fontset_load(fontNames[0]);
	XFreeFontNames(fontNames);
	fontNames = XListFonts(GDK_DISPLAY(), "*courier-bold-r-*-*-*18-*", 300, &nFonts);
	if (0<nFonts)
		font20 = gdk_fontset_load(fontNames[0]);
	XFreeFontNames(fontNames);
	fontNames = XListFonts(GDK_DISPLAY(), "*courier-bold-r-*-*-*34-*", 300, &nFonts);
	if (0<nFonts)
		font60 = gdk_font_load(fontNames[0]);
	XFreeFontNames(fontNames);
	
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
	drawingArea = gtk_drawing_area_new();
	gtk_drawing_area_size(GTK_DRAWING_AREA(drawingArea), clockIm->rgb_width, clockIm->rgb_height);
	gtk_container_add (GTK_CONTAINER (window), drawingArea);

	gtk_signal_connect (GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
	gtk_signal_connect (GTK_OBJECT (drawingArea), "expose_event", GTK_SIGNAL_FUNC (expose), NULL);
	gtk_signal_connect (GTK_OBJECT (drawingArea), "configure_event", GTK_SIGNAL_FUNC (configure), NULL);
	gtk_timeout_add(1000, (GtkFunction)ClockUpdate, (gpointer)drawingArea);
	
	gtk_widget_set_events(drawingArea, GDK_EXPOSURE_MASK);

	
	InitApp();
								    
	gtk_widget_show_all(window);
    
	gtk_main ();
	
	ExitApp();
	
	return(0);
}

#else

/////////////////////////////////////////////////////////////////////////////////
//
// for command line
//
/////////////////////////////////////////////////////////////////////////////////

#if defined(TENGINE)
MBEG
#else
int main( int argc, char* argv[] )
#endif
{
#if !defined(TENGINE)
	kbinit();
#endif
	
	InitApp();

	int ch = 0;
	do
	{
#if !defined(TENGINE)
		if (0 < kbhit()) {
			ch = getchar();
			ch = toupper( ch );
		}
		else
			Wait(1000);
#else
		Wait(1000);
#endif
		
		clockDev->update();
		
		Clock clock;
		std::string clockStr;
		clock.toString(clockStr);

		cout << clockStr << endl;
	} while( ch != 'Q');

	ExitApp();
	
#if !defined(TENGINE)
	kbexit();
#endif
	
	return(0);
}

#endif    

