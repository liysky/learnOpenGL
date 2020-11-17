#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main2()
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("pic.png", &width, &height, &nrChannels, 0);


	for (size_t i = 0; i < 50; i++)
	{
		std::cout << (int)data[i] << std::endl;
	}

	// free data 
	stbi_image_free(data);

	while (true)
	{

	}
}