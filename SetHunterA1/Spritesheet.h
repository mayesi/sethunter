#pragma once

#include <wincodec.h> //This is the WIC codec header - we need this to decode image files
#include "Graphics.h" //This includes both Windows and D2D libraries
//Remember to add "windowscodecs.lib" to your Linker/Input/AdditionalDependencies

class SpriteSheet
{
	Graphics* gfx;		// Reference to the Graphics class
	ID2D1Bitmap* bmp;	// This will hold our loaded and converted Bitmap file
	ID2D1Effect* chromakeyEffect;	// the chromakey effect

public:
	SpriteSheet(wchar_t* filename, Graphics* gfx);

	~SpriteSheet();	// Destructor

	void AddChromakey();	// Uses default of blue, adds chromakey effect to the spritesheet
	void AddChromakey(float r, float g, float b);	// Adds a chromakey effect to the spritesheet
	
	void Draw();			// Draw bitmap to the render target
	void DrawChromakey(float x, float y);	// Draw bitmap to the render target with chromakey effect

};