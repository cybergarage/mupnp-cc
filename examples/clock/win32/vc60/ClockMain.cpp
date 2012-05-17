/******************************************************************
*
*	CyberX3D for C++
*
*	Copyright (C) Satoshi Konno 1996-2003
*
*	File:	ClockMain.cpp
*
******************************************************************/
#include <winsock2.h>   
#include <windowsx.h>   
#include <commdlg.h>   
#include "resource.h"

#include "ClockDevice.h"

using namespace CyberLink;

static HINSTANCE gInstance;
static HBITMAP clockBitmap;

const char panelFilename[] = "images/clock.bmp";
const char szTitle[] = "CyberLink Clock Device";

LONG WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

ClockDevice *clockDev;

////////////////////////////////////////////////////////// 
//  InitApp
////////////////////////////////////////////////////////// 

void InitApp()
{
	clockBitmap = (HBITMAP)LoadImage(gInstance, panelFilename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE); 

	clockDev = new ClockDevice();
	clockDev->start();
}

void ExitApp()
{
	clockDev->stop();
	delete clockDev;
}

void CALLBACK ClockUpdate(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	clockDev->update();
	InvalidateRect(hWnd, NULL, FALSE);
}

////////////////////////////////////////////////////////// 
//  WinMain
////////////////////////////////////////////////////////// 

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	static char szAppName[] = "CyberLink Clock Device";
	WNDCLASS	wc;
	MSG			msg; 
	HWND		hWnd;

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC)WndProc;	  
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= NULL;  
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName		= ""/*MAKEINTRESOURCE(IDR_MENU)*/;  
	wc.lpszClassName	= szAppName; 

	RegisterClass( &wc );
  
	gInstance = hInstance;

	int borderXSize = GetSystemMetrics(SM_CXFIXEDFRAME);
	int borderYSize = GetSystemMetrics(SM_CXFIXEDFRAME);

	hWnd = CreateWindow(
				szAppName,
				szTitle,
				//WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
				CW_USEDEFAULT, CW_USEDEFAULT, 
				300 + borderXSize*2, 
				200 + borderYSize *2 + GetSystemMetrics(SM_CYCAPTION),
				NULL,	 
				NULL,	 
				hInstance,
				NULL);

	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );		

	SetTimer(hWnd, 1, 1000, ClockUpdate);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage( &msg ); 
		DispatchMessage( &msg );
	}

	return( msg.wParam ); 
}

////////////////////////////////////////////////////////// 
//  OnPaint
////////////////////////////////////////////////////////// 

void OnPaint(HWND hWnd) 
{
	Clock clock;
	std::string dateStr;
	std::string timeStr;
	clock.getDateString(dateStr);
	clock.getTimeString(timeStr);
	
	int width = 300;
	int height = 200;

	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd,&ps);

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(memDC, memBitmap);

	HDC bitmapDC = CreateCompatibleDC(hdc);
	SelectObject(bitmapDC, clockBitmap);
	BitBlt(memDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
	DeleteDC(bitmapDC);

	SetBkMode(memDC,TRANSPARENT);
	SetTextColor(memDC,RGB(0, 0, 0));

	//// Date String ////

	HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Lucida Console");
	HFONT oldFont = (HFONT)SelectObject(memDC, hFont);
	TextOut(memDC, 45, 45, dateStr.c_str(), dateStr.length());
	SelectObject(memDC, oldFont);
	DeleteObject(hFont);

	//// Time String ////
	
	hFont = CreateFont(60, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Lucida Console");
	oldFont = (HFONT)SelectObject(memDC, hFont);
	int timeStrX = 60;
	int timeStrY = 80;
	int timeStrWidth = 180;
	int timeStrOffset = 55;
	TextOut(memDC, timeStrX, timeStrY, timeStr.c_str(), timeStr.length());
	SelectObject(memDC, oldFont);
	DeleteObject(hFont);

	//// Second Bar ////
	
	int DEFAULT_SECOND_BLOCK_HEIGHT = 8;
	int sec = clock.getSecond();
	int secBarBlockSize = timeStrWidth / 60;
	int secBarBlockY = timeStrY + timeStrOffset;
	HBRUSH barBrush = CreateSolidBrush(RGB(0, 0, 0));
	for (int n=0; n<sec; n++) {
		int x = timeStrX + (secBarBlockSize*n);
		RECT rect;
		rect.left = x;
		rect.top = secBarBlockY;
		rect.right = x + (secBarBlockSize - 1);
		rect.bottom = secBarBlockY + DEFAULT_SECOND_BLOCK_HEIGHT;
		FillRect(memDC, &rect, barBrush);
	}
	DeleteObject(barBrush);

	if (sec != 0 && (sec % 10) == 0) {
		int x = timeStrX + (secBarBlockSize*sec);
		HFONT hFont = CreateFont(10, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Lucida Console");
		HFONT oldFont = (HFONT)SelectObject(memDC, hFont);
		char secStr[8];
		sprintf(secStr, "%02d", sec);
		TextOut(memDC, x + secBarBlockSize, secBarBlockY, secStr, strlen(secStr));
		SelectObject(memDC, oldFont);
		DeleteObject(hFont);
	}

	BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);

	DeleteDC(memDC);

	EndPaint(hWnd,&ps);
}

////////////////////////////////////////////////////////// 
//  WndProc
////////////////////////////////////////////////////////// 
 
LONG WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg){
	case WM_CREATE: 
		InitApp();
		return 0;

	case WM_SIZE:
	     return 0;

	case WM_PAINT:
		OnPaint(hWnd);
		return 0;

	case WM_ERASEBKGND:
		return 0;

	case WM_COMMAND:
		return 0;

	case WM_LBUTTONDOWN:
		return 0;

	case WM_LBUTTONUP:
		return 0;

	case WM_MOUSEMOVE:
		return 0;

	case WM_DESTROY:
		ExitApp();
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}
