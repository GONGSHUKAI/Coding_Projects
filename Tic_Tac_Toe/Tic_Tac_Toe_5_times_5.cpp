#include <iostream>
#include <string.h>
#include <cstdlib>
#define HUMAN 1
#define AI -1
#define NOTOVER 2
#define TIE 0
using namespace std;

const int SIZE = 5;//井字棋棋盘的大小为5*5
const int INF = 10000;//表示无穷大
int status[SIZE][SIZE];//外部的二维数组status，存储棋盘上的状态。
const string line = " --------- ";//表示在绘制棋盘时的分割线。
const int MAXDEPTH = 15;//博弈树搜索时所考虑的最大层数。
int player = 1;//外部的整型变量player，表示当前轮到哪个玩家下棋。
int depth = 0;//当前的搜索深度

void Initial();//初始化游戏状态。
char ToChar(int x);//返回表示棋子的字符。
void Draw();//绘制当前棋盘状态。
void ChessMove(int chess, int player);//用于落子
void SwitchPlayer();//用于切换当前玩家。
int Check(int chess);//检查是否存在获胜方。
int Minimax_Decision(int player);//根据当前棋盘状态和玩家，选择最佳的下棋位置。
int Minimax_Value(int chess, int player, int alpha, int beta);//评估当前棋盘状态对当前玩家的价值.

int main(){
    Initial();
    Draw();
    while (1){
        int chess;
        if (player == HUMAN){
            cout << "Please input your chess:" << endl;
            cin >> chess;//从左到右、从上到下编号1-25，chess输入放入的格子编号
            chess--;//重编号为0-24，从而放入数组
            if (status[chess / SIZE][chess % SIZE] == 0){//如果这个格子未曾落子
                ChessMove(chess, player);//玩家落子
            }
            else{//如果这个格子已被落子
                cout << "The location is occupied!" << endl;
                Draw();
                continue;
            }
        }
        else{ //玩家为AI
            chess = Minimax_Decision(player);//AI通过Minimax对抗算法生成落子位置
            ChessMove(chess, player);//AI落子
        }
        Draw();
        int BoardStatus = Check(chess);//检查此时棋盘状态
        if (BoardStatus == NOTOVER){//棋局还未结束
            SwitchPlayer();
            continue;
        }
        if (abs(BoardStatus) == 1){//人类获胜或AI获胜
            cout << "player " << player << " win!" << endl;
            break;
        }
        if (BoardStatus == TIE){//棋盘已满，平局
            cout << "Tie!" << endl;
            break;
        }
    }
}

//初始化游戏状态
void Initial(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            status[i][j] = 0;
        }
    }
}

//返回表示棋子的字符
char ToChar(int x){
    if (x == 0) return ' ';
    else if (x == 1) return 'o';
    else return 'x';
}

//绘制当前棋盘状态
void Draw(){
    cout << line << endl;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            cout << "|" << ToChar(status[i][j]);
        }
        cout << "|" << endl;
        cout << line << endl;
    }
}

void ChessMove(int chess, int player){//将落子写入棋盘
    status[chess / SIZE][chess % SIZE] = player;
}

void SwitchPlayer(){//切换玩家，1为人类玩家，-1为AI玩家
    player = -player;
}

