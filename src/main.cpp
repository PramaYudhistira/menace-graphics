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
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    //--------------------------------------------------SETTING UP BUFFERS----------------------------------------------------------------------
    //think of the name, vertex buffer objects, basically helps you store vertex data in the GPU's memory
    unsigned int VBO;

    //i bet segfault is here
    std::cout << "calling genBuffers" << std::endl;
    //basically, creates 1 buffer object, and store this buffer object's ID in the VBO variable
    glGenBuffers(1, &VBO); //BTS: allocates space in the VRAM and returns the ID to reference the space
    std::cout << "VBO has been initialized and generated: " << VBO << std::endl;

    //technically, you can have multiple buffers, and that the VBO variable essentially should be an array of IDs, so if we wanted say, 
    //10 buffers, we would have to create a variable pointer to an array of ids

    //for example: 
    /*
    unsigned int buffers[3];
    glGenBuffers(3, buffers);
    */

    //bind the buffer we made to the GL_ARRAY_BUFFER target, which is essentially the vertex buffer  
    //the first parameter is essentially to optimize VRAM
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //BTS: binds the VBO variable to the GL_ARRAY_BUFFER which is the target

        //this basically kicks off the pipeline (but nothing is drawn yet)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //BTS: Copies vertex data into buffer's memory

    //there is GL_STATIC_DRAW: set once but used many times, so not change after being uploaded
    //GL_DYNAMIC_DRAW: upload many times but used many times, so changed frequently but updated mostly by CPUs, example is animations
    //GL_Stream_DRAW: set once and used a few times

    //for example, if we have a buffer and you think data changes all the time we would need
    //to use GL_DYNAMIC_DRAW, where the GPU will place data in memory that allows for faster writes

    //--------------------------------------------------END OF SETTING UP BUFFERS---------------------------------------------------------------


    //--------------------------------------------------SETTING UP SHADERS----------------------------------------------------------------------
    /**
     * note: shaders are written in GLSL, and stored in the VRAM, and are compiled and linked to GPU
     * I will make a shader class to handle this, for now i write here to visualize graphics pipeline
     
    */

    //vertex shader
    unsigned int vertexShader;

    //creates a shader in the VRAM, returns the ID of the shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

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

    //fragment shader
    unsigned int fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: FRAGMENT SHADER COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //SHADER PROGRAM

    unsigned int shaderProgram;

    //create program, store in VRAM, returns the id of program
    shaderProgram = glCreateProgram();

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

    //--------------------------------------------------SETTING UP VERTEX ATTRIBUTES----------------------------------------------------------------------

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
