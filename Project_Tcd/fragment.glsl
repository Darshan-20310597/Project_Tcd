#version 330 core

struct Material
{
	//colors and intensities
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	//features
	sampler2D diffuseTex; 
	sampler2D specularTex;

};

in vec3 Postion;
in vec3 Color;
in vec2 Textcord;
in vec3 Normal;

out vec4 FragColor;

uniform Material material;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightpos0;
uniform vec3 CameraPosition;

//Create functions when you need instead of blocking the whole main

vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material,vec3 Postion, vec3 lightpos0,vec3 Normal)
{
	vec3 postoLigthDirVec = normalize(lightpos0-Postion);
	//vec3 diffuseColor = vec3(1.0f,1.0f,1.0f);
	float diffuse = clamp(dot(postoLigthDirVec,Normal),0,1);
	vec3 diffusefinal =  material.diffuse * diffuse;

	return diffusefinal;
	
}

vec3 calculateSpecular(Material material,vec3 Postion, vec3 lightpos0,vec3 Normal,vec3 CameraPosition)
{
	vec3 LigthtoPosDirVec = normalize(Postion-lightpos0);
	vec3 ReflectDir = normalize(reflect(-LigthtoPosDirVec, normalize(Normal)));
	vec3 Postoview = normalize(CameraPosition-lightpos0);
	float Specconstant = pow(max(dot(LigthtoPosDirVec,ReflectDir),0),100);
	vec3 SpecFinal =  material.specular * Specconstant;

	return SpecFinal;
	
}
void main()
{
	//FragColor = vec4(Color, 1.0f);
	//FragColor = texture(texture0, Textcord)*texture(texture1, Textcord);

	//Ambient light
	vec3 ambientlight = calculateAmbient(material);

	// Diffuse Light
	//vec3 postoLigthDirVec = normalize(Postion-lightpos0);
	//vec3 diffuseColor = vec3(1.0f,1.0f,1.0f);
	//float diffuse = clamp(dot(postoLigthDirVec,Normal),0,1);
	//vec3 diffusefinal =  material.diffuse * diffuse;
	vec3 diffusefinal =  calculateDiffuse(material,Postion,lightpos0,Normal);

	// Specular Light
//	vec3 LigthtoPosDirVec = normalize(lightpos0-Postion);
//	vec3 ReflectDir = normalize(reflect(-LigthtoPosDirVec, normalize(Normal)));
//	vec3 Postoview = normalize(lightpos0-CameraPosition);
//	float Specconstant = pow(max(dot(LigthtoPosDirVec,ReflectDir),0),30);
//	vec3 SpecFinal =  material.specular * Specconstant;
	vec3 SpecFinal = calculateSpecular(material,Postion,lightpos0,Normal,CameraPosition);

	FragColor = texture(texture0, Textcord) 
	* (vec4(ambientlight,1.0f) + vec4(diffusefinal,1.0f) + vec4(SpecFinal,1.0f));

};