#include <iostream>
#include "config.h"
int status[SIZE][SIZE];

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
        return status[row][col];//棋局结束，对角的三个'x'或三个'o'
    }
    if (CheckCounterDiag(row, col)){
        return status[row][col];//棋局结束，副对角的三个'x'或三个'o'
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

bool ValidIndex(int i, int j){
    return (i > 0 && i < SIZE && j > 0 && j < SIZE);
}