#include <iostream>
#include "config.h"
#include "check.cpp"
int depth = 0;
int player = 1;

void Initial();//初始化游戏状态。
char ToChar(int x);//返回表示棋子的字符。
void Draw();//绘制当前棋盘状态。
void ChessMove(int chess, int player);//用于落子
void SwitchPlayer();//用于切换当前玩家。
int CurrentScore();//计算当前盘面的分值（效用函数）
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
            clock_t startTime = clock();//计时开始
            chess = Minimax_Decision(player);//AI通过Minimax对抗算法生成落子位置
            ChessMove(chess, player);//AI落子
            clock_t endTime = clock();//计时结束
            cout << "运行时间：" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
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

int CurrentScore(){
    int maxscore = 0;
    for (int i = 0 ; i < SIZE ; i++){
        for (int j = 0 ; j < SIZE ; j++){
            if (status[i][j] == HUMAN){
                for (int action = 0 ; action < 8 ; action++){
                    if (ValidIndex(i+dx[action], j+dy[action]) && status[i+dx[action]][j+dy[action]] == status[i][j]){
                        int new_i = i + dx[action];
                        int new_j = j + dx[action];
                        if (status[new_i+dx[action]][new_j+dy[action]] == status[i][j]){
                            maxscore += 10;
                        }
                    }
                }
            }
            else if (status[i][j] == AI){
                for (int action = 0 ; action < 8 ; action++){
                    if (ValidIndex(i+dx[action], j+dy[action]) && status[i+dx[action]][j+dy[action]] == status[i][j]){
                        int new_i = i + dx[action];
                        int new_j = j + dx[action];
                        if (status[new_i+dx[action]][new_j+dy[action]] == status[i][j]){
                            maxscore -= 30;
                        }
                    }
                }
            }
        }
    }
    return maxscore;
}

int Evaluate(int depth, int signal, int player){//给出深度depth下人类胜利/AI胜利/平局的得分
    //signal = -1表示AI胜利
    //signal = 1表示人类胜利
    //signal = 0表示和棋
    //其余情况下表示还没搜到底，需要做trade-off
    if (signal == -1){
        return -100;
    }
    else if (signal == 1){
        return 100;
    }
    else if (signal == 0){
        return TIE;
    }
    else{
        return CurrentScore();
    }
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
    //HUMAN胜利返回得分HUMANSCORE，AI胜利返回得分AISCORE
    if (BoardStatus == -1 || BoardStatus == 1 || BoardStatus == 0){
        return Evaluate(depth, BoardStatus, player);
    }
    if (depth >= MAXDEPTH){
        return Evaluate(depth, BoardStatus, player);
    }

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

    if (NextPlayer == AI) return beta;//如果没遇到要剪枝的问题，下一个玩家是AI就返回Min方的最优值beta
    else return alpha;//如果没遇到要剪枝的问题，下一个玩家是人类就返回Max方的最优值alpha
}
