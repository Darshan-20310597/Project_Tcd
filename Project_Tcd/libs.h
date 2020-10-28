#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include <string>
#include <sstream>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec4.hpp>
#include<vec3.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<Windows.h>

#include<Shader.h>
#include<Texture.h>


using namespace std;


#include<SOIL2.h>


struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 textcoord;
	glm::vec3 normal;
};

