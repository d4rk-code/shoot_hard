#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void resize_callback(GLFWwindow* window, int height, int width);
void input(GLFWwindow* window);
float changecolor(GLFWwindow* window,float color);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 change;\n"
    "void main()\n"
    "{\n"
    "   FragColor = change;\n"
    "}\n\0";

// create vertex and fragment shader sources , create shaders , create shader programs , create vbo vao , draw triangle

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
		// first triangle
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left 
				     // second triangle
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f
	};

	//creating vbo and vao
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

		// doing some key bs 
		float color = 1.0f;
		int location = glGetUniformLocation(shaderprogram, "change");
		
		glUniform4f(location, 1.0f, changecolor(window, color), 0.0f, 1.0f);


		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
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

float changecolor(GLFWwindow* window,float color){
	if(glfwGetKey(window,GLFW_KEY_G) == GLFW_PRESS)
		color = 0.5f;
	return color;
}
