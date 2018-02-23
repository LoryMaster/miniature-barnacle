#include "tools\OpenGL\glCore.h"
#include "GameCode\mainGame.h"

#define PLATFORM_IMPLEMENTATION
#define I_WANT_GRAPHICS
#include "Platform\lsWindows.h"

#define LS_MATH_IMPLEMENTATION
#include "tools\Maths\Maths.h"

#define LS_CRT_IMPLEMENTATION
#include "tools\lsCRT.h"

internal VOID Win32_ProcessKeyboard(KeyboardManager *Keyboard, MSG Msg)
{
	switch (Msg.message)
	{
		case WM_KEYDOWN:
			switch (Msg.wParam)
			{
			case VK_ESCAPE:
				Keyboard->isQuitting = TRUE;
				break;
			case VK_SHIFT:
				Keyboard->Key_Shift = TRUE;
				break;
			case VK_CONTROL:
				Keyboard->Key_Ctrl = TRUE;
				break;
			case VK_DOWN:
				Keyboard->DownArrow = TRUE;
				break;
			case VK_UP:
				Keyboard->UpArrow = TRUE;
				break;
			case VK_LEFT:
				Keyboard->LeftArrow = TRUE;
				break;
			case VK_RIGHT:
				Keyboard->RightArrow = TRUE;
				break;

			case 'W':
				Keyboard->Key_W = TRUE;
				break;
			case 'A':
				Keyboard->Key_A = TRUE;
				break;
			case 'S':
				Keyboard->Key_S = TRUE;
				break;
			case 'D':
				Keyboard->Key_D = TRUE;
				break;
			
			case 'P':
				Keyboard->Key_P = TRUE;
				break;
			}
			break;
		case WM_KEYUP:
			switch (Msg.wParam)
			{
			case VK_SHIFT:
				Keyboard->Key_Shift = FALSE;
				break;
			case VK_CONTROL:
				Keyboard->Key_Ctrl = FALSE;
				break;
			case VK_DOWN:
				Keyboard->DownArrow = FALSE;
				break;
			case VK_UP:
				Keyboard->UpArrow = FALSE;
				break;
			case VK_LEFT:
				Keyboard->LeftArrow = FALSE;
				break;
			case VK_RIGHT:
				Keyboard->RightArrow = FALSE;
				break;

			case 'W':
				Keyboard->Key_W = FALSE;
				break;
			case 'A':
				Keyboard->Key_A = FALSE;
				break;
			case 'S':
				Keyboard->Key_S = FALSE;
				break;
			case 'D':
				Keyboard->Key_D = FALSE;
				break;

			case 'P':
				Keyboard->Key_P = FALSE;
				break;
			}
		default:
			break;
	}
}

internal VOID Win32_ProcessMouse(MouseManager *Mouse, MSG Msg)
{
	POINT MousePos = {};
	switch (Msg.message)
	{
		case WM_MOUSEMOVE:
			if (!GetCursorPos(&MousePos))
			{
				DWORD Error = GetLastError();
				ls_printf("When retrieving mouse position in Win32_ProcessMouse got error: %d", Error);
			}
			Mouse->mouseX = (f32)MousePos.x;
			Mouse->mouseY = (f32)MousePos.y;
			//Mouse->mouseX = (((f32)MousePos.x * 2) / 1920.0f) - 1.0f;
			//Mouse->mouseY = (((f32)MousePos.y * 2) / 1080.0f) - 1.0f;
			break;
		case WM_KEYDOWN:
			switch (Msg.wParam)
			{
				case VK_LBUTTON:
					Mouse->LeftDown = TRUE;
					break;
				case VK_RBUTTON:
					Mouse->RigthDown = TRUE;
					break;
				case VK_MBUTTON:
					Mouse->MiddleDown = TRUE;
					break;
			}
			break;
		case WM_KEYUP:
			switch (Msg.wParam)
			{
				case VK_LBUTTON:
					Mouse->LeftDown = FALSE;
					break;
				case VK_RBUTTON:
					Mouse->RigthDown = FALSE;
					break;
				case VK_MBUTTON:
					Mouse->MiddleDown = FALSE;
					break;
			}
			break;
	}
}

