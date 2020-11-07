#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


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

		printf(vertexSource);
		printf(fragmentSource);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what();
	}

	
}
