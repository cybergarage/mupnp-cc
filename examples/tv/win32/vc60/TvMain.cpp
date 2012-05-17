/******************************************************************
*
*	CyberX3D for C++
*
*	Copyright (C) Satoshi Konno 1996-2003
*
*	File:	X3DBrowser.cpp
*
******************************************************************/
#include <winsock2.h>   
#include <windowsx.h>   
#include <commdlg.h>   

#include "TVDevice.h"

using namespace CyberLink;

static HINSTANCE gInstance;
static HBITMAP TVBitmap;
static HBITMAP TVOnBitmap;

const char panelFilename[] = "images/tv.bmp";
const char onImgFilename[] = "images/tvon.bmp";
const char szTitle[] = "CyberLink TV Device";

LONG WINAPI WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

TVDevice *TVDev;

////////////////////////////////////////////////////////// 
//  InitApp
////////////////////////////////////////////////////////// 

void InitApp()
{
	TVBitmap = (HBITMAP)LoadImage(gInstance, panelFilename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE); 
	TVOnBitmap = (HBITMAP)LoadImage(gInstance, onImgFilename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE); 

	TVDev = new TVDevice();
	TVDev->start();
}

void ExitApp()
{
	TVDev->stop();
	delete TVDev;
}

void CALLBACK TVUpdate(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	InvalidateRect(hWnd, NULL, FALSE);
}

////////////////////////////////////////////////////////// 
//  WinMain
////////////////////////////////////////////////////////// 

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{	
	static char szAppName[] = "CyberLink TV Device";
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
				360 + borderXSize*2, 
				230 + borderYSize *2 + GetSystemMetrics(SM_CYCAPTION),
				NULL,	 
				NULL,	 
				hInstance,
				NULL);

	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );		

	SetTimer(hWnd, 1, 1000, TVUpdate);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage( &msg ); 
		DispatchMessage( &msg );
		/*
		if (mouseButton != MOUSE_BUTTON_NONE)
			MoveViewpoint(hWnd, &sceneGraph, mxPos, myPos);
		sceneGraph.update();
		InvalidateRect(hWnd, NULL, NULL);
		UpdateWindow(hWnd);
		*/
	}

	return( msg.wParam ); 
}

////////////////////////////////////////////////////////// 
//  OnPaint
////////////////////////////////////////////////////////// 

void OnPaint(HWND hWnd) 
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd,&ps);

	int width = 360;
	int height = 230;

	HDC memDC = CreateCompatibleDC(hdc);
	HBITMAP memBitmap = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(memDC, memBitmap);

	HDC bitmapDC = CreateCompatibleDC(hdc);
	SelectObject(bitmapDC, TVBitmap);
	BitBlt(memDC, 0, 0, width, height, bitmapDC, 0, 0, SRCCOPY);
	DeleteDC(bitmapDC);

	HDC onBitmapDC = CreateCompatibleDC(hdc);
	SelectObject(onBitmapDC, TVOnBitmap);
	BitBlt(memDC, 20, 20, 320, 180, onBitmapDC, 0, 0, SRCCOPY);
	DeleteDC(onBitmapDC);

	SetBkMode(memDC,TRANSPARENT);
	SetTextColor(memDC,RGB(0xff, 0xff, 0xff));

	std::string clockStr = TVDev->getClockTime();

	HFONT hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Lucida Console");
	HFONT oldFont = (HFONT)SelectObject(memDC, hFont);
	TextOut(memDC, 20, 20, clockStr.c_str(), clockStr.length());
	SelectObject(memDC, oldFont);
	DeleteObject(hFont);

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
