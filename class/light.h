//
// Created by KaiyuanLiu on 2019-06-17.
//

#ifndef GRAPHICS_LIGHT_H
#define GRAPHICS_LIGHT_H
#include "../aux/shader.h"
#include "block.h"
class Light {
public:
    Light();
    void SetPosition(float x = 0, float y = 0, float z = 0);
    void Draw(Shader& shader);
private:
    float x;
    float y;
    float z;
    unsigned int VAO;
    void SetUpLight();
};


#endif //GRAPHICS_LIGHT_H
