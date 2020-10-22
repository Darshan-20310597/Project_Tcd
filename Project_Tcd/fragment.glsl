#version 330 core
in vec4 Postion;
in vec3 Color;
in vec2 Textcord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;


void main()
{
	//FragColor = vec4(Color, 1.0f);
	FragColor = texture(texture0, Textcord)*texture(texture1, Textcord);

};