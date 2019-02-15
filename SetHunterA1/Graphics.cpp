#include "Graphics.h"

/***********************************************************************************
The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible
for managing the rendertarget.
******************************************************************************************/


/*
	Method:			Graphics()
	Description:	Constructor for Graphics class
*/
Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
}


/*
	Method:			~Graphics()
	Description:	Destructor, all COM objects we instantiate are released
*/
Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (grayBrush) grayBrush->Release();
}


/*
	Method:			Init()
	Description:	Creates and initializes the render target for rendering to the window
	Parameters:
		HWND windowHandle - the HWND to which the render target issues the output from its drawing commands
	Return:
		bool - true: success, false: error
*/
bool Graphics::Init(HWND windowHandle)
{
	/* Create a factory object that can be used to create Direct2D objects */
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (result != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect); // set the rect's right and bottom properties = the client window's size

	/* Create and set up the render target for rendering to the window */
	result = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget);
	if (result != S_OK) return false;

	/* Set up the gray brush */
	result = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f), &grayBrush);
	if (result != S_OK) return false;

	return true;
}


/* 
	Method:		ClearScreen()
	Description:	Clears the drawing area to a specified colour. Uses the D2D1::ColorF class to define the colour.
	Parameters:
		float r - red value
		float g - green value
		float b - blue value
*/
void Graphics::ClearScreen(float r, float g, float b)
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}

ID2D1SolidColorBrush* Graphics::GrayBrush()
{
	return grayBrush;
}

