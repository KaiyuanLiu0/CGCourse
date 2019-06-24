//
// Created by KaiyuanLiu on 2019-06-24.
//

#ifndef GRAPHICS_TRIANGULAR_PRISM_H
#define GRAPHICS_TRIANGULAR_PRISM_H
#include "../src/shader.h"
const float prismVertices[] = {
        // positions          // normals    // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  -1.0f, 0.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  -1.0f, 0.0f,  1.0f,  0.0f,
        0.0f,  -0.5f, 0.366f,  0.0f,  -1.0f, 0.0f,  0.5f,  0.86f,

        -0.5f, 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  0.0f,  0.0f,
        0.5f, 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  1.0f,  0.0f,
        0.0f, 0.5f, 0.366f,  0.0f,  1.0f, 0.0f,  0.5f,  0.86f,

        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
        -0.5f, 0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, 0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        0.5f, 0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  -0.866f,  0.0f, 0.5f,  0.0f,  0.0f,
        0.0f,  -0.5f, 0.366f,  0.0f,  0.0f, 0.5f,  1.0f,  0.0f,
        -0.5f, 0.5f, -0.5f,  -0.866f,  0.0f, 0.5f,  0.0f,  1.0f,
        -0.5f, 0.5f, -0.5f,  -0.866f,  0.0f, 0.5f,  0.0f,  1.0f,
        0.0f,  0.5f, 0.366f,  -0.866f,  0.0f, 0.5f,  1.0f,  1.0f,
        0.0f,  -0.5f, 0.366f,  -0.866f,  0.0f, 0.5f,  1.0f,  0.0f,

        0.5f, -0.5f, -0.5f,  0.866f,  0.0f, 0.5f,  0.0f,  0.0f,
        0.0f,  -0.5f, 0.366f,  0.866f,  0.0f, 0.5f,  1.0f,  0.0f,
        0.5f, 0.5f, -0.5f,  0.866f,  0.0f, 0.5f,  0.0f,  1.0f,
        0.5f, 0.5f, -0.5f,  0.866f,  0.0f, 0.5f,  0.0f,  1.0f,
        0.0f,  0.5f, 0.366f,  0.866f,  0.0f, 0.5f,  1.0f,  1.0f,
        0.0f,  -0.5f, 0.366f,  0.866f,  0.0f, 0.5f,  1.0f,  0.0f,

};

class Prism {
public:
    Prism();
    void Draw(Shader& shader);
private:
    unsigned int VAO;
    unsigned int TextureID;
    const char* path = "../resources/block/wood.png";
    unsigned int LoadTexture();
};


#endif //GRAPHICS_TRIANGULAR_PRISM_H
