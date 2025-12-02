#include <iostream>
#include <GLFW/glfw3.h>
#include <vectors>

using namespace std;

//creating a callback function for resizing

void callback_size(GLFWwindow *window,int width,int height){
	glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main (){

	//initialize glfw
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//creating a window 
	
	GLFWwindow *window = glfwCreateWindow(800,600,"game", NULL , NULL);
	
	// error check
	
	if (window == NULL){
		glfwTerminate();
		return -1;
	}

	// glad initialization so that the function pointers are matching with the proc address i.e. working for different systems 
/*
	gladLoadGL();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Glad messed up!" << endl;
		return -1;
	}
*/
	// glviewport -> for dimensioning of the window
	glViewport(0,0,800,800); // glViewport(lower_left_x , lower_left_y , width , height)
	
	// callback for random resizing
	glfwSetFramebufferSizeCallback(window, callback_size);
	
	// starting a window
	
	glfwMakeContextCurrent(window);

	// creating a loop window
	
	while(!glfwWindowShouldClose(window)){

		// input
		processInput(window);
	
		// rendering 

		// poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// window termination
	glfwTerminate();
	return 0;
}
