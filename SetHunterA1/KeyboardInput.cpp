#include "KeyboardInput.h"

KeyboardInput::KeyboardInput(HWND hwnd, LPDIRECTINPUT8 m_diObject)
{
	// Set up the DirectInput keyboard device object
	HRESULT hr = m_diObject->CreateDevice(GUID_SysKeyboard, &m_diDevice, NULL);

	// Set up the keyboard device data format
	hr = m_diDevice->SetDataFormat(&c_dfDIKeyboard);

	// Set up the keyboard behaviour, use device when the window is active and have non-exclusive behaviour
	hr = m_diDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	// Set all the keys to not pressed
	pKeys = { false, false, false, false };
}

KeyboardInput::~KeyboardInput()
{
	if (m_diDevice)
	{
		m_diDevice->Unacquire();
		m_diDevice->Release();
	}
}


bool KeyboardInput::GetDeviceState()
{
	pKeys = { false, false, false, false, false }; // reset
	
	// Acquire the device, if failed return false
	Acquire();
	if (!acquired)
	{
		return false;
	}

	// get the input's device state, and put the state in keys - zero first
	ZeroMemory(keys, sizeof(keys));
	m_diDevice->GetDeviceState(sizeof(keys), keys);

	// We can 'AND' with 0x80 to find if the key was pressed. If it returns true, the key was pressed.
	// If it is 0 the key was not pressed.
	pKeys.pressed_left = (keys[DIK_A] & 0x80) > 0 || (keys[DIK_LEFTARROW] & 0x80) > 0;
	pKeys.pressed_up = (keys[DIK_W] & 0x80) > 0 || (keys[DIK_UPARROW] & 0x80) > 0;
	pKeys.pressed_down = (keys[DIK_S] & 0x80) > 0 || (keys[DIK_DOWNARROW] & 0x80) > 0;
	pKeys.pressed_right = (keys[DIK_D] & 0x80) > 0 || (keys[DIK_RIGHTARROW] & 0x80) > 0;
	pKeys.pressed_space = keys[DIK_SPACE];
	
	return true;
}

PressedKeys KeyboardInput::GetKeys()
{
	return pKeys;
}
