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


};
