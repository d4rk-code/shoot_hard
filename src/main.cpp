#include <GLFW/glfw3.h>

int main() {
    // Initialize GLFW
    if (!glfwInit()) return -1;

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Rectangle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a rectangle using old-school OpenGL
        glBegin(GL_QUADS);  
            glColor3f(0.2f, 0.8f, 0.3f);  // green

            glVertex2f(-0.5f, -0.5f);     // bottom-left
            glVertex2f( 0.5f, -0.5f);     // bottom-right
            glVertex2f( 0.5f,  0.5f);     // top-right
            glVertex2f(-0.5f,  0.5f);     // top-left
        glEnd();

        // Swap buffers + poll input
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

