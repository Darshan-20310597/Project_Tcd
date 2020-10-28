#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>

#include<SOIL2.h>
class Texture 
{
private:
	
	unsigned int id;
	int width;
	int height;
	unsigned int type;
	GLint textureunit;

public:

	Texture(const char* FileName,GLenum type, GLint textureunit)
	{
		this->textureunit = textureunit;
		this->type = type;
		unsigned char* image = SOIL_load_image(FileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);
		// We create a texture id to load the images 
		//unsigned int Texture0;
		//generate textures and bind it
		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		//glTexParamteri() -- maping images to x and y coordinates in Textures (S and T)
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image)
		{
			std::cout << "Image Loaded successfully" << std::endl;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			//glGenerateMipmap - makes smaller and bigger version of image we have given (Several sizes and 
			glGenerateMipmap(GL_TEXTURE_2D);

		}
		else {
			std::cout << "Error While Loading Image : Texture loading failed" << FileName <<std::endl;
		}

		glActiveTexture(0);
		glBindTexture(type, 0);
		SOIL_free_image_data(image);
	}

	~Texture() 
	{
		glDeleteTextures(1,&this->id);
	}

	void bind() 
	{
		glActiveTexture(GL_TEXTURE0 + this->textureunit);
		//std::cout << "Iy" << std::endl;
		glBindTexture(this->type, this->id);
	}
	void unbind() 
	{
		glActiveTexture(0);
		glBindTexture(this->type,0);
	}

	inline GLint getID() const { return this->id; }
};
