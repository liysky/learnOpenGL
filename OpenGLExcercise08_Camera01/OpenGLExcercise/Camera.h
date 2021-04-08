// prevent compile a head file twice
// can be replaced by: 
/*
*  #ifndef CAMERA_H
*  #define CAMERA_H
*  #endif
*/
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
};


