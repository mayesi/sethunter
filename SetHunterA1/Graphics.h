#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "d2d1.lib")

#include <Windows.h>
#include <d2d1_1.h>
#include <d2d1.h>
#include <d3d11_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
#include <dwrite.h>

static const WCHAR msc_fontName[] = L"Verdana";
static const FLOAT msc_fontSize = 50;

/* This class handles rendering of the window graphics */
class Graphics
{
	/* Below, these are all COM interfaces we're using to create D2D resources.
	   We release them as part of the ~Graphics deconstructor... or bad things can happen */
	ID2D1Factory* factory;					// The factory allows us to create many other types of D2D resources
	ID2D1HwndRenderTarget* rendertarget;	// this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* grayBrush;		// a gray coloured brush
	ID2D1SolidColorBrush* whiteBrush;		// a white coloured brush
	IDWriteFactory* wfactory;				// This factory allows us to create text
	IDWriteTextFormat* textFormatCenter;	// Text format object, centered on the screen
	IDWriteTextFormat* textFormatUpperLeftCorner;	// Text format object, upper left corner

public:
	

	Graphics();		// Constructor

	~Graphics();	// Destructor

	bool Init(HWND windowHandle); 

	ID2D1RenderTarget* GetRenderTarget()
	{
		return rendertarget;
	}

	ID2D1DeviceContext* GetDeviceContext()
	{
		ID2D1DeviceContext *rtDC;
		rendertarget->QueryInterface(&rtDC);
		return rtDC;
	}

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);

	ID2D1SolidColorBrush* GrayBrush();
	ID2D1SolidColorBrush* WhiteBrush() { return whiteBrush; };
	IDWriteTextFormat* TextFormatCenter() { return textFormatCenter; };
	IDWriteTextFormat* TextFormatUpperLeftCorner() { return textFormatUpperLeftCorner; }

};