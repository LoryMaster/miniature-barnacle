#include "tools\OpenGL\glCore.h"
#include "GameCode\mainGame.h"
//#include "tools\Maths\Maths.h"
#include "tools\lsCRT.h"

void LoadTexture(GameInfo *Game, MemoryArena *Memory, const char *Path)
{
	char ext[8];
	ls_getFileExtension((char *)Path, ext);

	if (ls_strcmp(ext, "bmp") == 0)
	{
		Bitmap bitmap = { 0 };
		ls_loadBitmap((char *)Path, &bitmap);
		Game->bitmaps[Game->NextBitmapIndex++] = bitmap;
	}

	else if (ls_strcmp(ext, "png") == 0)
	{
		PNG png = { 0 };
		ls_loadCompressedPNG((char *)Path, &png);
		Game->bitmaps[Game->NextBitmapIndex++] = (Bitmap)png;
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
		Camera->pos = Camera->pos + V4((NormalizeV3(cameraFront ^ cameraUp) * Camera->speed));
	}
	if (Keyboard->UpArrow == TRUE)
	{
		Camera->pos = Camera->pos + V4(cameraUp * Camera->speed);
	}
	if (Keyboard->LeftArrow == TRUE)
	{
		Camera->pos = Camera->pos - V4((NormalizeV3(cameraFront ^ cameraUp) * Camera->speed));
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

internal void InitTransform(OpenGLInfo *OpenGL, MemoryArena *Memory)
{
	TransformManager *Transform = createTransform(Memory);

	OpenGL->Transform = Transform;
}

internal void RenderToScreen(OpenGLInfo *OpenGL, VertexData Vertex, VAO_Type Type)
{
	GLuint VAO = OpenGL->VAOs[Type].VAO;
	Shader *Shader = OpenGL->VAOs[Type].ShaderProgram;
	GLuint Program = OpenGL->VAOs[Type].ShaderProgram->Program;
	Texture *Texture = OpenGL->VAOs[Type].Texture;

	UseShader(Program);
	//glUseProgram(Program);

	char texName[24] = {};
	fil(Texture->texQuantity)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, Texture->Tex[i]);
		ls_sprintf(texName, "myTexture[%d]", i);
		//ls_sprintf(texName, "material.diffuse");
		glUniform1i(glGetUniformLocation(Program, texName), i);
	}

	if (Type == VAO_LIGHT_CONTAINER)
	{
		v3 cameraPosInModelSpace = V3(OpenGL->Camera->pos * OpenGL->Transform->ModelMatrix);

		Shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		Shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		Shader->setVec3("lightPos", -1.5f, -2.2f, -2.5f);
		Shader->setVec3("viewPos", cameraPosInModelSpace);

		Shader->setVec3("material.ambientColor", 1.0f, 0.5f, 0.31f);
		Shader->setVec3("material.diffuseColor", 1.0f, 0.5f, 0.31f);
		Shader->setVec3("material.specularColor", 0.5f, 0.5f, 0.5f);
		Shader->setFloat("material.shininess", 128.0f);

		Shader->setVec3("light.ambientStrength", 0.2f, 0.2f, 0.2f);
		Shader->setVec3("light.diffuseStrength", 0.5f, 0.5f, 0.5f);
		Shader->setVec3("light.specularStrength", 1.0f, 1.0f, 1.0f);

		//glUniform3f(glGetUniformLocation(Program, "objectColor"), 1.0f, 0.5f, 0.31f);
		//glUniform3f(glGetUniformLocation(Program, "lightColor"), 1.0f, 1.0f, 1.0f);
		//glUniform3f(glGetUniformLocation(Program, "lightPos"), -1.5f, -2.2f, -2.5f);
		//glUniform3f(glGetUniformLocation(Program, "viewPos"), cameraPosInModelSpace.x, cameraPosInModelSpace.y, cameraPosInModelSpace.z);//OpenGL->Camera->pos.x, OpenGL->Camera->pos.y, OpenGL->Camera->pos.z);
	}

	glBindVertexArray(VAO);

	if (Type == VAO_RECTANGLE)
	{
		GLuint TransformLoc = glGetUniformLocation(Program, "transform");
		glUniformMatrix4fv(TransformLoc, 1, GL_TRUE, (GLfloat *)OpenGL->Transform->Transform.values);
	}

	if (Type == VAO_LIGHT_CONTAINER)
	{
		GLuint TransformLoc = glGetUniformLocation(Program, "transform");
		glUniformMatrix4fv(TransformLoc, 1, GL_TRUE, (GLfloat *)OpenGL->Transform->Transform.values);

		GLuint ModelLoc = glGetUniformLocation(Program, "model");
		glUniformMatrix4fv(ModelLoc, 1, GL_TRUE, (GLfloat *)OpenGL->Transform->ModelMatrix.values);

		GLuint ModelNormalLoc = glGetUniformLocation(Program, "modelNormal");
		glUniformMatrix3fv(ModelNormalLoc, 1, GL_TRUE, (GLfloat *)NormalMatrix(OpenGL->Transform->ModelMatrix).values);
	}
	
	else if (Type == VAO_LIGHT)
	{
		GLuint TransformLoc = glGetUniformLocation(Program, "transform");
		glUniformMatrix4fv(TransformLoc, 1, GL_TRUE, (GLfloat *)OpenGL->Transform->Transform.values);
	}

	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(Vertex.verticesSize / (8*sizeof(GLfloat))));
	glBindVertexArray(0);
}

