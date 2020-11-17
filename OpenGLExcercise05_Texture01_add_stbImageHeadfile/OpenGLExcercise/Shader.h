#pragma once
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;

	// const: write once
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;	//Shader program ID
	void use();			//use the shader to call CPU input shader into program
	
private:
	void checkCompileErrors(unsigned int ID, std::string type);

};
