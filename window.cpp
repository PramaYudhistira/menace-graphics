#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); //makes the window's context current

    // Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {//i.e. glewInit failed
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    while (!glfwWindowShouldClose(window)) {
        // Render here

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}