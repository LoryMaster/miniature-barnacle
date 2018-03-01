#pragma once

#include "Platform\win32.h"
#include "tools\lsCRT.h"
#include "tools\Maths\Maths.h"

struct Shader;
struct Texture;
struct Camera;
struct TransformManager;

enum FILE_TYPE
{
	BINARY_DATA,
	BITMAP,
	//PNG,

	FILE_TYPE_MAX
};

struct FileInfo
{
	FILE_TYPE	FileType;

	u64			size;
	void		*data;

};

struct ScreenInfo
{
	WNDCLASSA	WindowClass;
	HWND		WindowHandle;
	HDC			DeviceContext;
	HGLRC		RenderingContext;

	s32			Width;
	s32			Height;

	s32			UpdateFrequency;
};

struct KeyboardManager
{
	b32	isQuitting = FALSE;

	b32	DownArrow = FALSE;
	b32 UpArrow = FALSE;
	b32	LeftArrow = FALSE;
	b32 RightArrow = FALSE;

	b32 Key_W = FALSE;
	b32 Key_A = FALSE;
	b32 Key_S = FALSE;
	b32 Key_D = FALSE;

	b32 Key_P = FALSE;

	b32 Key_Shift = FALSE;
	b32 Key_Ctrl = FALSE;
};

struct MouseManager
{
	f32 mouseX;
	f32 mouseY;

	f32 xOffset;
	f32 yOffset;

	f32 MouseCenterX;
	f32 MouseCenterY;

	b32 LeftDown = FALSE;
	b32 RigthDown = FALSE;
	b32 MiddleDown = FALSE;
};

enum VAO_Type
{
	VAO_TRIANGLE,
	VAO_RECTANGLE,
	VAO_LIGHT_CONTAINER,
	VAO_LIGHT,

	VAO_MAX
};

struct VAO_Container
{
	GLuint		VAO;
	Shader		*ShaderProgram;
	Texture		*Texture;

	VAO_Type	Type;
	u32			IndexInContainer;
};

struct OpenGLInfo
{
	VAO_Container		VAOs[32];
	u32					NextAvailableIndex;

	Camera				*Camera;
	TransformManager	*Transform;
};

struct InputManager
{
	MouseManager		*Mouse;
	KeyboardManager		*Keyboard;
};

enum GAME_MODE
{
	WORLD_MODE,

	NUM_MODE
};

struct VertexData
{
	GLfloat *vertices;
	size_t verticesSize;

	GLuint *indices;
	size_t indicesSize;
};

struct GameInfo
{
	GAME_MODE GameMode;

	Bitmap bitmaps[10];
	u32 NextBitmapIndex;
};

void LoadTexture(GameInfo *Game, const char *Path);

extern "C" void GameLoop(GameInfo *Game, WindowInfo *Screen, OpenGLInfo *OpenGL, InputManager *Input);

internal void ProcessWorldInput(KeyboardManager *Keyboard, f32 *AngleX, f32 *AngleY);
internal void ProcessCameraInput(KeyboardManager *Keyboard, Camera *Camera, v3 cameraFront);
internal void InitCamera(OpenGLInfo *OpenGL);
internal void InitTransform(OpenGLInfo *OpenGL);
internal void RenderToScreen(OpenGLInfo *OpenGL, VertexData Vertex, VAO_Type Type);
internal void SetupVAO(GameInfo *Game, OpenGLInfo *OpenGL, VAO_Type Type, VertexData Vertex, char **texPaths, u32 texQuantity, char *VSPath, char *FSPath);