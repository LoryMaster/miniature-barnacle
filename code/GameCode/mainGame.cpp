#include "GameCode\mainGame.h"
#include "tools\OpenGL\glCore.h"

void LoadTexture(GameInfo *Game, MemoryArena *Memory, const char *Path)
{
	FileInfo File = {};
	Memory->ReadEntireFile(Path, &File, &Memory->PermanentMemory);

	if (File.FileType == BITMAP)
	{
		u32 PixelOffset	= *((u32 *)((char *)File.data + 10));
		u32 HeaderSize	= *((u32 *)((char *)File.data + 14));

		s32 Width		= *((s32 *)((char *)File.data + 18));
		s32 Height		= *((s32 *)((char *)File.data + 22));
		Height = ls_abs(Height);

		u32 Compression = *((u32 *)((char *)File.data + 30));

		u32 PixelBufferSize = *((u32 *)((char *)File.data + 34));

		Game->bitmaps[Game->NextBitmapIndex].data = ((char *)File.data + PixelOffset);
		Game->bitmaps[Game->NextBitmapIndex].width = Width;
		Game->bitmaps[Game->NextBitmapIndex].height = Height;
		Game->bitmaps[Game->NextBitmapIndex++].size = (u32)File.size;
	}
}

//@TODO Better Input Control?
internal void ProcessWorldInput(KeyboardManager *Keyboard, f32 *AngleX, f32 *AngleY)
{
	if (Keyboard->Key_W == TRUE)
	{
		*AngleX += 0.1f;
	}
	if (Keyboard->Key_D == TRUE)
	{
		*AngleY += 0.1f;
	}
	if (Keyboard->Key_S == TRUE)
	{
		*AngleX -= 0.1f;
	}
	if (Keyboard->Key_A == TRUE)
	{
		*AngleY -= 0.1f;
	}
}

//@TODO Better Input Control?
internal void ProcessCameraInput(KeyboardManager *Keyboard, Camera *Camera, v3 cameraFront)
{
	v3 cameraUp = Camera->worldY;

	if (Keyboard->RightArrow == TRUE)
	{
		Camera->pos = Camera->pos + V4((Normalize(cameraFront ^ cameraUp) * Camera->speed));
	}
	if (Keyboard->UpArrow == TRUE)
	{
		Camera->pos = Camera->pos + V4(cameraUp * Camera->speed);
	}
	if (Keyboard->LeftArrow == TRUE)
	{
		Camera->pos = Camera->pos - V4((Normalize(cameraFront ^ cameraUp) * Camera->speed));
	}
	if (Keyboard->DownArrow == TRUE)
	{
		Camera->pos = Camera->pos - V4(cameraUp * Camera->speed);
	}
	if (Keyboard->Key_Shift == TRUE)
	{
		Camera->pos = Camera->pos - V4(cameraFront * Camera->speed);
	}
	if (Keyboard->Key_Ctrl == TRUE)
	{
		Camera->pos = Camera->pos + V4(cameraFront * Camera->speed);
	}
}

internal void InitCamera(OpenGLInfo *OpenGL, MemoryArena *Memory)
{
	v4 pos = { 0.0f, 0.0f, 15.0f, 1.0f };
	v4 target = { 0.0f, 0.0f, 0.0f, 1.0f };
	Camera *Camera = createCamera(Memory, pos, target);

	OpenGL->Camera = Camera;
}

