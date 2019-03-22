// From http://keithditch.powweb.com/Games/html/directinput.html
// I could have used Windows messages instead, but I already coded this up so...
#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	// for handling keyboard and mouse input

class UserInput
{
protected:
	LPDIRECTINPUTDEVICE8 m_diDevice;	// A DirectInput device object for the keyboard or mouse
	bool acquired;	// If the device is acquired, it will be set to true
	void Acquire();	// We need to acquire the device before we can use it

public:	
	virtual bool GetDeviceState() = 0;	// Get data from the device, map to chars
};