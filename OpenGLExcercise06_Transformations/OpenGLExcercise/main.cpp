/*
* OpenGL core lib: 核心库gl，实用库glu，辅助库aux，使用工具库glut，窗口库glx、agl、wgl和拓展函数库
* gl是核心，glu是对gl的部分封装
* glx、agl、wgl是针对不同窗口系统的函数
* glut是为跨平台的OpenGL程序的工具包，比aux功能强大，aux很大程度上已经被glut库取代
* 拓展函数库是硬件厂商为了实现硬件更新利用OpenGL的拓展机制开发的函数
*
* ###
* gult：
* 主要包括窗口操作函数，窗口初始化、窗口大小、窗口位置等函数；
* 回调函数：相应刷新消息、键盘消息、鼠标消息、定时器函数；
* 创建复杂的三维物体；
* 菜单函数；程序运行函数
* gult对应的开源实现是freegult
*
* ###
* glew：The OpenGL Extension Wrangler Library
* glut或者freeglut是1.0的基本函数功能；
* glew是2.0之后的一个工具函数
*
* 支持许多函数库，只需要包含一个glew.h的头文件，就能使用gl,glu,glext,wgl,glx的全部函数
*
* ###
* glfw
* glut的升级和改进，用来显示窗口和捕捉窗口事件的API   --> glut --> freeglut --> glfw
*
* ###
* glad: new glew
*
* ###
* In Short
* 窗口管理：
*	老产品：glut/freeglut
*	替代品：glfw
*
* 函数加载：
*	老产品：glew
*	替代品：glad
*
* 通常的三种环境配置：
* * glfw + glew
* * glfw + glad
* * freeglut
*/



/*
*  Vertex Array Object : VAO
*  Vertex Buffer Object: VBO
*  Element Buffer Object: EBO or Index Buffer Object: IBO
*/

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>			 
#include <GLFW/glfw3.h>			 
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

float vertices[] = {
	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

//0, 1, 2		0, 2, 3
unsigned int indices[] = { // 注意索引从0开始! 
	0, 1, 2, // 第一个三角形
	//1, 2, 3  // 第二个三角形
	2, 3, 0  // 第二个三角形
};

int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//configure big version and minor version.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//use core_profile 
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//open GLFW Window
	//create a window object, which will required by most of other functions of GLFW.
	GLFWwindow* window = glfwCreateWindow(800, 600, "myDemo", NULL, NULL);
	if (window == NULL)
	{
		cout << "Open window failed" << endl;
		glfwTerminate();
		return -1;
	}
	// tell GLFW to make the context of our window now created as main context on the currrent thread.
	glfwMakeContextCurrent(window);


	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "Init glew failed";
		glfwTerminate();
		return -1;
	}
	// the first two parameters set location of the lower left corner of the window 
	//while the third and fourth set the width and height of the rendering window in pixels. 	
	glViewport(0, 0, 800, 600);
	//glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);			// draw line of triangle
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// draw fill
	//glCullFace(GL_BACK);
	//glCullFace(GL_FRONT);

	// shader create after glew init
	Shader* myShader = new Shader("..\\Shader\\vertexSource.txt", "..\\Shader\\fragmentSource.txt");

	// vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO); // 1 represent one vertex;
	glBindVertexArray(VAO);

	//vertex buffer object 
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// targeted to copy user-defined data into the currently bound buffer			
	// copy vertices data into GPU bound buffer
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


/*
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// create shader program and link it
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
*/

	// tell OpenGL how it should interpret the vertex data
	// 0: start location, which we specified the location of the position vertex attribute in vertex shader
	// 3: every vertex attribute is a vec3 
	// GL_FALSE: normalize the data? no
	// fifth: stride, space between consecutive vertex attribute
	// offset of where the position data begins in the buffer
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//  enable the vertex attribute
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(7);

	// set texture data point
	// enable the data of the pointer belong to vertex property with index 8
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(8);

	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);
	//activate the index of texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexBufferA);

	// set the width height nrchannel of the image readed from texture director
	int width, height, nrChannel;
	// because the y-axis of openGl is inversed with it in stb_image.h
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("..\\Texture\\container.jpg", &width, &height, & nrChannel, 0);
	if (data) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image failed." << endl;
	}
	stbi_image_free(data);
	
	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TexBufferB);

	unsigned char* data2 = stbi_load("..\\Texture\\awesomeface.png", &width, &height, &nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load imagedata2 failed." << endl;
	}
	stbi_image_free(data2);

	// calculate our transformation matrix here.
	//trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	//glfwWindowsShouldClose function checks if GLFW is asked to be closed or not?
	//if true: close the loop blender
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans,55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//trans = glm::rotate(trans,(float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
		std::cout<<	((float)glfwGetTime())<<std::endl;
		// scale translate 
		//trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));																		
		// rotation translate matrix
		//trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		// position translate matrix seted.
		//trans = glm::translate(trans, glm::vec3(-0.0001f, 0.0f, 0.0f));

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/*
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		*/

		myShader->use();
		// get texture uniform location
		glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 3);
		
		// set tranform data to be used in ..\\Shader\\vertexSource.txt
		glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));


		//glDrawArrays(GL_TRIANGLES, 0, 3);
		// -- draw triangle number is 3 while duadrangle is 6
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//swap the buffer with screen
		glfwSwapBuffers(window);
		//checks if any events are triggered (keyboard input or mouse) and call corresponding function.
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}






