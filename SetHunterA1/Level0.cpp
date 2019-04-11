#include "Level0.h"

void Level0::Load()
{
	// Set up the level
	switchLevel = false;
	nextLevel = 1;

	// Load music here
	audioComponent = new AudioComponent();
	titleMusic = new SoundEvent();

	bool result = audioComponent->LoadFile(musicFile, *titleMusic);
	if (result)
	{
		titleMusic->SetLoopForever();
		audioComponent->PlaySoundEvent(*titleMusic);
	}
}

void Level0::Unload()
{
	audioComponent->StopSoundEvent(*titleMusic);
}

void Level0::Update()
{
	// Check if the user has pressed the spacebar
	keyboard->GetDeviceState();
	PressedKeys keys = keyboard->GetKeys();
	if (keys.pressed_space || keys.pressed_down)
	{
		switchLevel = true;
	}
}

void Level0::Render()
{
	if (!initialized)
	{
		DrawTitle();
	}
	if (switchLevel)
	{
		gfx->ClearScreen(0, 0, 0);
		DrawLoading();
	}
}

void Level0::DrawTitle()
{
	// Retrieve the size of the render target.
	D2D1_SIZE_F renderTargetSize = gfx->GetRenderTarget()->GetSize();

	WCHAR titleText[256] = L"S.E.T HUNTER\n\nPress SPACEBAR";

	gfx->GetRenderTarget()->DrawText(
		titleText,
		wcslen(titleText),
		gfx->TextFormat(),
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		gfx->WhiteBrush()
	);

}

void Level0::DrawLoading()
{
	// Retrieve the size of the render target.
	D2D1_SIZE_F renderTargetSize = gfx->GetRenderTarget()->GetSize();

	WCHAR titleText[256] = L"LOADING";

	gfx->GetRenderTarget()->DrawText(
		titleText,
		wcslen(titleText),
		gfx->TextFormat(),
		D2D1::RectF(0, 0, renderTargetSize.width, renderTargetSize.height),
		gfx->WhiteBrush()
	);
}