/*
TODO: Implement Mesh class
*/
#pragma once
#include "Mesh.h"

Mesh::Mesh(std::vector<float> vertices, std::size_t size) {
    this->vertices = vertices;
    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}
