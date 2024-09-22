#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

//adjust viewport size when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    //if escape key is pressed, close window, refer to glfw documentation, or the glfw3.h file
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    //initialize GLFW library
    if (!glfwInit()) {
        return -1;
    }

    //hints for the window
    //sets version of openGL to 4.2
    //set openGL profile to core profile, bear this in mind if you decide to gitignore include directory
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    int windowWidth = 800;
    int windowHeight = 600;

    

    //Create window
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Menace Graphics", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //make window's context current, i.e. use the `window` variable's settings and resources for rendering
    glfwMakeContextCurrent(window);

    //initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //telling openGL the size of the rendering window, the window which has the context
    //first 2 arguments represent lower left corner of window, last 2 represent width and height
    //viewport is the transformation from normalized device coordinates to screen coordinates
    glViewport(0, 0, windowWidth, windowHeight);


    //when window is resized, adjust viewport size accordingly using callback function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //render loop
    while(!glfwWindowShouldClose(window)) {

        //process input
        processInput(window);

        //rendering commands

        

        //process events 
        glfwPollEvents();

        //swap buffers, front buffer is displayed, back buffer is being rendered
        glfwSwapBuffers(window);//computer graphics technique to eliminate flickering
    }

    glfwTerminate();//clean up resources

    return 0;
}