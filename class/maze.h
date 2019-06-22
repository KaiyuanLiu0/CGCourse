//
// Created by KaiyuanLiu on 2019-06-20.
//

#ifndef CGCOURSE_MAZE_H
#define CGCOURSE_MAZE_H
#define DIRECTIONLIMIT 4    // four direction in total
#define NOWAY          0x0  // the following numbers in hexadecimal format
#define EAST           0x1  // are used for bitwise computation
#define SOUTH          0x2  // if the bit is 1, then the bit is open
#define WEST           0x4  // which stands for this direction has no wall
#define NORTH          0x8
 #define PRINCESS       0x10
// #define MONSTER        0x20
 #define LOBBY          0x40
// #define HERO           0x80
#define MAZE_LIMIT      100  // maximum size of the maze
#define ERROR_CODE      -1
// #define CHEATCODE      0    // used for cheat
#include <string>
enum direction { GOEAST = 1, GOSOUTH, GOWEST, GONORTH }; // four directions, south is down, north is up
struct Position {            // for functions' implementation
    int row;
    int col;
};
void InitMaze(int level);   // initialize the maze, all to NOWAY(0)
void PrintMaze(int level);  // print the whole maze
void MazeGenerator(int level, int& lobbyRow, int& lobbyCol); // generate the maze, by dfs
void Prompt(int row, int col);  // print the prompt message for input
int OperationToOp(std::string &str); // change the command in string format to int
void Cheat(int row, int col, int level); // for cheat command
#endif //CGCOURSE_MAZE_H
