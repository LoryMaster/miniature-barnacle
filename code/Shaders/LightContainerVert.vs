#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 transform;
uniform mat4 model;

out vec3 Normals;
out vec3 FragPos;

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
	
	FragPos = vec3(model * vec4(pos, 1.0));
	Normals = normal;
} 