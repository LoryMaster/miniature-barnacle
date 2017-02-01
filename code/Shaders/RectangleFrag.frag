#version 330 core

in vec3 myColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main()
{
	color = mix(texture(myTexture1, TexCoord).rgba, texture(myTexture2, TexCoord).rgba, 0.3);
	
} 