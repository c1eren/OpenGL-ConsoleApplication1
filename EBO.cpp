#pragma once

//#include<iostream>

#include "EBO.h"

ElementBufferObject::ElementBufferObject()
{
	//debug
	//std::cout << "Element Buffer Object Constructed!" << std::endl;

	//generate EBO and set m_Id
	glGenBuffers(1, &this->m_Id);
	this->bind();
}

void ElementBufferObject::bufferData(std::span<const GLuint> indices)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void ElementBufferObject::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_Id);
}