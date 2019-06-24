//
// Created by KaiyuanLiu on 2019-06-20.
//
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "maze.h"
unsigned int Maze[MAZE_LIMIT][MAZE_LIMIT];

/* randomly generate a position in the maze */
static struct Position RandomPosition(int level)
{
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, level - 1);
    int randomRow = uniform_dist(e1);
    int randomCol = uniform_dist(e1);
    struct Position retPos { randomRow, randomCol };
    return retPos;
}

/* shuffle the direction list, used in dfs */
static void ShuffleList(std::vector<int> &iVec)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(iVec.begin(), iVec.end(), g);
}

/* start from the lobby, by backtracking and dfs to generate the maze */
static void dfs(int level, struct Position currentPosition, std::vector<bool>& visited)
{
    std::vector<int> list = { GOEAST, GOSOUTH, GOWEST, GONORTH };
    
    ShuffleList(list);
    if (visited[currentPosition.row * level + currentPosition.col] == false) // not visited
    {
        visited[currentPosition.row *level + currentPosition.col] = true;
        for (auto c : list) // for all node adjacent to current node
        {
            struct Position tempPos;
            switch (c)
            {
                case GOEAST:
                    tempPos.row = currentPosition.row, tempPos.col = currentPosition.col + 1;
                    if (tempPos.col >= level) break; // meet the bound of the
                    if (visited[tempPos.row * level + tempPos.col] == false)
                    {
                        Maze[currentPosition.row][currentPosition.col] |= EAST; // remove the wall between the two cell
                        Maze[tempPos.row][tempPos.col] |= WEST;
                        dfs(level, tempPos, visited);
                    }
                    break;
                case GOSOUTH:
                    tempPos.row = currentPosition.row + 1, tempPos.col = currentPosition.col;
                    if (tempPos.row >= level) break; // meet the bound of the
                    if (visited[tempPos.row * level + tempPos.col] == false)
                    {
                        Maze[currentPosition.row][currentPosition.col] |= SOUTH;
                        Maze[tempPos.row][tempPos.col] |= NORTH;
                        dfs(level, tempPos, visited);
                    }
                    break;
                case GOWEST:
                    tempPos.row = currentPosition.row, tempPos.col = currentPosition.col - 1;
                    if (tempPos.col < 0) break; // meet the bound of the
                    if (visited[tempPos.row * level + tempPos.col] == false)
                    {
                        Maze[currentPosition.row][currentPosition.col] |= WEST;
                        Maze[tempPos.row][tempPos.col] |= EAST;
                        dfs(level, tempPos, visited);
                    }
                    break;
                case GONORTH:
                    tempPos.row = currentPosition.row - 1, tempPos.col = currentPosition.col;
                    if (tempPos.row < 0) break; // meet the bound of the
                    if (visited[tempPos.row * level + tempPos.col] == false)
                    {
                        Maze[currentPosition.row][currentPosition.col] |= NORTH;
                        Maze[tempPos.row][tempPos.col] |= SOUTH;
                        dfs(level, tempPos, visited);
                    }
                    break;
            }
        }
    }
}

/* all sets to 0 */
extern void InitMaze(int level)
{
    for (int i = 0; i < level; ++i)
        for (int j = 0; j < level; ++j)
        {
            Maze[i][j] = NOWAY;
        }
}

void PrintMaze(int level)
{
    for (int i = 0; i < level; ++i)
    {
        for (int j = 0; j < level; ++j)
        {
            std::cout << "+";
            if (!(Maze[i][j] & NORTH)) std::cout << "---";
            else std::cout << "   ";
        }
        std::cout << "+" << std::endl;
        for (int j = 0; j < level; ++j)
        {
            if (!(Maze[i][j] & WEST)) std::cout << "|";
            else std::cout << " ";
            // if (Maze[i][j] & MONSTER) std::cout << " M ";
            // else if (Maze[i][j] & PRINCESS) std::cout << " P ";
            if (Maze[i][j] & LOBBY) std::cout << " L ";
            // else if (Maze[i][j] & HERO) std::cout << " & ";
            else std::cout << "   ";
        }
        std::cout << "|" << std::endl;
    }
    for (int j = 0; j < level; ++j) std::cout << "+---";
    std::cout << "+" << std::endl;
}

extern void MazeGenerator(int level, int& lobbyRow, int& lobbyCol)
{
    if (level >= MAZE_LIMIT) level = MAZE_LIMIT;
    // struct Position monsterPosition = RandomPosition(level);
    // struct Position princessPosition = RandomPosition(level);
    std::vector<bool> visited(level * level, false);
    struct Position lobbyPosition = RandomPosition(level);

    /* check whether the princess and the monster are generated at the same grid */
    // while (princessPosition.row == monsterPosition.row and princessPosition.row == monsterPosition.row)
    // {
    //     princessPosition = RandomPosition(level); // re-generate the princess's location
    // }
    /* check whether the lobby is generated at the same grid with princess or the monster */
    // while ((lobbyPosition.row == monsterPosition.row  and lobbyPosition.col == lobbyPosition.col) or \
	// 	(lobbyPosition.row == princessPosition.row and lobbyPosition.col == princessPosition.col))
    // {
    //     lobbyPosition = RandomPosition(level); // re-generate the lobby's location
    // }
    InitMaze(level); // initialization
    //Maze[monsterPosition.row][monsterPosition.col] |= MONSTER; // set the grid info
    //Maze[princessPosition.row][princessPosition.col] |= PRINCESS;
    Maze[lobbyPosition.row][lobbyPosition.col] |= LOBBY;
    dfs(level, lobbyPosition, visited); // depth-first search generate the maze
    lobbyRow = lobbyPosition.row;
    lobbyCol = lobbyPosition.col;
}
