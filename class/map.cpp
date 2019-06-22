//
// Created by KaiyuanLiu on 2019-06-15.
//

#include "map.h"
#include "maze.h"
extern unsigned int Maze[MAZE_LIMIT][MAZE_LIMIT];
Map::Map()
{
    this->m_level_ = LEVEL1;
    map_limit = (m_level_ + 1) * LEVEL_SEP * 2 + 1;
    SetUpMap();
}

Map::Map(LEVEL level)
{
    this->m_level_ = level;
    map_limit = (m_level_ + 1) * LEVEL_SEP * 2 + 1;
    SetUpMap();
}

void Map::SetLevel(LEVEL level)
{
    this->m_level_ = level;
    map_limit = (m_level_ + 1) * LEVEL_SEP * 2 + 1;
    delete [] map;
    SetUpMap();
}

TYPE Map::GetType(int row, int col)
{
    return map[row * (2 * (m_level_ + 1) * LEVEL_SEP + 1) + col];
}

int Map::GetLimit()
{
    return map_limit;
}
void Map::SetUpMap()
{
    int maze_limit = (m_level_ + 1) * LEVEL_SEP;
    struct Position start;
    start.row = 5;
    start.col = 5;
    MazeGenerator(maze_limit, start.row, start.col);
    map = new TYPE[(maze_limit * 2 + 1) * (maze_limit * 2 + 1)];
    int idx = 0;
    for (int i = 0; i < maze_limit; ++i)
    {
        for (int j = 0; j < maze_limit; ++j)
        {
            map[idx++] = WALL;
            if (!(Maze[i][j] & NORTH)) map[idx++] = WALL; // 1 for PLAIN 0 for wall
            else map[idx++] = PLAIN;
        }
        map[idx++] = WALL;
        for (int j = 0; j < maze_limit; ++j)
        {
            if (!(Maze[i][j] & WEST)) map[idx++] = WALL;
            else map[idx++] = PLAIN;
            map[idx++] = PLAIN;
        }
        map[idx++] = WALL;
    }
    for (int i = 0; i < maze_limit * 2 + 1; ++i) map[idx++] = WALL;
    maze_limit = (maze_limit * 2 + 1);
    int center = maze_limit * maze_limit / 2;
    map[center - 2 * maze_limit - 2] = PLAIN;
    map[center - 2 * maze_limit - 1] = PLAIN;
    map[center - 2 * maze_limit] = PLAIN;
    map[center - 2 * maze_limit + 1] = PLAIN;
    map[center - 2 * maze_limit + 2] = PLAIN;
    map[center - maze_limit - 2] = PLAIN;
    map[center - maze_limit - 1] = PLAIN;
    map[center - maze_limit] = PLAIN;
    map[center - maze_limit + 1] = PLAIN;
    map[center - maze_limit + 2] = PLAIN;
    map[center - 2] = PLAIN;
    map[center - 1] = PLAIN;
    map[center] = PLAIN;
    map[center + 1] = PLAIN;
    map[center + 2] = PLAIN;
    map[center + maze_limit - 2] = PLAIN;
    map[center + maze_limit - 1] = PLAIN;
    map[center + maze_limit] = PLAIN;
    map[center + maze_limit + 1] = PLAIN;
    map[center + maze_limit + 2] = PLAIN;
    map[center + 2 * maze_limit - 2] = PLAIN;
    map[center + 2 * maze_limit - 1] = PLAIN;
    map[center + 2 * maze_limit] = PLAIN;
    map[center + 2 * maze_limit + 1] = PLAIN;
    map[center + 2 * maze_limit + 2] = PLAIN;


}