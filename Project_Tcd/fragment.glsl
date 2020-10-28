#version 330 core
in vec3 Postion;
in vec3 Color;
in vec2 Textcord;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightpos0;
uniform vec3 CameraPosition;


void main()
{
	//FragColor = vec4(Color, 1.0f);
	//FragColor = texture(texture0, Textcord)*texture(texture1, Textcord);

	//Ambient light
	vec3 ambientlight = vec3(.1f,.1f,.1f);

	// Diffuse Light
	vec3 postoLigthDirVec = normalize(Postion-lightpos0);
	vec3 diffuseColor = vec3(1.0f,1.0f,1.0f);
	float diffuse = clamp(dot(postoLigthDirVec,Normal),0,1);
	vec3 diffusefinal =  diffuseColor * diffuse;

	// Specular Light
	vec3 LigthtoPosDirVec = normalize(lightpos0-Postion);
	vec3 ReflectDir = normalize(reflect(-LigthtoPosDirVec, normalize(Normal)));
	vec3 Postoview = normalize(lightpos0-CameraPosition);
	float Specconstant = pow(max(dot(LigthtoPosDirVec,ReflectDir),0),30);
	vec3 SpecFinal =  vec3(1.0f,1.0f,1.0f) * Specconstant;

	FragColor = texture(texture1, Textcord) * vec4(Color, 1.0f) 
	* (vec4(ambientlight,1.0f) + vec4(diffusefinal,1.0f) + vec4(SpecFinal,1.0f));

};