#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 TextureCoords;

uniform mat4 transform;
uniform mat4 model;
uniform mat3 modelNormal;

out vec3 Normals;
out vec3 FragPos;
out vec2 UVs;

void main()
{
	gl_Position = transform * vec4(pos, 1.0);
	
	FragPos = vec3(model * vec4(pos, 1.0));
	
	/* Using the model normal so we have invariance in 
	respect to rotations, translations and resizes, 
	AND keep the normals, well... normal*/
	/*My own model normal seems to have some problems. 
	Directions are a little bit fucked. Don't know why, 
	considering I tested inverse and transpose and they seem to work*/
	Normals = mat3(transpose(inverse(model))) * normal; // modelNormal * normal;
	UVs = TextureCoords;
} 