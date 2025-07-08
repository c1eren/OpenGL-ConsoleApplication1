//#include <iostream>

#include "VBO.h"

//constructor reads and builds the VAO
VertexBufferObject::VertexBufferObject()
{
	//debug
	//std::cout << "Vertex Buffer Object Constructed!" << std::endl;

	//generate VBO and set m_Id
	glGenBuffers(1, &this->m_Id);
	this->bind();
}

void VertexBufferObject::bufferData(std::span<const GLfloat> vertices) //passes pointer to container and a size 
{
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}

void VertexBufferObject::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_Id);
}
