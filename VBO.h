#pragma once

#include <span>

#include <glad/glad.h>


class VertexBufferObject {
public:
	GLuint m_Id;

	VertexBufferObject();

	//void bufferData(std::array<GLfloat, 120>& vertices);
	void bufferData(std::span<const GLfloat> vertices); //changed c++ from 14 to 20 for this in project properties

	void bind();
};