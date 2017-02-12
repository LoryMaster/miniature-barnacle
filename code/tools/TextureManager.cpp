#include "tools\OpenGL\Managers\TextureManager.h"

Texture *InitTextureManager(MemoryArena *Memory, char **Paths, TEXTURE_ENUM *Names, u32 texQuantity)
{
	Texture *TextureManager;

	Memory->Alloc(&Memory->PermanentMemory, (void **)(&TextureManager), sizeof(Texture));

	Memory->Alloc(&Memory->PermanentMemory, (void **)(&TextureManager->Tex), texQuantity * sizeof(GLuint));
	Memory->Alloc(&Memory->PermanentMemory, (void **)(&TextureManager->Name), texQuantity * sizeof(TEXTURE_ENUM));

	TextureManager->texQuantity = texQuantity;
	TextureManager->Path = Paths;
	TextureManager->Name = Names;

	return TextureManager;
}

void GenAndBindTexture(const char *Path, GameInfo *Game, MemoryArena *Memory, Texture *TextureManager, u32 idx)
{
	glGenTextures(1, &TextureManager->Tex[idx]);
	glBindTexture(GL_TEXTURE_2D, TextureManager->Tex[idx]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	LoadTexture(Game, Memory, Path);

	Bitmap currBitmap = Game->bitmaps[Game->NextBitmapIndex - 1];
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, currBitmap.width, currBitmap.height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, currBitmap.data);
	glBindTexture(GL_TEXTURE_2D, 0);
}