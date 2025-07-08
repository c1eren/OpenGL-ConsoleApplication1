//#include <iostream>

#include "VAO.h"

//constructor reads and builds the VAO
VertexArrayObject::VertexArrayObject()
{
	//debug
	//std::cout << "Vertex Array Object Constructed!" << std::endl;

	//generate VAO and set m_Id
	glGenVertexArrays(1, &this->m_Id);
	this->bind();
}

void VertexArrayObject::bind()
{
	glBindVertexArray(this->m_Id);
}

void VertexArrayObject::unbind()
{
	glBindVertexArray(0);
}

void VertexArrayObject::setAttribPointer(const VertexAttribPointer::attribs& attribData)
{
	bind();
	VertexAttribPointer VAP(attribData);
	VAP.enable();
}
