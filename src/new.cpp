#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

// creating our first window

void resize_callback(GLFWwindow* window,int width , int height);
void input(GLFWwindow* window);

int main(){

	// initializing glfw3
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version set to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version set to 3 to avoid undefined reference errors
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // explicitly using the core profile


	// creating a window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // creating current thread context
	glfwSetFramebufferSizeCallback(window, resize_callback); //telling openGL to use the resize_callback function when the window is resized

	// initializing GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}  

	while (!glfwWindowShouldClose(window)){
		//input function
		input(window);

		//rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render loop
		glfwSwapBuffers(window); //stores color buffer for the window
		glfwPollEvents(); //listens for triggers
	}

	glfwTerminate();
	return 0;

}

void resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height); // glviewport helps us create a render window where can do stuff from openGL
}

void input(GLFWwindow* window)
{
	// basically when esc is pressed the window will close
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		  glfwSetWindowShouldClose(window, true);
}
