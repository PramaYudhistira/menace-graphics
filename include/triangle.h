#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
//TODOL same thing as triangle.cpp

//VBO stores vertex data in GPU memory
void setupTriangle(unsigned int VAO, unsigned int VBO);

void drawTriangle(unsigned int VAO);


#endif