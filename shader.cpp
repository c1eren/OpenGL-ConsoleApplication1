#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


#include "shader.h"

//constructor reads and builds the shader
Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath)
{
	//debug
	std::cout << "Shader Object Constructed!" << std::endl;

	//retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//ensures ifstream objects can throw exceptions 
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//open files
		vShaderFile.open(vertexSourcePath);
		fShaderFile.open(fragmentSourcePath);

		//string stream objects 
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		//read entire file contents into stream objects with rdbuf()
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//close file handlers
		vShaderFile.close();
		fShaderFile.close();

		//convert stream data to GLchar array
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	//still converting that stream data (not a string) to GLchar* (c-string)
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	
	//debug
	//std::cout << "Vertex Shader Source:\n" << vShaderCode << "\n";
	//std::cout << "Fragment Shader Source:\n" << fShaderCode << "\n";
	
	//compile/link shaders
	GLuint vertex;
	GLuint fragment;
	GLint success;
	GLchar infoLog[512];

	//vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
		infoLog << std::endl;
	}

	//fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
		infoLog << std::endl;
	}

	//shader program 
	this->m_Program = glCreateProgram();
	glAttachShader(this->m_Program, vertex);
	glAttachShader(this->m_Program, fragment);
	glLinkProgram(this->m_Program);

	glGetProgramiv(this->m_Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->m_Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" <<
		infoLog << std::endl;
	}

	//delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath, const GLchar* geometrySourcePath)
{
	//debug
	std::cout << "Shader Object Constructed!" << std::endl;

	//retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;

	//ensures ifstream objects can throw exceptions 
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//open files
		vShaderFile.open(vertexSourcePath);
		fShaderFile.open(fragmentSourcePath);
		gShaderFile.open(geometrySourcePath);

		//string stream objects 
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;
		std::stringstream gShaderStream;

		//read entire file contents into stream objects with rdbuf()
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();

		//close file handlers
		vShaderFile.close();
		fShaderFile.close();
		gShaderFile.close();

		//convert stream data to GLchar array
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		geometryCode = gShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	//still converting that stream data (not a string) to GLchar* (c-string)
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	const GLchar* gShaderCode = geometryCode.c_str();

	//debug
	//std::cout << "Vertex Shader Source:\n" << vShaderCode << "\n";
	//std::cout << "Fragment Shader Source:\n" << fShaderCode << "\n";
	//std::cout << "Geometry Shader Source:\n" << gShaderCode << "\n";

	//compile/link shaders
	GLuint vertex;
	GLuint fragment;
	GLuint geometry;
	GLint success;
	GLchar infoLog[512];

	//vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	//fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	// Geometry
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, NULL);
	glCompileShader(geometry);

	glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(geometry, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	}

	//shader program 
	this->m_Program = glCreateProgram();
	glAttachShader(this->m_Program, vertex);
	glAttachShader(this->m_Program, fragment);
	glAttachShader(this->m_Program, geometry);
	glLinkProgram(this->m_Program);

	glGetProgramiv(this->m_Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->m_Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" <<
			infoLog << std::endl;
	}

	//delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);
}

//use the program
void Shader::Use()
{
	glUseProgram(this->m_Program);
}

//set texture int
void Shader::setInt(const char* f_name, int val)
{
	Use();
	glUniform1i(glGetUniformLocation(this->m_Program, f_name), val);
}

void Shader::setFloat(const char* f_name, float val)
{
	Use();
	glUniform1f(glGetUniformLocation(this->m_Program, f_name), val);
}

void Shader::setVec2(const char* f_name, glm::vec2 vectors)
{
	Use();
	glUniform2fv(glGetUniformLocation(this->m_Program, f_name), 1, glm::value_ptr(vectors));
}

void Shader::setVec3(const char *f_name, glm::vec3 vectors)
{
	Use();
	glUniform3fv(glGetUniformLocation(this->m_Program, f_name), 1, glm::value_ptr(vectors));
}

void Shader::setVec4(const char* f_name, glm::vec4 vectors)
{
	Use();
	glUniform4fv(glGetUniformLocation(this->m_Program, f_name), 1, glm::value_ptr(vectors));
}

void Shader::setMat3(const char* f_name, glm::mat3 matrix)
{
	Use(); // Don't forget to merge this
	glUniformMatrix3fv(glGetUniformLocation(this->m_Program, f_name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setMat4(const char *f_name, glm::mat4 matrix)
{
	Use(); // Don't forget to merge this
	glUniformMatrix4fv(glGetUniformLocation(this->m_Program, f_name), 1, GL_FALSE, glm::value_ptr(matrix));
}
