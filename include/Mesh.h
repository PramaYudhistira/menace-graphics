#pragma once

#include <glad/glad.h>
#include <vector>

class Mesh {
    public: 
        Mesh(std::vector<float> vertices, std::size_t size);
        ~Mesh();
        void draw();

    private:
        unsigned int VAO_, VBO_;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
};
