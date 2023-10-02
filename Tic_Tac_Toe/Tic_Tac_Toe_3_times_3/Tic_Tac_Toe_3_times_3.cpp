#include <iostream>
#include "tic.h"
using namespace std;
int player = 1;
int status[SIZE][SIZE];
//初始化游戏状态
void Initial(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            status[i][j] = 0;
        }
    }
}
//返回表示棋子的字符
char Pic(int x){
    if (x == 0) return ' ';
    else if (x == 1) return 'o';
    else return 'x';
}
//绘制当前棋盘状态
void Draw(){
    cout << line << endl;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout << "|" << Pic(status[i][j]);
        }
        cout << "|" << endl;
        cout << line << endl;
    }
}

int main(){
    Initial();
    Draw();
    while (1){
        int chess;
        if (player == 1){
            cout << "Please input:" << endl;
            cin >> chess;//从左到右、从上到下编号1-9，chess输入放入的格子编号
            chess--;//重编号为0-8，从而放入数组
            if (status[chess / SIZE][chess % SIZE] == 0){//如果这个格子未曾落子
                Result(chess, player);//玩家落子
            }
            else{//如果这个格子已被落子
                cout << "The location is occupied" << endl;
                Draw();
                continue;
            }
        }
        else{
            chess = Minimax_Decision(player); ////AI 为玩家 -1
            Result(chess, player);
        }
        Draw();
        int BoardStatus = Check(chess);
        if (BoardStatus == 2){//棋局还未结束
            SwitchPlayer();
            continue;
        }
        if (abs(BoardStatus) == 1){//人类获胜或AI获胜
            cout << "player " << player << " win!" << endl;
            break;
        }
        if (BoardStatus == 0){//棋盘已满，平局
            cout << "Tie!" << endl;
            break;
        }
    }
}
/*返回值
 * 1 玩家1（人类）获胜
 * -1 玩家-1（AI）获胜
 * 2 还没结束
 * 0 棋盘已满
*/
int Check(int chess){//判断棋局是否结束
    int row = chess / SIZE;//落子所在行
    int col = chess % SIZE;//落子所在列
    if (status[row][0] == status[row][1] && status[row][0] == status[row][2]){
        return status[row][0];//棋局结束，同一行三个'x'或三个'o'，返回行连成的第一个元素
    }
    if (status[0][col] == status[1][col] && status[0][col] == status[2][col]){
        return status[0][col];//棋局结束，同一列三个'x'或三个'o'，返回列连成的第一个元素
    }
    if (row == col && 
        status[(row + 2) % SIZE][(col + 2) % SIZE] == status[row][col] &&
        status[row][col] == status[(row + 1) % SIZE][(col + 1) % SIZE]){
        return status[(row + 2) % SIZE][(col + 2) % SIZE];//棋局结束，主对角线三个'x'或三个'o'，返回主对角线连成的最后一个元素
    }
    if (row + col == SIZE - 1 && 
        status[(row + 2) % SIZE][(col + 1) % SIZE] == status[row][col] && 
        status[row][col] == status[(row + 1) % SIZE][(col + 2) % SIZE]){
        return status[(row + 2) % SIZE][(col + 1) % SIZE];//棋局结束，副对角线三个'x'或三个'o'，返回副对角线连成的最后一个元素
    }
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++) {
            if (status[i][j] == 0){
                return 2;//棋盘只要有一个地方没落子，就是棋局未结束
            }
        }
    }
    return 0;
}
void SwitchPlayer(){//切换玩家，1为人类玩家，-1为AI玩家
    player = -player;
}

void Result(int chess, int player){//将落子写入棋盘状态
    status[chess / SIZE][chess % SIZE] = player;
}

//计算AI的最佳落子
/*
AI为Min玩家
对于每一个空位
    尝试落子
    计算minimax分值，并更新最小值和最小值对应的落子
    清除落子
返回最佳落子位置
*/
int Minimax_Decision(int player){
    int min = INF;
    int choice = -1;//AI的落子位置
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(status[i][j] == 0){
                status[i][j] = player;//模拟落子
                int temp = Minimax_Value(i*SIZE+j, player, -INF, INF);//计算对应位置的Minimax_Value
                //alpha的初值是-INF，随着更新越来越大
                //beta的初值是INF，随着更新越来越小
                status[i][j] = 0;//清除落子
                if(min > temp){
                    min = temp;
                    choice = i*SIZE+j;
                }
            }
        }
    }
    return choice;
}

/*
AI 为Min 玩家,人类为 Max 玩家

若棋局结束，直接返回分值

初始化最大和最小值
设置 nextPlayer = - player

对于每一个空位
    nextPlayer 尝试落子
    计算nextPlayer落子之后的Minimax_Value，并更新最大值/最小值
    清除落子
返回最大或最小值
*/

int Minimax_Value(int chess, int player, int alpha, int beta){
    int BoardStatus = Check(chess);
    if(abs(BoardStatus) == 1) return BoardStatus;//有玩家获胜，返回对应分数
    if(BoardStatus == 0) return 0;//和棋

    int NextPlayer = -player;//下一步由nextPlayer落子

    if(player == -1){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(status[i][j] == 0){
                    status[i][j] = NextPlayer;
                    alpha = max(alpha, Minimax_Value(i * SIZE + j, NextPlayer, alpha, beta));
                    status[i][j] = 0;
                    if(beta <= alpha) break;
                }
            }
        }
    }
    else{
        for(int i =0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(status[i][j] == 0){
                    status[i][j] = NextPlayer;
                    beta = min(beta, Minimax_Value(i * SIZE + j, NextPlayer, alpha, beta));
                    status[i][j] = 0;
                    if(beta <= alpha) break;
                }
            }
        }
    }

    if (NextPlayer == -1) return beta;
    else return alpha;
}