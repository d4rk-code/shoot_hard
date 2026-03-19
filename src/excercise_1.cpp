#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

//shader source codes:
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n" 
    "}\n\0";


int main(){

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "q1", NULL, NULL);

	if (window == NULL){
		cout << "failed to create window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "failed GLAD" << endl;
		return -1;
	}

	// creating all shader programs
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexshader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexshader);

	GLuint fragmentshader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader1, 1, &fragmentShaderSource1, NULL);
	glCompileShader(fragmentshader1);

	GLuint fragmentshader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentshader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentshader2);

	GLuint shaderprogram1 = glCreateProgram();
	glAttachShader(shaderprogram1, vertexshader);
	glAttachShader(shaderprogram1, fragmentshader1);
	glLinkProgram(shaderprogram1);

	GLuint shaderprogram2 = glCreateProgram();
	glAttachShader(shaderprogram2, vertexshader);
	glAttachShader(shaderprogram2, fragmentshader2);
	glLinkProgram(shaderprogram2);

	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader1);
	glDeleteShader(fragmentshader2);

	GLfloat vertex1[] = {
		-1.0f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};
	GLfloat vertex2[] = {
		 0.0f, -0.5f, 0.0f,
		 1.0f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f
	};

	GLuint VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	//first triangle
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex1), vertex1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//second triangle
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex2), vertex2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	//render loop
	while(!glfwWindowShouldClose(window)){
		glUseProgram(shaderprogram1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderprogram2);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(shaderprogram1);
	glDeleteProgram(shaderprogram2);

	return 0;
}
