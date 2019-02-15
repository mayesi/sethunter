#pragma once

#include <wincodec.h> //This is the WIC codec header - we need this to decode image files
#include "Graphics.h" //This includes both Windows and D2D libraries
//Remember to add "windowscodecs.lib" to your Linker/Input/AdditionalDependencies

class SpriteSheet
{
	Graphics* gfx;		// Reference to the Graphics class
	ID2D1Bitmap* bmp;	// This will hold our loaded and converted Bitmap file

public:
	SpriteSheet(wchar_t* filename, Graphics* gfx);

	~SpriteSheet();	// Destructor

	void Draw();			// Draw bitmap to the render target
	void DrawChromakey(float x, float y);	// Draw bitmap to the render target with chromakey effect

};