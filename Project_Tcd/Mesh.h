#pragma once
#include<iostream>
#include<vector>
#include<Shader.h>
#include<Texture.h>
#include<Material.h>
#include<Vertex.h>


class Mesh
{
private:

	//std::vector<Vertex> vertices;
	//std::vector<GLuint> indices;
	unsigned noOfVertices;
	unsigned noOfIndices;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	//void initVertexData(Vertex* vertexArray, const unsigned& noOfVertices)Vertex* vertexArray, const unsigned& noOfVertices, GLuint* indexArray, const unsigned& noOfindeces
	//{
	//	for (size_t i = 0; i < noOfVertices; i++)
	//	{
	//		this->vertices.push_back(vertexArray[i]);
	//	}
	//}
	//void initIndexData(GLuint* indexArray, const unsigned& noOfindeces)
	//{
	//	for (size_t j = 0; j < noOfindeces; j++)
	//	{
	//		this->indices.push_back(indexArray[j]);
	//	}
	//}

	void initVAO(Vertex* vertexArray, const unsigned& noOfVertices, GLuint* indexArray, const unsigned& noOfIndices)
	{
		this->noOfVertices = noOfVertices;
		this->noOfIndices = noOfIndices;
		glGenVertexArrays(1, &this->VAO);// VAO Big box that holders all the data
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO); // Elelment object 
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		//glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, this->noOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->noOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textcoord));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void initModelmatrix()
	{

		this->position = glm::vec3(0.0f);
		this->rotation = glm::vec3(0.0f);
		this->scale = glm::vec3(1.0f);
		this->ModelMatrix = glm::mat4(1.0f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.f, 1.0f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);

	}

	void updateUniforms(Shader* shader) {
		shader->setMat4fv(this->ModelMatrix,"ModelMatrix");
	}
	

public:
	Mesh(Vertex* vertexArray, const unsigned& noOfVertices, GLuint* indexArray, const unsigned& noOfindeces)
	{
		//this->initVertexData(vertexArray, noOfVertices);
		//this->initIndexData(indexArray, noOfindeces);
		this->initVAO(vertexArray,noOfVertices, indexArray,noOfIndices);
		this->initModelmatrix();
		
	}


	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);

	}

	void update()
	{

	}
	void render(Shader* shader)
	{
		this->updateUniforms(shader);
		shader->use();
		glBindVertexArray(this->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		/*if (this->noOfIndices == NULL)
			glDrawArrays(GL_TRIANGLES, 0, this->noOfVertices);
		else*/
			glDrawElements(GL_TRIANGLES, this->noOfIndices, GL_UNSIGNED_INT, 0);
	}




};

