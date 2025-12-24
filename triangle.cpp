#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

// process input function for drawing the triangle 

// setting the layout for the vertex shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// creating the fragment layout 

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";

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

	
	// starting a window
	
	glfwMakeContextCurrent(window);

	// glad initialization so that the function pointers are matching with the proc address i.e. working for different systems 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "Glad messed up!" << endl;
		return -1;
	}
	// glviewport -> for dimensioning of the window
	glViewport(0,0,800,800); // glViewport(lower_left_x , lower_left_y , width , height)
	
	// callback for random resizing
	glfwSetFramebufferSizeCallback(window, callback_size);

	// creating a compiling the shader programs


	// creating the vertex shader 
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSources[] = { vertexShaderSource };
	glShaderSource(vertexShader, 1, vertexSources, NULL);
	glCompileShader(vertexShader);
	
	// checking for compilation errors 
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success){
		glGetShaderInfoLog(vertexShader, 512 , NULL, infoLog);
		cout << "error : " << infoLog << endl;
	}

	// creating fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// compiling the fragment shader source
	const char* fragmentSources[] = { fragmentShaderSource };
	glShaderSource(fragmentShader, 1, fragmentSources, NULL);

	glCompileShader(fragmentShader);
	
	// checking for compilation errors 
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	char infoLog2[512];
	if (!success){
		glGetShaderInfoLog(fragmentShader, 512 , NULL , infoLog2);
		cout << "error : " << infoLog2<< endl;
	}
	

	// creating the shader program and linking the shader objects
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	char infoLog3[512];
	if (!success){
		glGetProgramInfoLog(shaderProgram, 512 , NULL , infoLog3);
		cout << "error in linking" << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// vertex data 

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// creating a VBO and a VAO

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO); // generating a VBO using the function in the library
	glGenVertexArrays(1, &VAO); 

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// binding different types of buffers in the glBuffer that we created 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// -> current buffer is VBO here 

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// creating the vertex attribute pointer 
	glVertexAttribPointer(0,3, GL_FLOAT ,GL_FALSE ,3 * sizeof(float) , (void*)0);
	glEnableVertexAttribArray(0);


	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0); 


	// creating a loop window
	
	while(!glfwWindowShouldClose(window)){

		// input
		processInput(window);
	
		// rendering 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// drawing my triangle finally 
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0 , 3);


		// poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	// window termination
	glfwTerminate();
	return 0;
}
