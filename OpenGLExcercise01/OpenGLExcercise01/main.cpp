/*
* OpenGL core lib: ���Ŀ�gl��ʵ�ÿ�glu��������aux��ʹ�ù��߿�glut�����ڿ�glx��agl��wgl����չ������
* gl�Ǻ��ģ�glu�Ƕ�gl�Ĳ��ַ�װ
* glx��agl��wgl����Բ�ͬ����ϵͳ�ĺ���
* glut��Ϊ��ƽ̨��OpenGL����Ĺ��߰�����aux����ǿ��aux�ܴ�̶����Ѿ���glut��ȡ��
* ��չ��������Ӳ������Ϊ��ʵ��Ӳ����������OpenGL����չ���ƿ����ĺ���
* 
* ###
* gult��
* ��Ҫ�������ڲ������������ڳ�ʼ�������ڴ�С������λ�õȺ�����
* �ص���������Ӧˢ����Ϣ��������Ϣ�������Ϣ����ʱ��������
* �������ӵ���ά���壻
* �˵��������������к���
* gult��Ӧ�Ŀ�Դʵ����freegult
* 
* ###
* glew��The OpenGL Extension Wrangler Library
* glut����freeglut��1.0�Ļ����������ܣ�
* glew��2.0֮���һ�����ߺ���
* 
* ֧����ຯ���⣬ֻ��Ҫ����һ��glew.h��ͷ�ļ�������ʹ��gl,glu,glext,wgl,glx��ȫ������
*
* ###
* glfw
* glut�������͸Ľ���������ʾ���ںͲ�׽�����¼���API   --> glut --> freeglut --> glfw
* 
* 
* ###
* glad: new glew
* 
* 
* ###
* In Short
* ���ڹ���
*	�ϲ�Ʒ��glut/freeglut
*	���Ʒ��glfw
* 
* �������أ�
*	�ϲ�Ʒ��glew
*	���Ʒ��glad
* 
* ͨ�������ֻ������ã�
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
















