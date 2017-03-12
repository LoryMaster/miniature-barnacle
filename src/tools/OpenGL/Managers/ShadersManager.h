#pragma once

#include "Platform\win32.h"
#include "tools\OpenGL\glCore.h"

struct Shader
{
	GLuint Program;

	GLuint VertexShader;
	GLuint FragmentShader;

	GLchar *vertexShaderPath;
	GLchar *fragmentShaderPath;
};

Shader *CreateShaderProgram(MemoryArena *Memory, GLchar *vertexShaderPath, GLchar *fragmentShaderPath);
void UseShader(Shader *ShaderProgram);