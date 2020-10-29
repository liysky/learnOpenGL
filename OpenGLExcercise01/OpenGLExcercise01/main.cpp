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
* 
* ###
* glad: new glew
* 
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
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>		
#include <GLFW/glfw3.h>
using namespace std;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//configure big version and minor version.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//use core_profile 
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	//OPen GLFW Window
	//create a window object, which will required by most of other functions of GLFW.
	GLFWwindow* window = glfwCreateWindow(800, 600, "Mywindow", NULL, NULL);
	if (window == NULL)
	{
		cout << "Open window failed" << endl;
		glfwTerminate();
		return -1;
	}
	// tell GLFW to make the context of our window now created as main context on the currrent thread.
	glfwMakeContextCurrent(window);	

	/*
	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
	}
	*/
	//Init GLEW

	glewExperimental = true;
	if (glewInit()!=GLEW_OK)
	{
		cout << "Init glew failed";
		glfwTerminate();
		return -1;
	}
	// the first two parameters set location of the lower left corner of the window 
	//while the third and fourth set the width and height of the rendering window in pixels. 	
	glViewport(0, 0, 800, 600);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();		//checks if any events are triggered (keyboard input or mouse) and call corresponding function.
	}

	glfwTerminate();

	return 0;
}
















