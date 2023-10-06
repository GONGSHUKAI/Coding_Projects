#ifndef TIC_H
#define TIC_H

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#define HUMAN 1
#define AI -1
#define NOTOVER 2
#define TIE 0
using namespace std;

const int SIZE = 5;//井字棋棋盘的大小为5*5
const int INF = 10000;//表示无穷大
extern int status[SIZE][SIZE];//外部的二维数组status，存储棋盘上的状态。
const string line = " ---------- ";//表示在绘制棋盘时的分割线。
const int MAXDEPTH = 8;//博弈树搜索时所考虑的最大层数。
extern int player;//外部的整型变量player，表示当前轮到哪个玩家下棋。
const int dx[8] = {-1,1,0,0,-1,-1,1,1};
const int dy[8] = {0,0,-1,1,-1,1,-1,-1};

#endif