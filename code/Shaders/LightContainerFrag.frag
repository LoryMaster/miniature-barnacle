#version 330 core

in vec3 Normals;
in vec3 FragPos;
out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	/*Apply ambient lighting to the object by multiplying 
		its color by a constant. The object won't be completely dark, 
		it will recieve a small fraction of light from "distant sources"*/
		
	float ambientStrength = 0.1;
	vec3 ambientLight = ambientStrength * lightColor;

	/*We only care about the direction of vectors, 
		not their magnitude in light calculations. 
		That's why we always normalize everything*/
	vec3 norm = normalize(Normals);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseLight = diff * lightColor;
	
	vec3 result = (ambientLight + diffuseLight) * objectColor;
	color = vec4(result, 1.0f);
} 