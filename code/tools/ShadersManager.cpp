#include "tools\OpenGL\Managers\ShadersManager.h"

Shader *CreateShaderProgram(GLchar *vertexShaderPath, GLchar *fragmentShaderPath)
{
	Shader *Result;

	char vsName[64], fsName[64];

	ls_getFileNameFromPath(vertexShaderPath, vsName);
	ls_getFileNameFromPath(fragmentShaderPath, fsName);

	Result = (Shader *)ls_alloc(sizeof(Shader));

	char *VertexShaderSource = 0, *FragmentShaderSource = 0;
	ls_readFile(vertexShaderPath, &VertexShaderSource, 0);
	ls_readFile(fragmentShaderPath, &FragmentShaderSource, 0);

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
			ls_printf("(%s): %s\n", vsName, infoLog);
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
			ls_printf("(%s), %s\n", fsName, infoLog);
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
			ls_printf("%s\n", infoLog);
		}
	}
	glDeleteShader(Result->VertexShader);
	glDeleteShader(Result->FragmentShader);

	return Result;
}


void UseShader(GLuint Program)
{
	glUseProgram(Program);
	return;
}

void Shader::setVec3(const char* name, v3 v)
{
	glUniform3f(glGetUniformLocation(this->Program, name), v.x, v.y, v.z);
}

void Shader::setVec3(const char* name, f32 x, f32 y, f32 z)
{
	glUniform3f(glGetUniformLocation(this->Program, name), x, y, z);
}

void Shader::setMat4(const char* name, f32 *value)
{
	glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_TRUE, (GLfloat *)value);
}

void Shader::setFloat(const char* name, f32 value)
{
	glUniform1f(glGetUniformLocation(this->Program, name), value);
}

void Shader::setInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(this->Program, name), value);
}