//Check1 - Check6，以及CheckDiag和CheckCounterDiag都是用于辅助Check函数的子函数
bool Check1(int row, int col){//0,1,2
    return (status[row][col] == status[row+1][col+1] && status[row+1][col+1] == status[row+2][col+2]);
}
bool Check2(int row, int col){//-1,0,1
    return (status[row][col] == status[row-1][col-1] && status[row][col] == status[row+1][col+1]);
}
bool Check3(int row, int col){//0,-1,-2
    return (status[row][col] == status[row-1][col-1] && status[row-1][col-1] == status[row-2][col-2]);
}
bool Check4(int row, int col){//0,1,2
    return (status[row][col] == status[row+1][col-1] && status[row+1][col-1] == status[row+2][col-2]);
}
bool Check5(int row, int col){//-1,0,1
    return (status[row][col] == status[row+1][col-1] && status[row][col] == status[row-1][col+1]);
}
bool Check6(int row, int col){//0,-1,-2
    return (status[row][col] == status[row-1][col+1] && status[row-1][col+1] == status[row-2][col+2]);
}
bool CheckDiag(int row, int col){
    if (row == col){
        if (row == 0){
            if (Check1(row, col)) return true;
            else return false;
        }
        else if (row == 1){
            if (Check1(row, col) || Check2(row, col)) return true;
            else return false;
        }
        else if (row == 2){
            if (Check1(row, col) || Check2(row, col) || Check3(row, col)) return true;
            else return false;
        }
        else if (row ==3){
            if (Check2(row, col) || Check3(row, col)) return true;
            else return false;
        }
        else if (row == 4){
            if (Check3(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row == col + 1){
        if (row == 1){
            if (Check1(row, col)) return true;
            else return false;
        }
        else if (row == 2){
            if (Check1(row, col) || Check2(row, col)) return true;
            else return false;
        }
        else if (row == 3){
            if (Check2(row, col) || Check3(row, col)) return true;
            else return false;
        }
        else if (row == 4){
            if (Check3(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row == col + 2){
        if (row == 2){
            if (Check1(row, col)) return true;
            else return false;
        }
        else if (row == 3){
            if (Check2(row, col)) return true;
            else return false;
        }
        else if (row == 4){
            if (Check3(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row == col - 1){
        if (col == 1){
            if (Check1(row, col)) return true;
            else return false;
        }
        else if (col == 2){
            if (Check1(row, col) || Check2(row, col)) return true;
            else return false;
        }
        else if (col == 3){
            if (Check2(row, col) || Check3(row, col)) return true;
            else return false;
        }
        else if (col ==4){
            if (Check3(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row == col - 2){
        if (col == 2){
            if (Check1(row, col)) return true;
            else return false;
        }
        else if (col == 3){
            if (Check2(row, col)) return true;
            else return false;
        }
        else if (col == 4){
            if (Check3(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}
bool CheckCounterDiag(int row, int col){
    if (row + col == SIZE - 1){
        if (row == 0){
            if (Check4(row, col)) return true;
            else return false;
        }
        else if (row == 1){
            if (Check4(row, col) || Check5(row, col)) return true;
            else return false;
        }
        else if (row == 2){
            if (Check4(row, col) || Check5(row, col) || Check6(row, col)) return true;
            else return false;
        }
        else if (row ==3){
            if (Check5(row, col) || Check6(row, col)) return true;
            else return false;
        }
        else if (row == 4){
            if (Check6(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row + col == SIZE - 2){
        if (row == 0){
            if (Check4(row, col)) return true;
            else return false;
        }
        else if (row == 1){
            if (Check4(row, col) || Check5(row, col)) return true;
            else return false;
        }
        else if (row == 2){
            if (Check5(row, col) || Check6(row, col)) return true;
            else return false;
        }
        else if (row == 3){
            if (Check6(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row + col == SIZE - 3){
        if (row == 0){
            if (Check4(row, col)) return true;
            else return false;
        }
        else if (row == 1){
            if (Check5(row, col)) return true;
            else return false;
        }
        else if (row == 2){
            if (Check6(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row + col == SIZE){
        if (row == 1){
            if (Check4(row, col)) return true;
            else return false;
        }
        else if (row == 2){
            if (Check4(row, col) || Check5(row, col)) return true;
            else return false;
        }
        else if (row == 3){
            if (Check5(row, col) || Check6(row, col)) return true;
            else return false;
        }
        else if (row == 4){
            if (Check6(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else if (row + col == SIZE + 1){
        if (row == 2){
            if (Check4(row, col)) return true;
            else return false;
        }
        else if (row == 3){
            if (Check5(row, col)) return true;
            else return false;
        }
        else if (row == 4){
            if (Check6(row, col)) return true;
            else return false;
        }
        else return false;
    }
    else return false;
}


int Check(int chess){//判断棋局是否结束
    int row = chess / SIZE;//落子所在行
    int col = chess % SIZE;//落子所在列
    if ((status[row][0] == status[row][1] && status[row][1] == status[row][2] && status[row][0] != 0)||
        (status[row][1] == status[row][2] && status[row][2] == status[row][3] && status[row][1] != 0)||
        (status[row][2] == status[row][3] && status[row][3] == status[row][4] && status[row][2] != 0)){
        return status[row][0];//棋局结束，同一行三个'x'或三个'o'，返回行连成的第一个元素
    }
    if ((status[0][col] == status[1][col] && status[1][col] == status[2][col] && status[0][col] != 0)||
        (status[1][col] == status[2][col] && status[2][col] == status[3][col] && status[1][col] != 0)||
        (status[2][col] == status[3][col] && status[3][col] == status[4][col] && status[2][col] != 0)){
        return status[0][col];//棋局结束，同一列三个'x'或三个'o'，返回列连成的第一个元素
    }
    if (CheckDiag(row, col)){
        return status[row][col];//棋局结束，主对角线三个'x'或三个'o'，返回主对角线连成的最后一个元素
    }
    if (CheckCounterDiag(row, col)){
        return status[row][col];//棋局结束，副对角线三个'x'或三个'o'，返回副对角线连成的最后一个元素
    }
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (status[i][j] == 0){
                return NOTOVER;//棋盘只要有一个地方没落子，就是棋局未结束
            }
        }
    }
    return TIE;
}

int Minimax_Decision(int player){//计算AI的最佳落子
//定义人类为先手(Max玩家)，AI为后手(Min玩家)
//对每个空位模拟落子，计算Minimax分值
//不断更新Max的分值alpha、Min的分值beta
//恢复模拟落子(棋盘在落子处值置0)
//返回最佳落子位置
    int min = INF;
    int choice = -1;//AI的落子位置
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(status[i][j] == 0){
                status[i][j] = player;//模拟落子
                int temp = Minimax_Value(i*SIZE+j, player, -INF, INF);//计算对应位置的Minimax_Value
                //(Max方)alpha的初值是-INF，随着更新越来越大
                //(Min方)beta的初值是INF，随着更新越来越小
                //更新通过递归来实现
                status[i][j] = 0;//恢复模拟落子
                if(min > temp){
                    min = temp;//如果Min方有更小的得分，就更新它
                    choice = i*SIZE+j;//更新最佳落子位置
                }
            }
        }
    }
    return choice;//返回最佳落子位置
}

int Minimax_Value(int chess, int player, int alpha, int beta){
    int BoardStatus = Check(chess);
    //有玩家获胜，返回对应分数
    //HUMAN胜利返回得分1，AI胜利返回得分-1
    if(abs(BoardStatus)==1) return BoardStatus;
    if(BoardStatus == 0) return 0;//返回和棋的得分：0
    if (depth >= MAXDEPTH) return 0;//如果搜索超过最大深度就不搜索了，返回得分0
    int NextPlayer = -player;//下一步由NextPlayer落子

    if(player == -1){//当前玩家为AI
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(status[i][j] == 0){
                    status[i][j] = NextPlayer;//模拟落子
                    depth++;
                    alpha = max(alpha, Minimax_Value(i * SIZE + j, NextPlayer, alpha, beta));
                    depth--;
                    status[i][j] = 0;
                    if(beta <= alpha) return alpha;
                    //如果Min层的beta不能让Max层的alpha变大，则剪枝，直接返回alpha
                }
            }
        }  
    }
    else{//当前玩家为人类
        for(int i =0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(status[i][j] == 0){
                    status[i][j] = NextPlayer;
                    depth++;
                    beta = min(beta, Minimax_Value(i * SIZE + j, NextPlayer, alpha, beta));
                    depth--;
                    status[i][j] = 0;
                    if(beta <= alpha) return beta;
                    //如果Max层的alpha不能让Min层的beta减小，则剪枝，直接返回beta
                }
            }
        }
    }

    if (NextPlayer == -1) return beta;//如果没遇到要剪枝的问题，下一个玩家是AI就返回Min方的最优值beta
    else return alpha;//如果没遇到要剪枝的问题，下一个玩家是人类就返回Max方的最优值alpha
}