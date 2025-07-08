#pragma once

#include <glad/glad.h>

class VertexAttribPointer {
public:
	struct attribs {
		GLuint index;
		GLint size; //is GLint for legacy -1 error checking
		GLenum type;
		GLboolean normalised;
		GLsizei stride;
		const GLvoid* pointer;
	};

	attribs data;

	//VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalised, GLsizei stride, const GLvoid* pointer)
		//: index(index), size(size), type(type), normalised(normalised), stride(stride), pointer(pointer)
	
	VertexAttribPointer(const attribs& attribData)
		: data(attribData)
	{}

	void enable() const
	{
		glEnableVertexAttribArray(data.index); 
		glVertexAttribPointer(
			data.index,
			data.size,
			data.type,
			data.normalised,
			data.stride,
			data.pointer
		);
	}
};