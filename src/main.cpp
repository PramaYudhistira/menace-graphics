#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


//vertex shader
//TODO: implement shader class to handle shader compilation and linking
const char* vertexShaderSource = "#version 330 core\n"
                                    "layout (location = 0) in vec3 aPos;\n"
                                    "void main()\n"
                                    "{\n"
                                    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                    "}\0";

//fragment shader
const char* fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";


//adjust viewport size when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInputEscape(GLFWwindow* window)
{
    //if escape key is pressed, close window, refer to glfw documentation, or the glfw3.h file
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    //--------------------------------------------------INITIALIZATION----------------------------------------------------------------------
    //initialize GLFW library
    if (!glfwInit()) {
        return -1;
    }
    std::cout << "Hello, World!" << std::endl;

    //sets version of openGL to 3.3
    //set openGL profile to core profile, bear this in mind if you decide to gitignore include directory
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //get window size based on native resolution
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    //Create window
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Menace Graphics", NULL, NULL);
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

    //set viewport size
    glViewport(0, 0, mode->width, mode->height);

    //when window is resized, adjust viewport size accordingly using callback function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //--------------------------------------------------END OF INITIALIZATION---------------------------------------------------------------

    //TESTING TRIANGLE 
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    //--------------------------------------------------SETTING UP SHADERS----------------------------------------------------------------------
    /**
     * note: shaders are written in GLSL, and stored in the VRAM, and are compiled and linked to GPU
     * I will make a shader class to handle this, for now i write here to visualize graphics pipeline
     
    */

    //creates a shader in the VRAM, returns the ID of the shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //places the shader code in the shader object in the VRAM
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    //compiles the shader source code stored in the shader object in the VRAM 
    glCompileShader(vertexShader);

    //check if the shader compilation was successful
    int success;
    char infoLog[512]; 
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR: VERTEX SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //fragment shader, same routine
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //SHADER PROGRAM
    GLuint shaderProgram = glCreateProgram();

    //attach shaders to the program 
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //link the program
    glLinkProgram(shaderProgram);

    //delete after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER PROGRAM LINKING FAILED\n" << infoLog << std::endl;
    } else {
        std::cout << "SHADER PROGRAM LINKING SUCCESSFUL" << std::endl;
    }

    //the next rendering loop will use this shader program, i.e. shaders on the VRAM
    glUseProgram(shaderProgram);

    //--------------------------------------------------END OF SETTING UP SHADERS---------------------------------------------------------------

    //--------------------------------------------------SETTING UP VERTEX ATTRIBUTES AND BUFFERS----------------------------------------------------------------------

    GLuint VBO;
    GLuint VAO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //actually storing the buffer data in the VRAM

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);


    //render loop
    while(!glfwWindowShouldClose(window)) {

        //process input 
        processInputEscape(window);

        //rendering commands
        glClearColor(0.2f, 0.9f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //swap buffers
        glfwSwapBuffers(window);

        //process events 
        glfwPollEvents();

    }

    glfwTerminate();//clean up resources

    return 0;
}
