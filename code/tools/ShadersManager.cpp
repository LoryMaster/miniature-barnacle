#include "tools\OpenGL\Managers\ShadersManager.h"

Shader *CreateShaderProgram(MemoryArena *Memory, GLchar *vertexShaderPath, GLchar *fragmentShaderPath)
{
	Shader *Result;

	Memory->Alloc(&Memory->PermanentMemory, (void **)(&Result), sizeof(Shader));

	char *VertexShaderSource = 0, *FragmentShaderSource = 0;
	Memory->ReadTextFile(&Memory->PermanentMemory, vertexShaderPath, &VertexShaderSource);
	Memory->ReadTextFile(&Memory->PermanentMemory, fragmentShaderPath, &FragmentShaderSource);

	Result->VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Result->VertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(Result->VertexShader);
	{
		GLint success;
		GLchar infoLog[512];

		glGetShaderiv(Result->VertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(Result->VertexShader, 512, NULL, infoLog);
			LogErrori(infoLog, -1);
		}
	}

	Result->FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Result->FragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(Result->FragmentShader);
	{
		GLint success;
		GLchar infoLog[512];

		glGetShaderiv(Result->FragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(Result->FragmentShader, 512, NULL, infoLog);
			LogErrori(infoLog, -1);
		}
	}

	Result->Program = glCreateProgram();
	glAttachShader(Result->Program, Result->VertexShader);
	glAttachShader(Result->Program, Result->FragmentShader);
	glLinkProgram(Result->Program);
	{
		GLint success;
		GLchar infoLog[512];

		glGetProgramiv(Result->Program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(Result->Program, 512, NULL, infoLog);
			LogErrori(infoLog, -1);
		}
	}
	glDeleteShader(Result->VertexShader);
	glDeleteShader(Result->FragmentShader);

	return Result;
}


void UseShader(Shader *ShaderProgram)
{
	glUseProgram(ShaderProgram->Program);
	return;
}