//
// Created by KaiyuanLiu on 2019-06-15.
//

#include "map.h"
Map::Map()
{
    this->m_level_ = LEVEL1;
}

Map::Map(LEVEL level)
{
    this->m_level_ = level;
}

void Map::SetLevel(LEVEL level)
{
    this->m_level_ = level;
}

TYPE Map::GetType(int row, int col)
{
    return map[m_level_][row][col];
}