#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main(){
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "lmao", NULL, NULL);

	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	while(!glfwWindowShouldClose(window)){
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
