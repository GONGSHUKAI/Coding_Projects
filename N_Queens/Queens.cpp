#include <stdio.h>
#include <iostream>

#define MAX_N 8
#define MAX_NODES 10*MAX_N            //栈的大小

#define pop() stack[--sp]
#define push(node) stack[sp++] = node
#define stack_not_empty (sp>0)

typedef struct BoardState{
    int n, q[MAX_N];//n表示当前棋盘上的皇后个数；q[i]表示当前行（第i行）上皇后的列号
}BoardState;

BoardState stack[MAX_NODES];
int sp = 0;
int queens[MAX_N];
int conflict(int q, int p, short queens[]);//判断在(@q,@p)放置皇后是否冲突
int queen(int n); //尝试在棋盘上放置 @n 个皇后
void print_queens(BoardState *st); //打印目前棋盘上的皇后

int main( ){
    BoardState init_st;

    init_st.n = 0;
    push(init_st);
    queen(MAX_N);
    return 0;
}

void print_queens(BoardState *st){
    for(int i = 0; i < st->n; i++)
    {
        for(int j = 0; j < st->n; j++)
        {
            if(j == st->q[i]) std::cout << "# ";
            else std::cout << ". ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//判断是否冲突：q行p列能不能放
int conflict(int q, int p, int queens[]){
    for(int i = 0; i < q; i++)
    {
        if(queens[i] == p || i + queens[i] == p + q || i - queens[i] + 8 == q - p + 8) return 1;
        //if(queens[i] == p) return 1;
    }
    return 0;
}

int queen(int n){ //解决n皇后问题
    int i, nCount=0;
    BoardState st;

    while(stack_not_empty){
        st = pop();
        if (st.n>=n)
        {
            print_queens(&st);
            nCount ++;
            continue;
        }
        st.n++;    //当前棋盘上的皇后数量+1
        for(i=0; i<n; i++){ //之前的皇后与当前皇后位置i是否冲突
            if (conflict(st.n-1, i, st.q))
                continue;
            st.q[st.n-1] = i;    //不冲突，放在i列
            push(st);        //新生成的节点入栈
        }
    }
    printf("%d\n", nCount);
    return 0;
}
