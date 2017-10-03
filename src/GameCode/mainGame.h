#pragma once

#include "Platform\win32.h"
#include "tools\Maths\Maths.h"

enum GAME_MODE
{
	WORLD_MODE,

	NUM_MODE
};

//struct Bitmap
//{
//	void *data;
//
//	u32 width;
//	u32 height;
//
//	u32 size;
//};

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

void LoadTexture(GameInfo *Game, MemoryArena *Memory, const char *Path);

extern "C" void GameLoop(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, InputManager *Input);

internal void ProcessWorldInput(KeyboardManager *Keyboard, f32 *AngleX, f32 *AngleY);
internal void ProcessCameraInput(KeyboardManager *Keyboard, Camera *Camera, v3 cameraFront);
internal void InitCamera(OpenGLInfo *OpenGL, MemoryArena *Memory);
internal void InitTransform(OpenGLInfo *OpenGL, MemoryArena *Memory);
internal void RenderToScreen(OpenGLInfo *OpenGL, VertexData Vertex, VAO_Type Type);
internal void SetupVAO(GameInfo *Game, MemoryArena *Memory, OpenGLInfo *OpenGL, VAO_Type Type, VertexData Vertex, Texture *Tex, char *VSPath, char *FSPath);