internal LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch (Message)
	{
		case WM_ACTIVATEAPP:
			if (wParam == TRUE)
			{
				OutputDebugStringA("Activate App\n"); 
				//@TODO Make this error path more @ROBUST. SetCapture actually returns an Handle to the previous Window owning mouse capture
				//If that window wasn't me, it will just post errors without meaning, even if stuff worked.
				if (SetCapture(Window) == NULL)
				{
					DWORD Error = GetLastError();
					ls_printf("When Setting Mouse Capture in WindowProc got error: ", Error);
				}
			}
			else
			{
				OutputDebugStringA("Deactivate App\n");
				if (ReleaseCapture() == NULL)
				{
					DWORD Error = GetLastError();
					ls_printf("When Setting Mouse Capture in WindowProc got error: ", Error);
				}
			}
			break;

		default:
			return DefWindowProcA(Window, Message, wParam, lParam);
	}

	return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

#ifdef LS_PLAT_WINDOWS
	AllocConsole();
#endif

	LARGE_INTEGER QueryFreq = {};
	if (!QueryPerformanceFrequency(&QueryFreq))
	{
		DWORD Error = GetLastError();
		ls_printf("Error in QueryPerformanceFrequency call: ", Error);
	}

	WindowInfo Screen = {};
	Screen.Height = 1080;
	Screen.Width = 1920;
	Screen.properties = LS_UNIQUEDC | LS_HREDRAW | LS_VREDRAW;
	Screen.style = LS_OVERLAPPED | LS_VISIBLE;
	Screen.className = "Window Class";
	Screen.menuName = "Window Menu";
	Screen.windowName = "Window";
	Screen.WindowProc = WindowProc;

	ls_createWindow(&Screen);
	ls_setupOpenGLContext(&Screen);

	OpenGLInfo OpenGL = {};

	GameInfo Game = {};

	InputManager Input = {};
	KeyboardManager Keyboard = {};
	MouseManager Mouse = {};
	Mouse.MouseCenterX = (f32)Screen.Width / 2.0f;
	Mouse.MouseCenterY = (f32)Screen.Height / 2.0f;
	Input.Keyboard	= &Keyboard;
	Input.Mouse		= &Mouse;

	b32 Running = TRUE;

	LARGE_INTEGER FirstCounter = {};
	if (!QueryPerformanceCounter(&FirstCounter))
	{
		DWORD Error = GetLastError();
		ls_printf("Error calling QueryPerformanceCounter at the beginning of the loop: ", Error);
	}
	while(Running)
	{
		MSG Msg;
		while (PeekMessageA(&Msg, Screen.WindowHandle, 0, 0, PM_REMOVE))
		{
			Win32_ProcessKeyboard(&Keyboard, Msg);
			Win32_ProcessMouse(&Mouse, Msg);

			TranslateMessage(&Msg);
			DispatchMessageW(&Msg);

			if (Keyboard.isQuitting)
			{
				Running = FALSE;
			}
		}

		//glClearColor(0.0f, 0.75f, 1.0f, 1.0f);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameLoop(&Game, &Screen, &OpenGL, &Input);

		HWND ActiveWindow = GetActiveWindow();
		if (ActiveWindow == Screen.WindowHandle)
		{
			SetCursorPos(Screen.Width / 2, Screen.Height / 2);
		}

		if (SwapBuffers(Screen.DeviceContext) == FALSE)
		{
			DWORD Error = GetLastError();
			ls_printf("In swapping buffers error: ", Error);
		}

		LARGE_INTEGER LastCounter = {};
		if (!QueryPerformanceCounter(&LastCounter))
		{
			DWORD Error = GetLastError();
			ls_printf("Error calling QueryPerformanceCounter at the end of the loop: ", Error);
		}

		s64 CounterDelta = LastCounter.QuadPart - FirstCounter.QuadPart;
		f32 MillisecondsPerFrame = ((f32)(1000 * CounterDelta) / (f32)QueryFreq.QuadPart);
		if (MillisecondsPerFrame < 16.67f)
		{
			DWORD RemainingTime = DWORD(16.67f - MillisecondsPerFrame);
			Sleep(RemainingTime);
		}

		FirstCounter = LastCounter;
	}
	return 0;
}