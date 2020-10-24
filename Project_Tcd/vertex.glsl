#version 330 core
layout(location = 0) in vec3 vPostion;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexcoord;
out vec4 Postion;
out vec3 Color;
out vec2 Textcord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;



void main()
{
	Postion =  ModelMatrix * vec4(vPostion,1.0f);
	Color = vColor;
	Textcord = vec2(vTexcoord.x, vTexcoord.y * -1.0f);
	gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vPostion,1.0f);
};
