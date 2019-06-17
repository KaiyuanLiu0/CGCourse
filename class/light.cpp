//
// Created by KaiyuanLiu on 2019-06-17.
//

#include "light.h"
Light::Light()
{
    SetUpLight();
}

void Light::SetPosition(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Light::Draw(Shader &shader)
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Light::SetUpLight()
{
    // temporarily using a cube
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(block_vertices), block_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}