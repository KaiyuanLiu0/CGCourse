//
// Created by KaiyuanLiu on 2019-06-14.
//

#ifndef GRAPHICS_BLOCK_H
#define GRAPHICS_BLOCK_H
#include <string>
#include <vector>
#include "../aux/shader.h"
#include "type.h"

const float block_vertices[] = {
        // Positions          // Normals           // Texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, -1.0f, -1.0f, -1.0f, // back
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, -1.0f,  1.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, -1.0f, -1.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, -1.0f, -1.0f,  1.0f, // front
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, -1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, -1.0f,  1.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, -1.0f, -1.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,	 1.0f, // left
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, -1.0f, -1.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, -1.0f, -1.0f, -1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, -1.0f, -1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, // right
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, -1.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, -1.0f, -1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, -1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, -1.0f, -1.0f, -1.0f, // bottom
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, -1.0f, -1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, -1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, -1.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, -1.0f, -1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, -1.0f, -1.0f, -1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  1.0f, -1.0f, // up
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, -1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, -1.0f,  1.0f, -1.0f,
};

const std::string path[NUMOFTYPE][6] = {
        // positive x                     // negative x                   // positive y
        // negative y                     // positive z                   // negative z
        {}, // EMPTY
        {}, // plain
        {"../resources/block/grass0.png", "../resources/block/grass0.png", "../resources/block/grass1.jpg", //WALL
                "../resources/block/earth.bmp",  "../resources/block/grass0.png", "../resources/block/grass0.png"},
        {"../resources/block/wood0.bmp",  "../resources/block/wood0.bmp",  "../resources/block/wood1.bmp", // BOX
                "../resources/block/wood0.bmp",  "../resources/block/wood0.bmp",  "../resources/block/wood0.bmp"},
        {}, // PLAYER
        {"../resources/block/earth.bmp", "../resources/block/earth.bmp", "../resources/block/wood0.bmp",
                "../resources/block/earth.bmp", "../resources/block/earth.bmp", "../resources/block/earth.bmp"}, // END
        {"../resources/block/earth.bmp", "../resources/block/earth.bmp", "../resources/block/earth.bmp", // BASE
         "../resources/block/earth.bmp", "../resources/block/earth.bmp", "../resources/block/earth.bmp"}
};

class Block {
public:
    Block();
    Block(TYPE type);
    Block(Block& block);
    // set the type of block
    void SetType(TYPE type);
    TYPE GetType();
    // draw with given shader
    void Draw(Shader shader);
private:
    TYPE  m_type_ = WALL;
    unsigned int texture_id_;
    unsigned int VAO, VBO;
    static unsigned int LoadTexture(TYPE type);
    void SetUpBlock();
};

#endif //GRAPHICS_BLOCK_H
