#pragma once

#include "win32.h"
#include "tools\Maths\Maths.h"

enum GAME_MODE
{
	WORLD_MODE,

	NUM_MODE
};

struct Bitmap
{
	void *data;

	u32 width;
	u32 height;

	u32 size;
};

struct GameInfo
{
	GAME_MODE GameMode;

	Bitmap bitmaps[10];
	u32 NextBitmapIndex;
};
void LoadTexture(GameInfo *Game, MemoryArena *Memory, const char *Path);

extern "C" void GameLoop(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, InputManager *Input);

//Test Functions
internal void RenderTriangle(GameInfo *Game, ScreenInfo *Screen, OpenGLInfo *OpenGL, MemoryArena *Memory);
internal void RenderRectangle(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, f32 right, f32 top, f32 AngleX, f32 AngleY);