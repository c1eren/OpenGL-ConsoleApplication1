#pragma once

#include <glad/glad.h>
#include <span>

class ElementBufferObject {
public:
	GLuint m_Id;

	ElementBufferObject();

	void bufferData(std::span<const GLuint> indices);

	//template<typename T>
	//void bufferData(std::span<const T> data, GLenum target);

	void bind();

};