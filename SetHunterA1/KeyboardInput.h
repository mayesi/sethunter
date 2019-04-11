#pragma once
#include "UserInput.h"

typedef struct PressedKeys
{
	bool pressed_up;
	bool pressed_down;
	bool pressed_left;
	bool pressed_right;
	bool pressed_space;
} PressedKeys;

class KeyboardInput : public UserInput
{
private:
	BYTE keys[256];		// hold the state of the keyboard
	PressedKeys pKeys;	// holds which keys are pressed (wsad,spacebar)

public:
	KeyboardInput(HWND hwnd, LPDIRECTINPUT8 m_diObject);	// constructor
	~KeyboardInput();	// destructor

	bool GetDeviceState();	// Get data from the device, map to chars
	PressedKeys GetKeys();
};