#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader/shaderClass.h>

#include <iostream>

using namespace std;

void resize_callback(GLFWwindow* window, int height, int width);
void input(GLFWwindow* window);


int main(){
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "lmao", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//calling our shader constructor
	Shader example("../shaders/vertex.shad", "../shaders/fragment.shad");

	//vertex location data for the triangle (normalized coordinates)

	float vertices[] = {
		 // positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	}; 

	//creating vbo and vao
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// for positions 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// for colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
	
	//render loop
	while(!glfwWindowShouldClose(window)){
		input(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		example.use();

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES,0,3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void resize_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0,width,height);
}

void input(GLFWwindow* window){
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
