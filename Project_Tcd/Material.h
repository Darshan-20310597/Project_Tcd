#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>
#include <string>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec4.hpp>
#include<vec3.hpp>
#include<mat4x4.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"


class Material 
{
private:
	//colors and intensities
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	//features
	GLint  diffuseTex;
	GLint  specularTex;
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint  diffuseTex, GLint  specularTex)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->diffuseTex = diffuseTex;
		this->specularTex = specularTex;
	
	}

	~Material(){}

	void senToShader(Shader& Programid)
	{
		Programid.setVec3f(this->ambient, "material.ambient");
		Programid.setVec3f(this->diffuse, "material.diffuse");
		Programid.setVec3f(this->specular, "material.specular");
		Programid.set1f(this->diffuseTex, "material.diffuseTex");
		Programid.set1f(this->specularTex, "material.specularTex");
	}


};