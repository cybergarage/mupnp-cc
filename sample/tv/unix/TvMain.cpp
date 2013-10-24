/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: TvMain.cpp
*
*	Revision;
*
*	09/18/03
*		- first revision
*	05/21/04
*		- Added support for MinGW using TimeUtil::Wait.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "TvDevice.h"
#include <cybergarage/util/TimeUtil.h>

#include <string>
#include <iostream>

#if defined(HAVE_GTK)
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <gdk_imlib.h>
#include <X11/Xlib.h>
#else
#include <ctype.h>
#include "InputUtil.h"
#endif

using namespace std;
using namespace CyberLink;
using namespace CyberUtil;

char tvImgFileName[] = "images/tv.jpg";
char tvOnImgFileName[] = "images/tvon.jpg";
char szTitle[] = "CyberLink TV Device";

TVDevice *tvDev;

////////////////////////////////////////////////////////// 
//  InitApp
////////////////////////////////////////////////////////// 

void InitApp()
{
	tvDev = new TVDevice();
	tvDev->start();
}

void ExitApp()
{
	tvDev->stop();
	delete tvDev;
}

/////////////////////////////////////////////////////////////////////////////////
//
// for Gtk
//
/////////////////////////////////////////////////////////////////////////////////

#if defined(HAVE_GTK)

GtkWidget *window;
GtkWidget *drawingArea;

GdkImlibImage *tvIm = (GdkImlibImage *)NULL;
GdkPixmap *tvPixmap = (GdkPixmap *)NULL;

GdkImlibImage *tvOnIm = (GdkImlibImage *)NULL;
GdkPixmap *tvOnPixmap = (GdkPixmap *)NULL;

GdkPixmap *dispPixmap = (GdkPixmap *)NULL;

GdkFont *font20;

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
	
	if (tvPixmap == NULL) {
		gdk_imlib_render(tvIm, w, h);
		tvPixmap = gdk_imlib_move_image(tvIm);
	}
	
	if (tvOnPixmap == NULL) {
		gdk_imlib_render(tvOnIm, tvOnIm->rgb_width, tvOnIm->rgb_height);
		tvOnPixmap = gdk_imlib_move_image(tvOnIm);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// expose
/////////////////////////////////////////////////////////////////////////////////

gint expose(GtkWidget *widget, GdkEventExpose *event)
{
	GdkGC *gc = widget->style->fg_gc[GTK_WIDGET_STATE(widget)];

	gdk_draw_pixmap(
		dispPixmap,
		gc,
		tvPixmap,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);

	gdk_draw_pixmap(
		dispPixmap,
		gc,
		tvOnPixmap,
		0, 0,
		20, 20,
		tvOnIm->rgb_width, tvOnIm->rgb_height);
	
	GdkDrawable *drawable = drawingArea->window;
  	GdkColor white = {0,0xffff,0xffff,0xffff};
	GdkGC *whitegc = gdk_gc_new(drawable);
	GdkColormap *cmap=gdk_colormap_get_system();
	gdk_color_alloc(cmap,&white);
  	gdk_gc_set_foreground(whitegc, &white);
    		
	std::string clockStr = tvDev->getClockTime();
	if (0 < clockStr.size())
		gdk_draw_string(dispPixmap, font20, whitegc, 20, 30, clockStr.c_str());
	
	gdk_gc_unref(whitegc);

	gdk_draw_pixmap(
		widget->window,
		gc,
		dispPixmap,
		event->area.x, event->area.y,
		event->area.x, event->area.y,
		event->area.width, event->area.height);
		
	return TRUE;
}

gint TvUpdate(GtkWidget *widget)
{
	GdkEventExpose e;
	
	e.type = GDK_EXPOSE;
	e.window = widget->window;
	e.area.x = 0;
	e.area.y = 0;
	e.area.width = widget->allocation.width;
	e.area.height = widget->allocation.height;
	e.send_event = 0;
	e.count = 0;
	
	tvDev->update();
	
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
	
	tvIm = gdk_imlib_load_image(tvImgFileName);
	tvOnIm = gdk_imlib_load_image(tvOnImgFileName);
	
	char **fontNames;
	int nFonts;
	fontNames = XListFonts(GDK_DISPLAY(), "*courier-bold-r-*-*-*14-*", 300, &nFonts);
	if (0<nFonts)
		font20 = gdk_fontset_load(fontNames[0]);
	XFreeFontNames(fontNames);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
	drawingArea = gtk_drawing_area_new();
	gtk_drawing_area_size(GTK_DRAWING_AREA(drawingArea), tvIm->rgb_width, tvIm->rgb_height);
	gtk_container_add (GTK_CONTAINER (window), drawingArea);

	gtk_signal_connect (GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (destroy), NULL);
	gtk_signal_connect (GTK_OBJECT (drawingArea), "expose_event", GTK_SIGNAL_FUNC (expose), NULL);
	gtk_signal_connect (GTK_OBJECT (drawingArea), "configure_event", GTK_SIGNAL_FUNC (configure), NULL);
	gtk_timeout_add(1000, (GtkFunction)TvUpdate, (gpointer)drawingArea);
	
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

int main(int argc, char *argv[])
{
	kbinit();
	
	InitApp();

	int ch = 0;
	do
	{
		if (0 < kbhit()) {
			ch = getchar();
			ch = toupper( ch );
		}
		else
			Wait(1000);
		
		std::string clockStr = tvDev->getClockTime();
		if (0 < clockStr.length())
			cout << clockStr << endl;
		
	} while( ch != 'Q');

	ExitApp();
	
	kbexit();
	
	return(0);
}

#endif    
