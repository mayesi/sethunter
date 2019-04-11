#pragma once
#include "GameLevel.h"
#include "GameController.h"
#include "SoundEvent.h"
#include "AudioComponent.h"

class Level0 : public GameLevel
{
private:
	SoundEvent* titleMusic;
	AudioComponent* audioComponent;
	const std::wstring musicFile = L"Car-Theft-101.wav";

	bool initialized = false;

public:
	void Load() override;	// Loads the sprites and sets up the initial state of the game.
	void Unload() override;	// Unloads resources
	void Update() override;	// Updates the state of game objects
	void Render() override;	// Renders the screen
	
	void DrawTitle();	// Draws the title onto the screen
	void DrawLoading();
};