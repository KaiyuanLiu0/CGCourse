//
// Created by KaiyuanLiu on 2019-06-17.
//

#ifndef GRAPHICS_PLANE_H
#define GRAPHICS_PLANE_H
#include "../src/shader.h"
#include "../src/stb_image.h"
const float planeVertices[] = {
        // positions            // normals         // texcoords
        500.0f, -0.5f,  500.0f,  0.0f, 1.0f, 0.0f,  500.0f,  0.0f,
        -500.0f, -0.5f,  500.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -500.0f, -0.5f, -500.0f,  0.0f, 1.0f, 0.0f,   0.0f, 500.0f,

        500.0f, -0.5f,  500.0f,  0.0f, 1.0f, 0.0f,  500.0f,  0.0f,
        -500.0f, -0.5f, -500.0f,  0.0f, 1.0f, 0.0f,   0.0f, 500.0f,
        500.0f, -0.5f, -500.0f,  0.0f, 1.0f, 0.0f,  500.0f, 500.0f
};

class Plane {
public:
    Plane();
    void Draw(Shader& shader);
private:
    const char* path = "../resources/block/marble.jpg";
    unsigned int VAO;
    unsigned int Texture;
    unsigned int LoadTexture(char const* path);
};


#endif //GRAPHICS_PLANE_H