internal void SetupVAO(GameInfo *Game, MemoryArena *Memory, OpenGLInfo *OpenGL, VAO_Type Type, VertexData Vertex, Texture *Tex, char *VSPath, char *FSPath)
{
	GLuint *VAO = &OpenGL->VAOs[Type].VAO;

	if (!(*VAO))
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

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
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
		OpenGL->VAOs[Type].Type = Type;
		OpenGL->VAOs[Type].IndexInContainer = OpenGL->NextAvailableIndex;
		OpenGL->NextAvailableIndex++;
	}
}

extern "C" void GameLoop(GameInfo *Game, MemoryArena *Memory, ScreenInfo *Screen, OpenGLInfo *OpenGL, InputManager *Input)
{
	KeyboardManager *Keyboard = Input->Keyboard;
	MouseManager	*Mouse = Input->Mouse;

	if (!OpenGL->Camera)	{ InitCamera(OpenGL, Memory); }
	if (!OpenGL->Transform) { InitTransform(OpenGL, Memory); }

	static v3 cameraFront = { 0.0f, 0.0f, -1.0f };

	static f32 AngleX = 0.0f;
	static f32 AngleY = 1.0f;
	static f32 right = 0.0f;
	static f32 top = 0.0f;
	static f32 yaw = 0.0f;
	static f32 pitch = 0.0f;

	ProcessWorldInput(Keyboard, &AngleX, &AngleY);

	if (OpenGL->Camera)
	{
		f32 sensitivity = 0.5f;
		Mouse->xOffset = Mouse->MouseCenterX - Mouse->mouseX;
		Mouse->yOffset = Mouse->MouseCenterY - Mouse->mouseY;

		f32 xOff = (f32)Mouse->xOffset * 0.08f;//sensitivity;
		f32 yOff = (f32)Mouse->yOffset * 0.25f;//sensitivity;

		f32 yawArg = (xOff / (Screen->Height / 2));
		f32 pitchArg = (yOff / (Screen->Width / 2));

		yaw += (f32)ls_atan((f64)yawArg);
		pitch += (f32)ls_atan((f64)pitchArg);

	/*	char buffer[512] = { };
		ls_sprintf(buffer, "yawArg: %f, yaw: %f, pitchArg: %f, pitch: %f\n", yawArg, yaw, pitchArg, pitchArg);
		OutputDebugStringA(buffer);*/

		f32 MaxPitch = (89.0f*PI_32) / 180.0f; //@TODO: Probably broken!?

		if (pitch > MaxPitch) { pitch = MaxPitch; }
		if (pitch < -MaxPitch) { pitch = -MaxPitch; }

		if (Keyboard->Key_P == TRUE)
		{
			int BreakHere = 1;
		}

		if ((yawArg && pitchArg) != 0)
		{
			cameraFront = { -(f32)ls_sine(yaw) * (f32)ls_cos(pitch) , (f32)ls_sine(pitch), -(f32)ls_cos(yaw) * (f32)ls_cos(pitch) };
			cameraFront = NormalizeV3(cameraFront);
		}

		ProcessCameraInput(Keyboard, OpenGL->Camera, cameraFront);

		OpenGL->Camera->target = OpenGL->Camera->pos + V4(cameraFront);
	}


	//TEMPORARY VERTEX DATA (V3 pos, V3 normals, V2 uvs)
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
							   
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
							    
		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
							   
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
							   
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
							   
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
	};

	GLfloat vertices2[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
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

	v4 cube[3] =
	{
		{ 0.0f,  0.0f,  0.0f, 1.0f },
		{ 2.0f,  5.0f, -15.0f, 1.0f },
		{ -1.5f, -2.2f, -2.5f, 1.0f }
	};
	v4 scale = { 1.0f, 1.0f, 1.0f, 1.0f };
	//TEMPORARY VERTEX DATA^^

	VertexData Vertex = {};
	Vertex.indices = indices;
	Vertex.indicesSize = sizeof(indices);
	Vertex.vertices = vertices;
	Vertex.verticesSize = sizeof(vertices);

	/*char *Paths[2] = { {"F:/ProgrammingProjects/Lowy/miniature-barnacle/resources/test.bmp"}, {"F:/ProgrammingProjects/Lowy/miniature-barnacle/resources/facciaDiUaua.bmp"} };
	TEXTURE_ENUM Names[2] = { TEX_TEST, TEX_TEST_2 };
	Texture *Tex = InitTextureManager(Memory, Paths, Names, 2);*/

	char *Path = "F:/ProgrammingProjects/Lowy/miniature-barnacle/resources/container.png";
	TEXTURE_ENUM Name = TEX_TEST;
	Texture *Tex = InitTextureManager(Memory, &Path, &Name, 1);

	SetupVAO(Game, Memory, OpenGL, VAO_RECTANGLE, Vertex, Tex, "F:/ProgrammingProjects/Lowy/miniature-barnacle/code/Shaders/RectangleVert.vs", "F:/ProgrammingProjects/Lowy/miniature-barnacle/code/Shaders/RectangleFrag.frag");
	SetupVAO(Game, Memory, OpenGL, VAO_LIGHT_CONTAINER, Vertex, Tex, "F:/ProgrammingProjects/Lowy/miniature-barnacle/code/Shaders/LightContainerVert.vs", "F:/ProgrammingProjects/Lowy/miniature-barnacle/code/Shaders/LightContainerFrag.frag");
	SetupVAO(Game, Memory, OpenGL, VAO_LIGHT, Vertex, Tex, "F:/ProgrammingProjects/Lowy/miniature-barnacle/code/Shaders/LightVert.vs", "F:/ProgrammingProjects/Lowy/miniature-barnacle/code/Shaders/LightFrag.frag");

	TransformManager *Transf = OpenGL->Transform;

	SetStandardProjection(Transf);
	fil(3)
	{
		SetView(Transf, *OpenGL->Camera);
		SetModel(Transf, cube[i], scale, AngleX, AngleY);

		SetTransform(Transf);

		RenderToScreen(OpenGL, Vertex, VAO_RECTANGLE);
	}

	//SetView(Transf, *OpenGL->Camera);
	//SetModel(Transf, cube[2], scale, AngleX, AngleY);

	//SetTransform(Transf);
	//RenderToScreen(OpenGL, Vertex, VAO_LIGHT);

	//SetModel(Transf, cube[0], scale, AngleX, AngleY);
	//SetTransform(Transf);

	//RenderToScreen(OpenGL, Vertex, VAO_LIGHT_CONTAINER);

	//SetModel(Transf, cube[1], scale, AngleX, AngleY);
	//SetTransform(Transf);

	//RenderToScreen(OpenGL, Vertex, VAO_LIGHT_CONTAINER);

	return;
}