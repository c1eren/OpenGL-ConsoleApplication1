#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	//program ID
	GLuint m_Program;

	//constructor reads and builds the shader
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	//use the program
	void Use();

	//set texture int
	void setInt(const char *f_name, int val);

	//set float
	void setFloat(const char* f_name, float val);

	//set vec3
	void setVec3(const char *f_name, glm::vec3 vectors);

	//set matrix
	void setMat4(const char* f_name, glm::mat4 matrix);
};

#endif