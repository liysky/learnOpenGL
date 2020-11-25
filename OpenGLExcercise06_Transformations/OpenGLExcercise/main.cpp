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
* ###
* glad: new glew
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
	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};

//0, 1, 2		0, 2, 3
unsigned int indices[] = { // ע��������0��ʼ! 
	0, 1, 2, // ��һ��������
	//1, 2, 3  // �ڶ���������
	2, 3, 0  // �ڶ���������
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






