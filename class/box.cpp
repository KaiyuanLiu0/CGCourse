//
// Created by KaiyuanLiu on 2019-06-16.
//

#include "box.h"
Box::Box()
{
    box.SetType(BOX);
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Box::Box(float x, float y, float z)
{
    box.SetType(BOX);
    this->x = x;
    this->y = y;
    this->z = z;
}

Box::Box(const Box& box)
{
    this->x = box.x;
    this->y = box.y;
    this->z = box.z;
}
void Box::Draw(Shader shader)
{
    box.Draw(shader);
}

void Box::SetPosition(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = 0;
}
void Box::MovePosition(float deltaX, float deltaY, float deltaZ)
{
    this->x += deltaX;
    this->y += deltaY;
    this->z += deltaZ;
}