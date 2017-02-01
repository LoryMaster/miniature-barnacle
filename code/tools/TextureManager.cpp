#include "tools\OpenGL\Managers\TextureManager.h"

Texture *InitTextureManager(MemoryArena *Memory, u32 texQuantity)
{
	Texture *TextureManager;

	Memory->Alloc(&Memory->PermanentMemory, (void **)(&TextureManager), sizeof(Texture));

	Memory->Alloc(&Memory->PermanentMemory, (void **)(&TextureManager->Tex), texQuantity * sizeof(GLuint));
	TextureManager->texQuantity = texQuantity;

	return TextureManager;
}

void GenAndBindTexture(const char *Path, GameInfo *Game, MemoryArena *Memory, Texture *TextureManager, TEXTURE_ENUM Name)
{
	TextureManager->Name = Name;

	glGenTextures(1, &TextureManager->Tex[Name]);
	glBindTexture(GL_TEXTURE_2D, TextureManager->Tex[Name]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	LoadTexture(Game, Memory, Path);

	Bitmap currBitmap = Game->bitmaps[Game->NextBitmapIndex - 1];
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, currBitmap.width, currBitmap.height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, currBitmap.data);
	glBindTexture(GL_TEXTURE_2D, 0);
}