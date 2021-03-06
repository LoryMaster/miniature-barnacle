#version 330 core

in vec3 myColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D myTexture[2];
//uniform sampler2D myTexture2;

void main()
{
	color = mix(texture(myTexture[0], TexCoord).rgba, texture(myTexture[1], TexCoord).rgba, 0.3);
	
} 