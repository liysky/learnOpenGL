#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#define GLEW_STATIC
#include <GL/glew.h>			 
#include <GLFW/glfw3.h>		

/*
* Read File Stream:
* CPU <== char* <== string <== stringBuffer <== FileBuffer <== diskFile
*/

Shader::Shader(const char* vertexPath, const char* fragmentPath) 
{
	// define fileBuffer    ---- this is fileBuffer
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	// define stringBuffer  ---- this is stringBuffer
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	// ensure ifstream objects can throw exception
	// failbit: Logical error on i/o operation
	// badbit: Read/writing error on i/o operation
	// while failbit & badbit, eofbit means: End-of-File reached on input operation
	vertexFile.exceptions( std::ifstream::failbit || std::ifstream::badbit );
	fragmentFile.exceptions( std::ifstream::failbit || std::ifstream::badbit );

	// judge if open Error
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open() )
		{
			throw std::exception("open file error");
		}

		// input fileBuffer into stringBuffer
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		// convert stream into string
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		// stringBuffer to string
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();
		
		// shader ID, unsigned int vertex, fragment
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		// compile shader into bin
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//shaderProgram is a multishader linked and compiled and returned 
		ID = glCreateProgram();
		//attach vertex and fragment into ID to link
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		// when linked shader into program, delete it  
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	
}

// --- use shader program ID
void Shader::use() {
	glUseProgram(ID);
}

// ---check compile errors
void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char infolog[512];

	/*
	*  type != program, then check shader
	*  ID, 
	*  check glcompilestatus
	*  return status info to success
	*/
	if (type != "PROGEAM")
	{
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infolog);
			std::cout << "shader compile error: " << infolog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infolog);
			std::cout << "program linking error: " << infolog << std::endl;
		}
	}
}
