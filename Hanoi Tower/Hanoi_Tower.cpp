#include <iostream>
#include <stack>

typedef struct HanoiState{
    int n;  //当前处理盘子数
    char A,B,C; //三个柱子的表示
}HanoiState;
//汉诺塔默认初始盘面：A柱n个盘子，B柱0个盘子，C柱0个盘子

std::stack <HanoiState> HanoiStack;

void Hanoi(int n, char A, char B, char C){//分治法递归求解：缩小问题规模
    if (n == 1) std::cout << "Move " << A << " To " << C << std::endl;
    else{
        Hanoi(n-1, A, C, B);
        std::cout << "Move " << A << " To " << C << std::endl;
        Hanoi(n-1, B, A, C);
    }  
}

void Hanoi2(int n, char A, char B, char C){//栈非递归求解
    HanoiState St;
    St.n = n;
    St.A = A;
    St.B = B;
    St.C = C;
    HanoiStack.push(St);//初始盘面入栈
    while (!HanoiStack.empty()){
        n = HanoiStack.top().n;//取栈顶盘面
        A = HanoiStack.top().A;
        B = HanoiStack.top().B;
        C = HanoiStack.top().C;
        HanoiStack.pop();//栈顶弹出
        if (n == 1) std::cout << "Move " << A << " To " << C << std::endl;
        else{
            HanoiState New_St;
            New_St.n = n-1; New_St.A = B; New_St.B = A; New_St.C = C; HanoiStack.push(New_St);//n-1个盘子从B柱移到C柱
            New_St.n = 1; New_St.A = A; New_St.B = B; New_St.C = C; HanoiStack.push(New_St);//1个盘子从A柱移到C柱
            New_St.n = n-1; New_St.A = A; New_St.B = C; New_St.C = B; HanoiStack.push(New_St);//n-1个盘子从A柱移到B柱
            //由于栈先进后出的结构，这三行代码应该从下往上看
        }
    }
}

int main(){
    int n = 3;
    std::cout << "递归求解" << std::endl;
    Hanoi(n, 'A', 'B', 'C');
    std::cout << "非递归求解" << std::endl;
    Hanoi2(n, 'A', 'B', 'C');
}