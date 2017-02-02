//#include <Windows.h>
#include "win32.h"
#include "GameCode\mainGame.h"
#include "tools\OpenGL\glCore.h"

internal VOID Win32_SetFnPointers()
{
	return;
}

internal ULONGLONG Win32_Time()
{
	FILETIME FileTime = {};
	GetSystemTimeAsFileTime(&FileTime);

	ULARGE_INTEGER Time = {};
	Time.LowPart = FileTime.dwLowDateTime;
	Time.HighPart = FileTime.dwHighDateTime;

	ULONGLONG Result = (Time.QuadPart / 10000000);
	return Result;
}

internal VOID Win32_AllocateMemory(Memory *Memory, s32 Size, s32 MinimumAllocationSize)
{
	Memory->Size = Size;
	Memory->UsedMemory = 0;
	Memory->RemainingMemory = Size;
	Memory->MinimumAllocationSize = MinimumAllocationSize;

	if ((Memory->BeginPointer = VirtualAlloc(NULL, Size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)) == NULL)
	{
		DWORD Error = GetLastError();
		LogError("When calling VirtualAlloc in Win32_AllocateMemory got error: ", Error);
	}
}

internal DWORD Win32_GiveMemory(Memory *Memory, VOID **BasePointer, s32 Size)
{
	if ((Memory->RemainingMemory - Size) > 0)
	{
		if (Size < Memory->MinimumAllocationSize)
		{
			*BasePointer = (VOID *)((u8 *)Memory->BeginPointer + Memory->UsedMemory);
			Memory->UsedMemory += Memory->MinimumAllocationSize;
			Memory->RemainingMemory -= Memory->MinimumAllocationSize;
		}
		else
		{
			*BasePointer = (VOID *)((u8 *)Memory->BeginPointer + Memory->UsedMemory);
			Memory->UsedMemory += Size;
			Memory->RemainingMemory -= Size;
		}

		return TRUE;
	}
	else
	{
		//@TODO: Fix Crash Path with dinamically growing Arena(IF STRICTLY NECESSARY!)
		//Assert("Tried To Allocate More Memory than the Arena had to give!!" == 0)
		return FALSE;
	}
}

