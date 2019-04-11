/* A lot of this code is taken from examples provided in the Graphics, Animation and Sound course */
#include <Windows.h>
#include "Graphics.h"
#include "Level0.h"
#include "Level1.h"
#include "GameController.h"
#include "KeyboardInput.h"


Graphics* graphics;
KeyboardInput* keyboardInput;

/*
	This is a function that processes messages sent to a window.
*/
LRESULT CALLBACK WindowProc(
	HWND hwnd,		// handle to the window
	UINT uMsg,		// the message
	WPARAM wParam,	// additional message information, depends on uMsg
	LPARAM lParam)	// additional message information, depends on uMsg
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }

	/* The following calls the default window procedure to provide default processing */
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


/*
	This is the entry point for the program.
*/
int WINAPI wWinMain(
	HINSTANCE hInstance,	// handle to an instance for windows procedure
	HINSTANCE prevInstance,	// always zero
	LPWSTR cmd,				// contains the cmd line arguments as a Unicode string
	int nCmdShow			// flag that says whether the application window will be minimized, maximized or shown normally
)
{
	/* Set up WindowClass, contains windows class information */
	WNDCLASSEX windowclass;		
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));		// fill with zeroes
	windowclass.cbSize = sizeof(WNDCLASSEX);			// size of structure of WNDCLASSEX
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;	// handle to class background brush, can be handle or colour value
	windowclass.hInstance = hInstance;					// handle to instance that contains the window procedure
	windowclass.lpfnWndProc = WindowProc;				// pointer to window procedure, must be a function
	windowclass.lpszClassName = "MainWindow";			
	windowclass.style = CS_HREDRAW | CS_VREDRAW;	// redraws the entire window if a movement or size adjustment changes
													// the width or height of the client area

	RegisterClassEx(&windowclass);	// registers the window class for subsequent use with CreateWindow

	
	RECT rect = { 0, 0, GameLevel::WIN_WIDTH, GameLevel::WIN_HEIGHT };	// rectangle structure, define upper left and lower right corners
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);	// calculates size of window rectangle

	/* Create a window, using the dimensions in rect, with window name 'Set Hunter A1'. Have to still call */
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "Set Hunter A1", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle) return -1;

	/* Create a new Graphics object and create and initialize the render target for rendering to the window */
	graphics = new Graphics();
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	/* Create a DirectInput object for creating keyboard and mouse devices */
	LPDIRECTINPUT8 m_diObject;
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&m_diObject, NULL);

	/* Create the keyboard and mouse device objects */
	keyboardInput = new KeyboardInput(windowhandle, m_diObject);

	GameLevel::Init(graphics, keyboardInput);
	ShowWindow(windowhandle, nCmdShow);
	//GameController::LoadInitialLevel(new Level1());
	GameController::LoadInitialLevel(new Level0());

#pragma region GameLoop
	//Below, we have essentially an infinite loop that will keep the window running and will dispatch/show messages
	//As many people will tell you, most Windows you see are just infinite loops waiting for some kind of work-flow or 
	//system-based interuption.

	//Note - Our message handling has changed from the first demo code.
	//Here, we use a PeekMessage to avoid locking the graphics/windoProc
	//when a message has to be dispatched.
	MSG message;
	message.message = WM_NULL; //Do not have this set to WM_QUIT, which has a specific context
	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			//This allows us to send a message to the WindowProc IF there is one
			DispatchMessage(&message);
		else
		{
			if (GameController::currentLevel->switchLevel)
			{
				if (GameController::currentLevel->nextLevel == 1)
				{
					GameController::SwitchLevel(new Level1());
				}
			}
			//Update Routine... we've moved the code for handling updates to GameController
			GameController::Update();

			//Render Routine... This is very modular. GameController now handles the rendering
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();

		}
	}

#pragma endregion
	delete graphics;
	return 0;
}