#version 330 core
layout(location = 0) in vec3 vPostion;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexcoord;
layout(location = 3) in vec3 vNormal;
out vec3 Postion;
out vec3 Color;
out vec2 Textcord;
out vec3 Normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;




void main()
{
	Postion =  vec3(ModelMatrix * vec4(vPostion,1.0f)).xyz;
	Color = vColor;
	Textcord = vec2(vTexcoord.x, vTexcoord.y * -1.0f);
	// for Normal we consider only the translation part and not the homogenous part only world space 
	Normal = mat3(ModelMatrix) * vNormal;
	gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vPostion,1.0f);
};