internal void RenderTriangle(GameInfo *Game, ScreenInfo *Screen, OpenGLInfo *OpenGL, MemoryArena *Memory)
{
	//TEMPORARY, MAKE FINDING FUNCTION MAYBE?
	GLuint *VAO = &OpenGL->VAOs[0].VAO;
	GLuint *Program = 0;

	if (&OpenGL->VAOs[0].ShaderProgram)
	{
		Program = &OpenGL->VAOs[0].ShaderProgram->Program;
	}
	
	if(!(*VAO && *Program))
	{
		glViewport(0, 0, Screen->Width, Screen->Height);


		glGenVertexArrays(1, VAO);
		glBindVertexArray(*VAO);

		GLfloat vertices[] =
		{
			-0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			-1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		Shader *ShaderProgram = CreateShaderProgram(Memory, "W:/doubleMouse/code/Shaders/TriangleVert.vs", "W:/doubleMouse/code/Shaders/TriangleFrag.frag");
		OpenGL->VAOs[0].ShaderProgram = ShaderProgram;

		if (!Program) { Program = &OpenGL->VAOs[0].ShaderProgram->Program; }

		OpenGL->VAOs[0].Type = VAO_TRIANGLE;
		OpenGL->VAOs[0].IndexInContainer = OpenGL->NextAvailableIndex;
		OpenGL->NextAvailableIndex++;
	}

	glUseProgram(*Program);

	glBindVertexArray(*VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	
}

internal void RenderRectangle(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, f32 right, f32 top, f32 AngleX, f32 AngleY)
{
	GLuint *VAO = &OpenGL->VAOs[1].VAO;
	GLuint *Program = 0;

	if (&OpenGL->VAOs[1].ShaderProgram)
	{
		Program = &OpenGL->VAOs[1].ShaderProgram->Program;
	}

	if (!(*VAO && *Program))
	{
		glViewport(0, 0, Screen->Width, Screen->Height);


		glGenVertexArrays(1, VAO);
		glBindVertexArray(*VAO);

		//GLfloat vertices[] =
		//{
		//	// pos				// color		   // texCoords
		//	0.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		//	1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		//    0.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		//	1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f
		//};
		//GLfloat vertices[] =
		//{
		//	// pos				// color		   // texCoords
		//	0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		//	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		//   -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		//   -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
		//};
		GLfloat vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		GLuint indices[] =
		{
			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,
			
			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,

			0, 1, 2,
			2, 3, 0,
		};

		GLuint VBO, EBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /*8*/5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//glVertexAttribPointer(1, 2/*3*/, GL_FLOAT, GL_FALSE, /*8*/ 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		/*Texture *Tex = InitTextureManager(Memory, 2);
		GenAndBindTexture("W:/doubleMouse/resources/test.bmp", Game, Memory, Tex, TEX_TEST);
		GenAndBindTexture("W:/doubleMouse/resources/facciaDiUaua.bmp", Game, Memory, Tex, TEX_TEST_2);*/

		Shader *ShaderProgram = CreateShaderProgram(Memory, "W:/doubleMouse/code/Shaders/RectangleVert.vs", "W:/doubleMouse/code/Shaders/RectangleFrag.frag");
		OpenGL->VAOs[1].ShaderProgram = ShaderProgram;
		//OpenGL->VAOs[1].Texture = Tex;

		if(!Program) {Program = &OpenGL->VAOs[1].ShaderProgram->Program;}

		OpenGL->VAOs[1].Type = VAO_RECTANGLE;
		OpenGL->VAOs[1].IndexInContainer = OpenGL->NextAvailableIndex;
		OpenGL->NextAvailableIndex++;
	}

	glUseProgram(*Program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, OpenGL->VAOs[1].Texture->Tex[TEX_TEST]);
	glUniform1i(glGetUniformLocation(*Program, "myTexture1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, OpenGL->VAOs[1].Texture->Tex[TEX_TEST_2]);
	glUniform1i(glGetUniformLocation(*Program, "myTexture2"), 1);

	v4 cube[3] =
	{
		{ 0.0f,  0.0f,  0.0f, 1.0f },
		{ 2.0f,  5.0f, -15.0f, 1.0f },
		{ -1.5f, -2.2f, -2.5f, 1.0f }
	};
	Mat4 ModelMatrix = {};
	//@Learn The view Matrix Works properly now! But learn how opengl positions things? Where's 0,0,0?
	//Mat4 ViewMatrix1 = LookAt(OpenGL->Camera->Sys, OpenGL->Camera->pos);
	Mat4 ViewMatrix = LookAt(*OpenGL->Camera);


	//Mat4 ProjectionMatrix = PerspectiveProj(0.1f, 100.0f, 0.1f, 0.059f); //The one I found by testing, I think the FOV one is just better though

	Mat4 ProjectionMatrix = PerspectiveProjFOV(PI_32 / 4.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);
	Mat4 Transform = {};

	glBindVertexArray(*VAO);
	fil(3)
	{
		ModelMatrix = Translate(cube[i]) * RotateX((PI_32 / 32)*AngleX) * RotateY((PI_32 / 32)*AngleY) ;
		Transform = ProjectionMatrix * ViewMatrix * ModelMatrix;
		GLuint TransformLoc = glGetUniformLocation(*Program, "transform");
		glUniformMatrix4fv(TransformLoc, 1, GL_TRUE, (GLfloat *)Transform.values);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}

internal void RenderToScreen(OpenGLInfo *OpenGL, VertexData Vertex, VAO_Type Type, f32 AngleX, f32 AngleY)
{
	GLuint VAO = OpenGL->VAOs[Type].VAO;
	GLuint Program = OpenGL->VAOs[Type].ShaderProgram->Program;
	Texture *Texture = OpenGL->VAOs[1].Texture;

	glUseProgram(Program);

	char texName[24] = {};
	fil(Texture->texQuantity)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Texture->Tex[i]);
		ls_sprintf(texName, "myTexture[%d]", i);
		glUniform1i(glGetUniformLocation(Program, texName), i);
	}

	v4 cube[3] =
	{
		{ 0.0f,  0.0f,  0.0f, 1.0f },
		{ 2.0f,  5.0f, -15.0f, 1.0f },
		{ -1.5f, -2.2f, -2.5f, 1.0f }
	};

	Mat4 ModelMatrix = {};
	//@Learn The view Matrix Works properly now! But learn how opengl positions things? Where's 0,0,0?
	Mat4 ViewMatrix = LookAt(*OpenGL->Camera);
	Mat4 ProjectionMatrix = PerspectiveProjFOV(PI_32 / 4.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);
	Mat4 Transform = {};

	glBindVertexArray(VAO);
	fil(3)
	{
		ModelMatrix = Translate(cube[i]) * RotateX((PI_32 / 32)*AngleX) * RotateY((PI_32 / 32)*AngleY);
		Transform = ProjectionMatrix * ViewMatrix * ModelMatrix;
		GLuint TransformLoc = glGetUniformLocation(Program, "transform");
		glUniformMatrix4fv(TransformLoc, 1, GL_TRUE, (GLfloat *)Transform.values);

		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(Vertex.verticesSize / 5));
	}
	glBindVertexArray(0);
}

internal void SetupVAO(GameInfo *Game, MemoryArena *Memory, OpenGLInfo *OpenGL, VAO_Type Type, VertexData Vertex, Texture *Tex, char *VSPath, char *FSPath)
{
	GLuint *VAO = &OpenGL->VAOs[Type].VAO;
	GLuint *Program = 0;
	
	if (&OpenGL->VAOs[Type].ShaderProgram)
	{
		Program = &OpenGL->VAOs[Type].ShaderProgram->Program;
	}

	if (!(*VAO && *Program))
	{
		glGenVertexArrays(1, VAO);
		glBindVertexArray(*VAO);

		GLuint VBO, EBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, Vertex.verticesSize, Vertex.vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Vertex.indicesSize, Vertex.indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//glVertexAttribPointer(1, 2/*3*/, GL_FLOAT, GL_FALSE, /*8*/ 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		//glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		fil(Tex->texQuantity)
		{
			GenAndBindTexture(Tex->Path[i], Game, Memory, Tex, i);
		}
		
		Shader *ShaderProgram = CreateShaderProgram(Memory, VSPath, FSPath);
		OpenGL->VAOs[Type].ShaderProgram = ShaderProgram;
		OpenGL->VAOs[Type].Texture = Tex;

		if (!Program) { Program = &OpenGL->VAOs[1].ShaderProgram->Program; }

		OpenGL->VAOs[Type].Type = Type;
		OpenGL->VAOs[Type].IndexInContainer = OpenGL->NextAvailableIndex;
		OpenGL->NextAvailableIndex++;
	}
}

extern "C" void GameLoop(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, InputManager *Input)
{
	KeyboardManager *Keyboard = Input->Keyboard;
	MouseManager	*Mouse = Input->Mouse;

	if (!OpenGL->Camera) { InitCamera(OpenGL, Memory); }

	static v3 cameraFront = { 0.0f, 0.0f, -1.0f };

	static f32 AngleX = 0.0f;
	static f32 AngleY = 1.0f;
	static f32 right = 0.0f;
	static f32 top = 0.0f;
	static f32 yawArg = 0.0f;
	static f32 pitchArg = 0.0f;

	ProcessWorldInput(Keyboard, &AngleX, &AngleY);

	if (OpenGL->Camera)
	{
		f32 sensitivity = 0.5f;
		Mouse->xOffset = Mouse->MouseCenterX - Mouse->mouseX;
		Mouse->yOffset = Mouse->MouseCenterY - Mouse->mouseY;

		f32 xOff = (f32)Mouse->xOffset * sensitivity;
		f32 yOff = (f32)Mouse->yOffset * sensitivity;

		yawArg += (xOff / (Screen->Height / 2));
		pitchArg += (yOff / (Screen->Width / 2));

		f32 yaw = (f32)ls_atan((f64)yawArg);
		f32 pitch = (f32)ls_atan((f64)pitchArg);

		f32 MaxPitch = (89.0f*PI_32) / 180.0f;

		if (pitch > MaxPitch) { pitch = MaxPitch; }
		if (pitch < -MaxPitch) { pitch = -MaxPitch; }

		if (Keyboard->Key_P == TRUE)
		{
			int BreakHere = 1;
		}

		if ((yawArg && pitchArg) != 0)
		{
			cameraFront = { -(f32)ls_sine(yaw) * (f32)ls_cos(pitch) , (f32)ls_sine(pitch), -(f32)ls_cos(yaw) * (f32)ls_cos(pitch) };
			cameraFront = Normalize(cameraFront);
		}

		ProcessCameraInput(Keyboard, OpenGL->Camera, cameraFront);

		OpenGL->Camera->target = OpenGL->Camera->pos + V4(cameraFront);
	}


	//TEMPORARY VERTEX DATA
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0,

		0, 1, 2,
		2, 3, 0,

		0, 1, 2,
		2, 3, 0,

		0, 1, 2,
		2, 3, 0,

		0, 1, 2,
		2, 3, 0,

		0, 1, 2,
		2, 3, 0,
	};
	//TEMPORARY VERTEX DATA^^


	VertexData Vertex = {};
	Vertex.indices = indices;
	Vertex.indicesSize = sizeof(indices);
	Vertex.vertices = vertices;
	Vertex.verticesSize = sizeof(vertices);

	char *Paths[2] = { {"W:/doubleMouse/resources/test.bmp"}, {"W:/doubleMouse/resources/facciaDiUaua.bmp"} };
	TEXTURE_ENUM Names[2] = { TEX_TEST, TEX_TEST_2 };
	Texture *Tex = InitTextureManager(Memory, Paths, Names, 2);

	SetupVAO(Game, Memory, OpenGL, VAO_RECTANGLE, Vertex, Tex, "W:/doubleMouse/code/Shaders/RectangleVert.vs", "W:/doubleMouse/code/Shaders/RectangleFrag.frag");
	RenderToScreen(OpenGL, Vertex, VAO_RECTANGLE, AngleX, AngleY);

	//RenderTriangle(Game, Screen, OpenGL, Memory);
	//RenderRectangle(Game, Memory, Screen, OpenGL, right, top, AngleX, AngleY);

	return;
}