internal VOID Win32_ReadTextFile(Memory *Memory, char *Path, char **Dest)
{
	DWORD Error = 0;
	HANDLE FileHandle = 0;
	if ((FileHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		LogError("When creating a file handle got error: ", Error);
	}

	LARGE_INTEGER FileSize = {};
	if (GetFileSizeEx(FileHandle, &FileSize) == 0)
	{
		Error = GetLastError();
		LogError("When getting file size got error: ", Error);
	}

	if (Win32_GiveMemory(Memory, (void **)(Dest), FileSize.LowPart) == FALSE)
	{
		OutputDebugStringA("Couldn't Allocate The memory to store File contents into.\n");
		return;
	}

	DWORD BytesRead = 0;
	if (ReadFile(FileHandle, *Dest, FileSize.LowPart, &BytesRead, NULL) == FALSE)
	{
		Error = GetLastError();
		LogError("When Reading contents of a file got error: ", Error);
	}
	else
	{
		if (BytesRead != FileSize.LowPart)
		{
			Assert("Bytes read when reading entire file don't equal the file size!!" == 0)
		}
	}

	if (CloseHandle(FileHandle) == FALSE)
	{
		OutputDebugStringA("Couldn't close file handle at the end of Win32_ReadEntireFile function.\n");
	}
}

internal VOID Win32_ReadEntireFile(const char *Path, FileInfo *FileInfo, Memory *Memory)
{
	DWORD Error = 0;
	HANDLE FileHandle = 0;
	if ((FileHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
	{
		Error = GetLastError();
		LogError("When creating a file handle got error: ", Error);
	}

	LARGE_INTEGER FileSize = {};
	if (GetFileSizeEx(FileHandle, &FileSize) == 0)
	{
		Error = GetLastError();
		LogError("When getting file size got error: ", Error);
	}

	s32 PathLen = ls_len((char *)Path);
	char ext[4];
	ext[0] = Path[PathLen - 3];
	ext[1] = Path[PathLen - 2];
	ext[2] = Path[PathLen - 1];
	ext[3] = 0;

	if (ls_strcmp(ext, "bmp") == 0)
	{
		FileInfo->FileType = BITMAP;
	}

	if (Win32_GiveMemory(Memory, &FileInfo->data, FileSize.LowPart) == FALSE)
	{
		OutputDebugStringA("Couldn't Allocate The memory to store File contents into.\n");
		return;
	}

	DWORD BytesRead = 0;
	if (ReadFile(FileHandle, FileInfo->data, FileSize.LowPart, &BytesRead, NULL) == FALSE)
	{
		Error = GetLastError();
		LogError("When Reading contents of a file got error: ", Error);
	}
	else
	{
		if (BytesRead != FileSize.LowPart)
		{
			Assert("Bytes read when reading entire file don't equal the file size!!" == 0)
		}
	}

	if (CloseHandle(FileHandle) == FALSE)
	{
		OutputDebugStringA("Couldn't close file handle at the end of Win32_ReadEntireFile function.\n");
	}
	FileInfo->size = FileSize.LowPart;
}

internal VOID Win32_SetupScreen(ScreenInfo *Screen, s32 Height, s32 Width, HINSTANCE Instance)
{
	Screen->Height = 1080;
	Screen->Width = 1920;

	Screen->WindowClass = { 0 };
	Screen->WindowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	Screen->WindowClass.lpfnWndProc = WindowProc;
	Screen->WindowClass.hInstance = Instance;
	Screen->WindowClass.hCursor = 0;
	Screen->WindowClass.lpszMenuName = "Window Menu";
	Screen->WindowClass.lpszClassName = "Window Class";
	if (!RegisterClassA(&Screen->WindowClass))
	{
		DWORD Error = GetLastError();
		LogError("When Registering WindowClass in Win32_SetupScreen got error: ", Error);
	}

	//WindowProc function needs to be fully operational before calling CreateWindow(Ex)(A/W) Because it calls it and uses it's return to create the window.
	//It can be set to return DefWindowProc(A/W) to return all default values and not have to handle them
	if ((Screen->WindowHandle = CreateWindowExA(0L, Screen->WindowClass.lpszClassName, "Win 32 Platform", WS_OVERLAPPED | WS_VISIBLE , CW_USEDEFAULT, CW_USEDEFAULT, Screen->Width, Screen->Height, 0, 0, Instance, 0)) == nullptr)
	{
		DWORD Error = GetLastError();
		LogError("When Retrieving a WindowHandle in Win32_SetupScreen got error: ", Error);
	}

	if (SetCapture(Screen->WindowHandle) == NULL)
	{
		DWORD Error = GetLastError();
		LogError("When Setting Mouse Capture in Win32_SetupScreen got error: ", Error);
	}

	if (SetCursorPos(Screen->Width / 2, Screen->Height / 2) == NULL)
	{
		DWORD Error = GetLastError();
		LogError("When Setting Cursor Position in Win32_SetupScreen got error: ", Error);
	}
}

internal VOID Win32_SetupOpenGLRenderingContext(ScreenInfo *Screen)
{
	PIXELFORMATDESCRIPTOR PixelFormat = {};

	PixelFormat.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	PixelFormat.nVersion		= 1;
	PixelFormat.dwFlags			= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	PixelFormat.iPixelType		= PFD_TYPE_RGBA;
	PixelFormat.cColorBits		= 32;	//Colordepth of the framebuffer
	PixelFormat.cDepthBits		= 24;	//Number of bits for the depthbuffer
	PixelFormat.cStencilBits	= 8;	//Number of bits for the stencilbuffer

	Screen->DeviceContext		= GetDC(Screen->WindowHandle);
	s32 PixelFormatValue		= ChoosePixelFormat(Screen->DeviceContext, &PixelFormat);
	SetPixelFormat(Screen->DeviceContext, PixelFormatValue, &PixelFormat);

	Screen->RenderingContext	= wglCreateContext(Screen->DeviceContext);
	wglMakeCurrent(Screen->DeviceContext, Screen->RenderingContext);
	LoadGLFunc(Screen->DeviceContext);

	glEnable(GL_DEPTH_TEST);
}

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
				LogError("When retrieving mouse position in Win32_ProcessMouse got error: ", Error);
			}
			Mouse->xOffset = (f32)MousePos.x - Mouse->mouseX;
			Mouse->yOffset = Mouse->mouseY - (f32)MousePos.y;
			Mouse->mouseX = (f32)MousePos.x;
			Mouse->mouseY = (f32)MousePos.y;
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
			OutputDebugStringA("Activate App\n"); //@TODO: Test more throughly
			break;

		default:
			return DefWindowProcA(Window, Message, wParam, lParam);
	}

	return Result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Win32_SetFnPointers();

	LARGE_INTEGER QueryFreq = {};
	if (!QueryPerformanceFrequency(&QueryFreq))
	{
		DWORD Error = GetLastError();
		LogError("Error in QueryPerformanceFrequency call: ", Error);
	}

	ScreenInfo Screen = {};
	Win32_SetupScreen(&Screen, 1920, 1080, hInstance);
	Win32_SetupOpenGLRenderingContext(&Screen);

	MemoryArena Arena = {};
	Win32_AllocateMemory(&Arena.PermanentMemory, Megabyte(512), 4);
	Arena.Alloc = &Win32_GiveMemory;
	Arena.Time = &Win32_Time;
	Arena.ReadTextFile = &Win32_ReadTextFile;
	Arena.ReadEntireFile = &Win32_ReadEntireFile;
	Arena.StartingTime = Win32_Time();
	Arena.MsPerFrame = 16.67f;

	OpenGLInfo OpenGL = {};

	GameInfo Game = {};

	InputManager Input = {};
	KeyboardManager Keyboard = {};
	MouseManager Mouse = {};
	Input.Keyboard	= &Keyboard;
	Input.Mouse		= &Mouse;

	b32 Running = TRUE;

	LARGE_INTEGER FirstCounter = {};
	if (!QueryPerformanceCounter(&FirstCounter))
	{
		DWORD Error = GetLastError();
		LogError("Error calling QueryPerformanceCounter at the beginning of the loop: ", Error);
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

		glClearColor(0.0f, 0.75f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GameLoop(&Game, &Arena, &Screen, &OpenGL, &Input);
		if (SwapBuffers(Screen.DeviceContext) == FALSE)
		{
			DWORD Error = GetLastError();
			LogError("In swapping buffers error: ", Error);
		}

		LARGE_INTEGER LastCounter = {};
		if (!QueryPerformanceCounter(&LastCounter))
		{
			DWORD Error = GetLastError();
			LogError("Error calling QueryPerformanceCounter at the end of the loop: ", Error);
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