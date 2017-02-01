#pragma once

#include "win32.h"
#include "GameCode\mainGame.h"
#include "tools\OpenGL\glCore.h"

enum TEXTURE_ENUM
{
	TEX_TEST = 0,
	TEX_TEST_2 = 1,

	TEX_MAX
};

struct Texture
{
	GLuint			*Tex;
	
	u32				texQuantity;
	TEXTURE_ENUM	Name;
};

Texture *InitTextureManager(MemoryArena *Memory, u32 texQuantity);
void GenAndBindTexture(const char *Path, GameInfo *Game, MemoryArena *Memory, Texture *TextureManager, TEXTURE_ENUM Name);