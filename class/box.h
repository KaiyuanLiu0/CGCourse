//
// Created by KaiyuanLiu on 2019-06-16.
//

#ifndef GRAPHICS_BOX_H
#define GRAPHICS_BOX_H
#include "block.h"
#include "type.h"
class Box {
public:
    Box();
    Box(float x, float y, float z = 0);
    Box(const Box& box);
    void Draw(Shader shader);
    void SetPosition(float x, float y, float z = 0);
    void MovePosition(float deltaX, float deltaY, float deltaZ = 0);
    float x;
    float y;
    float z;
private:
    Block box;
};


#endif //GRAPHICS_BOX_H
