#pragma once

#include <glad/glad.h>

#include "VAP.h"


class VertexArrayObject {
public:
	GLuint m_Id;

	VertexArrayObject();

	void bind();
	void unbind();
	void setAttribPointer(const VertexAttribPointer::attribs& attribData);
};