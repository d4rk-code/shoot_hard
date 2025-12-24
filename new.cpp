#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

// creating a callback function 
void resize(GLFWwindow *window , int width , int height)
{
	glViewport(0,0,width,height);
}

void exitloop(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
}

// layout for shaders
const char *vertexShaderSource = "#version 330 core\n" // vertex
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";


const char *fragmentShaderSource = "#version 330 core\n" //fragment
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";

int main (){
	// setting up GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// setting up window 
	GLFWwindow *window = glfwCreateWindow(800,600,"game", NULL , NULL);

	// error check
	if (window == NULL){
		glfwTerminate();
		return -1;
	}

	// starting a window
	glfwMakeContextCurrent(window);

	// setting up GLAD 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Glad error" << endl;
		return -1;
	}
	
	// window scaling 
	glViewport(0,0,800,600);

	// using the callback function for random resizing when needed
	glfwSetFramebufferSizeCallback(window, resize);

	// creating shaders 
	// vertex shader
	unsigned int vShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	const char *vsource[] = { vertexShaderSource };
	glShaderSource( vShader ,1 , vsource , NULL);
	glCompileShader(vShader);
	
	// fragment shader
	unsigned int fShader;
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fsource[] = { fragmentShaderSource };
	glShaderSource( fShader , 1 , fsource , NULL);
	glCompileShader(fShader);

	// creating shader programs and linking shader objects 
	unsigned int shaderprog;
	shaderprog = glCreateProgram();
	glAttachShader(shaderprog, vShader); // attaching vertex shader 
	glAttachShader(shaderprog, fShader); // attaching fragment shader
	glLinkProgram(shaderprog);

	// error handeling in compilation and linking 
	int success;
	char infolog[512];
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(vShader, 512 , NULL , infolog);
		cout << "some error occured while compiling the vertex shader!" << endl;
	}
	glGetShaderiv(fShader , GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(fShader, 512 , NULL , infolog);
		cout << "some error occured while compiling the fragment shader!" << endl;
	}
	glGetProgramiv(shaderprog, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(shaderprog , 512, NULL , infolog);
		cout << "some error occured while linking shader programs!" << endl;
	}

	// deleting the shaders after compilation 
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	// vertex data 
	float vertices[] = {
		0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	};

	// creating VBO and VAO
	unsigned int VBO , VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// binding VAO VBO  
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// vertex attrib pointer
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);  // did this to ensure didn't get any errors while linking others
	glBindVertexArray(0);

	// creating the main loop window 
	
	while (!glfwWindowShouldClose(window)){
		
		//input
		exitloop(window);
		
		// triangle
		glUseProgram(shaderprog);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0,3);

		// poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Termination 
	glfwTerminate();
	return 0;
}

