//条件编译指令，用于避免头文件被重复包含。如果之前没有定义过 TIC_H 宏，那么下面的内容就会被包含在编译中，否则会被跳过。
#ifndef TIC_H
#define TIC_H

#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;
const int SIZE = 3;//井字棋棋盘的大小为3*3
const int INF = 10000;//表示无穷大
extern int status[SIZE][SIZE];//外部的二维数组status，存储棋盘上的状态。
const string line = " ----- ";//表示在绘制棋盘时的分割线。
const int NUM = 16;//博弈树搜索时所考虑的最大层数。
extern int player;//外部的整型变量player，表示当前轮到哪个玩家下棋。
int Check(int chess);//检查是否存在获胜方。
void Result(int chess, int player);//用于显示游戏结果。
void SwitchPlayer();//用于切换当前玩家。
int Minimax_Decision(int player);//根据当前棋盘状态和玩家，选择最佳的下棋位置。
int Minimax_Value(int chess, int player, int alpha, int beta);//评估当前棋盘状态对当前玩家的价值。
void Initial();//初始化游戏状态。
void Draw();//绘制当前棋盘状态。
char Pic(int x);//返回表示棋子的字符。
int alpha_beta(int chess, int player, int alpha, int beta);//实现Alpha-Beta剪枝算法，在博弈树搜索过程中提高搜索效率。
//条件编译指令的结束标记。
#endif // TIC_H
