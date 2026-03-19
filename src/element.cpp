#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void resize_callback(GLFWwindow* window, int height, int width);
void input(GLFWwindow* window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

// create vertex and fragment shader sources , create shaders , create shader programs , create vbo vao , draw triangle
// using element buffer objects

int main(){
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "lmao", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//creating a vertex shader and sourcing n compiling it
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader,1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);

	//doing the same for fragment shader
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader,1 , &fragmentShaderSource,NULL);
	glCompileShader(fragmentshader);

	//creating a shader program
	GLuint shaderprogram = glCreateProgram();
	glAttachShader(shaderprogram, vertexshader);
	glAttachShader(shaderprogram, fragmentshader);
	glLinkProgram(shaderprogram);

	//deleting shaders after using them
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	//vertex location data for the triangle (normalized coordinates)
	GLfloat vertices[] = {
		//creating a squre
		-0.5f , -0.5f , 0.0f, //bottom left
		 0.5f , -0.5f , 0.0f, //bottom right
		-0.5f ,  0.5f , 0.0f, //top left
		 0.5f ,  0.5f , 0.0f  //top right
	};
	GLuint indices[] = {
		0,1,2,
		1,2,3
	};
	//creating vbo and vao
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	//render loop
	while(!glfwWindowShouldClose(window)){
		input(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderprogram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT,0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderprogram);

	glfwTerminate();
	return 0;
}

void resize_callback(GLFWwindow* window, int height, int width){
	glViewport(0,0,height,width);
}

void input(GLFWwindow* window){
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
