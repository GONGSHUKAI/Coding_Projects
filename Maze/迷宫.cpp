#include <iostream>

char mazemap[10][10]={
    {'@', '@', '@', '@', '@', '@', '@', '@', '@', '@'},
    {'@', 'O', '@', '@', 'O', 'O', 'O', 'O', 'O', '@'},
    {'@', 'O', '@', '@', 'O', 'O', 'O', '@', 'O', '@'},
    {'@', 'O', '@', 'O', 'O', '@', 'O', '@', 'O', '@'},
    {'@', 'O', '@', '@', '@', 'O', 'O', '@', 'O', '@'},
    {'@', 'O', 'O', 'O', '@', 'O', '@', '@', 'O', '@'},
    {'@', 'O', '@', 'O', 'O', 'O', '@', 'O', 'O', '@'},
    {'@', 'O', '@', '@', '@', 'O', '@', '@', 'O', '@'},
    {'@', '@', 'O', 'O', 'O', '@', 'O', 'O', 'O', '@'},
    {'@', '@', '@', '@', '@', '@', '@', '@', '@', '@'}
};

int visit[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


typedef struct direction{
    int delta_row;//行偏移量
    int delta_col;//列偏移量
    char dir;
}direction;

//开始位置(1,1)，结束位置(8,8)
direction move[4] = {
    {-1,0,'U'},
    {0,1,'R'},
    {1,0,'D'},
    {0,-1,'L'}
};

int maze(int x, int y){//迷宫开始位置[1][1]，结束位置[8][8]
    int row_now;
    int col_now;
    char dir_now;
    if (x == 8 && y == 8) return 1;
    for (int i = 0 ; i < 4 ; i++){
        row_now = x + move[i].delta_row;
        col_now = y + move[i].delta_col;
        dir_now = move[i].dir;
        if (mazemap[row_now][col_now] == 'O' && visit[row_now][col_now] == 0){
            visit[row_now][col_now] = 1;
            if (maze(row_now, col_now) == 1){//递归调用
                mazemap[row_now][col_now] = '*';
                //std::cout << row_now << col_now << dir_now << std::endl;
                return 1;
            }
        }
    }
    return 0;
}

void PrintMaze (char maze[10][10]){
    for (int i = 0 ; i < 10 ; i++){
        for (int j = 0 ; j < 10 ; j++){
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(){
    mazemap[1][1] = '*';
    maze(1,1);
    if (mazemap[8][8] != '*')   std::cout << "No Path!" << std::endl;
    else PrintMaze(mazemap);
}