#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#version 330 core


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


// vertex data 

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};
	

// creating a vbo 

unsigned int VBO;
glGenBuffer(1, &VBO); // generating a VBO using the function in the library

// binding different types of buffers in the glBuffer that we created 
glBindBuffer(GL_ARRAY_BUFFER, VBO);
// -> current buffer is VBO here 

glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// setting the layout for the vertex shader

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// creating the fragment layout 

out vec4 FragColor;

int main (){

	// creating the vertex shader 
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);


	//fragment shader object for them color 
	
	FragColor = vec4(0.0f,0.0f,0.0f,0.0f); // i think this is white 


	// creating fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);


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


	
	// shader source object and compiling the shader 
	
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// checking for compilation errors 
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(vertexShader, 512 , NULL, infoLog);
		cout << "error : " << infoLog << endl;
	}
	

	// compiling the fragment shader source
	glShaderSource(fragmentShader, 1 , &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	
	// checking for compilation errors 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	char infoLog2[512];
	if (!success){
		glGetShaderInfoLog(vertexShader, 512 , NULL , infoLog2);
		cout << "error : " << infoLog2<< endl;
	}
	// window termination
	glfwTerminate();
	return 0;

}
