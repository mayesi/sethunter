#pragma once
#include "UserInput.h"

typedef struct PressedKeys
{
	bool pressed_w;
	bool pressed_s;
	bool pressed_a;
	bool pressed_d;
} PressedKeys;

class KeyboardInput : public UserInput
{
private:
	BYTE keys[256];		// hold the state of the keyboard
	PressedKeys pKeys;	// holds which keys are pressed (wsad)

public:
	KeyboardInput(HWND hwnd, LPDIRECTINPUT8 m_diObject);	// constructor
	~KeyboardInput();	// destructor

	bool GetDeviceState();	// Get data from the device, map to chars
};