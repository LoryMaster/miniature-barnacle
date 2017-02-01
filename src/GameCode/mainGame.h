#pragma once

#include "win32.h"
#include "tools\Maths\Maths.h"

struct Bitmap
{
	void *data;

	u32 width;
	u32 height;

	u32 size;
};

struct GameInfo
{
	Bitmap bitmaps[10];
	u32 NextBitmapIndex;
};
void LoadTexture(GameInfo *Game, MemoryArena *Memory, const char *Path);

extern "C" void GameLoop(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, KeyboardManager *Keyboard);

//Test Functions
internal void RenderTriangle(GameInfo *Game, ScreenInfo *Screen, OpenGLInfo *OpenGL, MemoryArena *Memory);
internal void RenderRectangle(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, f32 right, f32 top, f32 AngleX, f32 AngleY);