//
// Created by KaiyuanLiu on 2019-06-15.
//

#include "map.h"
Map::Map()
{
    this->level = LEVEL1;
}

Map::Map(LEVEL level)
{
    this->level = level;
}

void Map::SetLevel(LEVEL level)
{
    this->level = level;
}

TYPE Map::GetType(int row, int col)
{
    return map[level][row][col];
}