#include "tools\OpenGL\Managers\TextureManager.h"
#include "GameCode\mainGame.h"
#include "tools\OpenGL\glCore.h"
#include "tools\lsCRT.h"

Texture *InitTextureManager(char **Paths, TEXTURE_ENUM *Names, u32 texQuantity)
{
	Texture *TextureManager;

	TextureManager = (Texture *)ls_alloc(sizeof(Texture));
	TextureManager->Tex = (GLuint *)ls_alloc(texQuantity * sizeof(GLuint));
	TextureManager->Name = (TEXTURE_ENUM *)ls_alloc(texQuantity * sizeof(TEXTURE_ENUM));
	
	//TODO: FIXME: What the fuck is happening with the Paths here !?!?!? 
	// Is that even a smart way to do it??
	TextureManager->texQuantity = texQuantity;
	TextureManager->Path = Paths;
	ls_memcpy(Names, TextureManager->Name, texQuantity * sizeof(TEXTURE_ENUM));
	//TextureManager->Name = Names;

	return TextureManager;
}

void FreeTextureManager(Texture *Tex)
{
	ls_free(Tex->Name);
	ls_free(Tex->Tex);
	ls_free(Tex);
}

void GenAndBindTexture(const char *Path, GameInfo *Game, Texture *TextureManager, u32 idx)
{
	glGenTextures(1, &TextureManager->Tex[idx]);
	glBindTexture(GL_TEXTURE_2D, TextureManager->Tex[idx]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	LoadTexture(Game, Path);

	Bitmap currBitmap = Game->bitmaps[Game->NextBitmapIndex - 1];
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, currBitmap.width, currBitmap.height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, currBitmap.data);

	glBindTexture(GL_TEXTURE_2D, 0);
}