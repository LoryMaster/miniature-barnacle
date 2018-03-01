#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 pos;
	
	vec3 ambientStrength;
	vec3 diffuseStrength;
	vec3 specularStrength;
};

in vec3 Normals;
in vec3 FragPos;
in vec2 UVs;
out vec4 color;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
	/*Apply ambient lighting to the object by multiplying 
		its color by a constant. The object won't be completely dark, 
		it will recieve a small fraction of light from "distant sources"*/
		
	/*Added diffuse maps. I'm using the fragment color itself for ambient as well, 
	because the colors are the same (No point in having diffuse and ambient maps)*/
	
	vec3 ambientLight = light.ambientStrength * vec3(texture(material.diffuse, UVs));

	/*We only care about the direction of vectors, 
		not their magnitude in light calculations. 
		That's why we always normalize everything*/
	vec3 norm = normalize(Normals);
	vec3 lightDir = normalize(light.pos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuseLight = light.diffuseStrength * diff * vec3(texture(material.diffuse, UVs));
	
	/*Specular Lighting. The pow exponent (32) is the "shinyness" of the reflection. 
	The higher the value, the more focues the point of reflection is. 
	An exp of 256 would make a small shiny point, an exp of 2 would make a reflection as big as the cube itself*/
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specularLight =  light.specularStrength * spec * vec3(texture(material.specular, UVs));
	
	vec3 result = (ambientLight + diffuseLight + specularLight);
	color = vec4(result, 1.0f);
} 