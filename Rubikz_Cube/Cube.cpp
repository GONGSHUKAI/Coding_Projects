#include <iostream>
#include <cstring>
#include <stack>
#include <ctime>
#define Clockwise 100
#define Counter_Clockwise -100
#define MaxDepth 5
#define DoubleMoveError 2   //指形如1+ 1— 这样拧完回归原状态的错误
#define QuadruMoveError 4   //指形如1+ 1+ 1+ 1+ 这样拧完回归原状态的错误
#define OK 1              //指没有上述两种错误，NextCube可以压入stack中

using namespace std;

typedef struct Status{
    char left[3][3];
    char right[3][3];
    char front[3][3];
    char back[3][3];
    char up[3][3];
    char down[3][3];
    int depth = 0;                                     //搜索深度：这个魔方结点在第depth层
    int path[20];                                      //记录拧（也即action）的路径
}CubeNode;

stack<CubeNode> nodes;                                 //创建一个存放CubeNode类型的栈（存放一个个魔方状态）
bool CheckSide (char side[3][3], char color);          //检查一面是否都是同色
bool isTarget (CubeNode S);                            //检查六面是否还原
string GetAction (int action);                         //根据action输出相应的拧动作，0+ 0- 1+ 1- 2+ 2- 3+ 3- 4+ 4- 5+ 5- 6+ 6- 7+ 7- 8+ 8-
void Rotate (char side[3][3], int operation);          //旋转一个面，operation区分顺、逆时针操作
CubeNode Move (CubeNode Cube, int action);             //做action动作拧一下，一共有18种拧法，从action = 1 到 action = 18
void ReverseMove (CubeNode Cube, int action);          //和Move方向相反的拧一下
void PrintSolution (CubeNode solution);                //打印还原序列
void CreateChild (CubeNode MyCube, int action);        //创建下一个魔方状态
int JudgeRepetition (CubeNode NextCube, int action);   //判断是否会出现MoveError（比如DoubleMoveError），否则不能让NextCube入栈
void DFS_Search();                                     //深度优先搜索：用栈实现

//Yellow y
//Red r
//Green g
//Pink p
//Blue b
//White w

/* 魔方的结构如下
      y y y
      y y y                     back
      y y y
r r r g g g p p p
r r r g g g p p p       left     up     right
r r r g g g p p p
      w w w
      w w w                     front
      w w w
      b b b
      b b b                     down
      b b b
*/

void DFS_Search(){
    while (!nodes.empty()){
        CubeNode MyCube = nodes.top();
        nodes.pop();
        if (isTarget(MyCube)){
            cout << "YES" << endl;
            cout << MyCube.depth << endl;
            PrintSolution(MyCube);
            return;
        }
        if (MyCube.depth >= MaxDepth) continue;
        else{
            MyCube.depth++;
            for (int action = 1 ; action <= 18 ; action++){
                CreateChild(MyCube, action);
            }
        }
    }
}
void CreateChild (CubeNode MyCube, int action){
    CubeNode* NextCube = new CubeNode();
    *NextCube = Move(MyCube, action);
    ReverseMove(MyCube, action);
    (*NextCube).path[(*NextCube).depth] = action;
    if (JudgeRepetition((*NextCube), action) == OK) nodes.push(*NextCube);
    delete NextCube;
}

int JudgeRepetition(CubeNode NextCube, int action){
    if (NextCube.depth == 1) return OK;
    else if (NextCube.depth >= 4){
        if (NextCube.path[NextCube.depth - 1] == action &&
            NextCube.path[NextCube.depth - 2] == action &&
            NextCube.path[NextCube.depth - 3] == action) return QuadruMoveError;
        else return OK;
    }
    else if (NextCube.depth >= 2){
        if (NextCube.path[NextCube.depth - 1] == action - 1 ||
            NextCube.path[NextCube.depth - 1] == action + 1 ) return DoubleMoveError;
        else return OK;
    }
    else return OK;
}

bool CheckSide (char side[3][3], char color){
    for (int i = 0 ; i < 3 ; ++i){
        for (int j = 0 ; j < 3 ; ++j){
            if (side[i][j] != color) return false;
        }
    }
    return true;
}

void PrintSolution (CubeNode solution){
    for (int i = 1 ; i <= solution.depth ; i++){
        cout << GetAction(solution.path[i]) << " ";
    }
    cout << endl;
}

bool isTarget (CubeNode S){
    if (CheckSide(S.left, 'r') == true &&
        CheckSide(S.right, 'p') == true &&
        CheckSide(S.up, 'g') == true &&
        CheckSide(S.down, 'b') == true &&
        CheckSide(S.front, 'w') == true &&
        CheckSide(S.back, 'y') == true)
        return true;
    else return false;
}

string GetAction(int action){
    if (action == 1) return "0+";
    else if (action == 2) return "0-";
    else if (action == 3) return "1+";
    else if (action == 4) return "1-";
    else if (action == 5) return "2+";
    else if (action == 6) return "2-";
    else if (action == 7) return "3+";
    else if (action == 8) return "3-";
    else if (action == 9) return "4+";
    else if (action == 10) return "4-";
    else if (action == 11) return "5+";
    else if (action == 12) return "5-";
    else if (action == 13) return "6+";
    else if (action == 14) return "6-";
    else if (action == 15) return "7+";
    else if (action == 16) return "7-";
    else if (action == 17) return "8+";
    else return "8-";
}

void Rotate (char side[3][3], int operation){
    if (operation == Counter_Clockwise){//逆时针转
        char temp = side[0][0];
        side[0][0] = side[0][2];
        side[0][2] = side[2][2];
        side[2][2] = side[2][0];
        side[2][0] = temp;
        
        temp = side[1][0];
        side[1][0] = side[0][1];
        side[0][1] = side[1][2];
        side[1][2] = side[2][1];
        side[2][1] = temp;
    }
    if (operation == Clockwise){//顺时针转
        char temp = side[2][2];
        side[2][2] = side[0][2];
        side[0][2] = side[0][0];
        side[0][0] = side[2][0];
        side[2][0] = temp;
        
        temp = side[2][1];
        side[2][1] = side[1][2];
        side[1][2] = side[0][1];
        side[0][1] = side[1][0];
        side[1][0] = temp;
    }
}

CubeNode Move (CubeNode Cube, int action){
    if (action == 1){           //0正向，左面顺时针旋转90
        char temp[3];
        temp[0] = Cube.down[0][0];
        temp[1] = Cube.down[1][0];
        temp[2] = Cube.down[2][0];

        Cube.down[0][0] = Cube.front[0][0];
        Cube.down[1][0] = Cube.front[1][0];
        Cube.down[2][0] = Cube.front[2][0];

        Cube.front[0][0] = Cube.up[0][0];
        Cube.front[1][0] = Cube.up[1][0];
        Cube.front[2][0] = Cube.up[2][0];

        Cube.up[0][0] = Cube.back[0][0];
        Cube.up[1][0] = Cube.back[1][0];
        Cube.up[2][0] = Cube.back[2][0];

        Cube.back[0][0] = temp[0];
        Cube.back[1][0] = temp[1];
        Cube.back[2][0] = temp[2];
        Rotate(Cube.left, Clockwise);
        return Cube;
    }
    else if (action == 2){      //0反向，左面逆时针旋转90
        char temp[3];
        temp[0] = Cube.back[0][0];
        temp[1] = Cube.back[1][0];
        temp[2] = Cube.back[2][0];

        Cube.back[0][0] = Cube.up[0][0];
        Cube.back[1][0] = Cube.up[1][0];
        Cube.back[2][0] = Cube.up[2][0];

        Cube.up[0][0] = Cube.front[0][0];
        Cube.up[1][0] = Cube.front[1][0];
        Cube.up[2][0] = Cube.front[2][0];

        Cube.front[0][0] = Cube.down[0][0];
        Cube.front[1][0] = Cube.down[1][0];
        Cube.front[2][0] = Cube.down[2][0];

        Cube.down[0][0] = temp[0];
        Cube.down[1][0] = temp[1];
        Cube.down[2][0] = temp[2];
        Rotate(Cube.left, Counter_Clockwise);
        return Cube;
    }
    else if (action == 3){      //1正向
        char temp[3];
        temp[0] = Cube.down[0][1];
        temp[1] = Cube.down[1][1];
        temp[2] = Cube.down[2][1];

        Cube.down[0][1] = Cube.front[0][1];
        Cube.down[1][1] = Cube.front[1][1];
        Cube.down[2][1] = Cube.front[2][1];

        Cube.front[0][1] = Cube.up[0][1];
        Cube.front[1][1] = Cube.up[1][1];
        Cube.front[2][1] = Cube.up[2][1];

        Cube.up[0][1] = Cube.back[0][1];
        Cube.up[1][1] = Cube.back[1][1];
        Cube.up[2][1] = Cube.back[2][1];

        Cube.back[0][1] = temp[0];
        Cube.back[1][1] = temp[1];
        Cube.back[2][1] = temp[2];
        return Cube;
    }
    else if (action == 4){      //1反向
        char temp[3];
        temp[0] = Cube.back[0][1];
        temp[1] = Cube.back[1][1];
        temp[2] = Cube.back[2][1];

        Cube.back[0][1] = Cube.up[0][1];
        Cube.back[1][1] = Cube.up[1][1];
        Cube.back[2][1] = Cube.up[2][1];

        Cube.up[0][1] = Cube.front[0][1];
        Cube.up[1][1] = Cube.front[1][1];
        Cube.up[2][1] = Cube.front[2][1];

        Cube.front[0][1] = Cube.down[0][1];
        Cube.front[1][1] = Cube.down[1][1];
        Cube.front[2][1] = Cube.down[2][1];

        Cube.down[0][1] = temp[0];
        Cube.down[1][1] = temp[1];
        Cube.down[2][1] = temp[2];
        return Cube;
    }
    else if (action == 5){      //2正向，右面逆时针旋转90度
        char temp[3];
        temp[0] = Cube.back[0][2];
        temp[1] = Cube.back[1][2];
        temp[2] = Cube.back[2][2];

        Cube.back[0][2] = Cube.up[0][2];
        Cube.back[1][2] = Cube.up[1][2];
        Cube.back[2][2] = Cube.up[2][2];

        Cube.up[0][2] = Cube.front[0][2];
        Cube.up[1][2] = Cube.front[1][2];
        Cube.up[2][2] = Cube.front[2][2];

        Cube.front[0][2] = Cube.down[0][2];
        Cube.front[1][2] = Cube.down[1][2];
        Cube.front[2][2] = Cube.down[2][2];

        Cube.down[0][2] = temp[0];
        Cube.down[1][2] = temp[1];
        Cube.down[2][2] = temp[2];
        Rotate(Cube.right, Counter_Clockwise);
        return Cube;
    }
    else if (action == 6){      //2反向，右面顺时针旋转90度
        char temp[3];
        temp[0] = Cube.down[0][2];
        temp[1] = Cube.down[1][2];
        temp[2] = Cube.down[2][2];

        Cube.down[0][2] = Cube.front[0][2];
        Cube.down[1][2] = Cube.front[1][2];
        Cube.down[2][2] = Cube.front[2][2];

        Cube.front[0][2] = Cube.up[0][2];
        Cube.front[1][2] = Cube.up[1][2];
        Cube.front[2][2] = Cube.up[2][2];

        Cube.up[0][2] = Cube.back[0][2];
        Cube.up[1][2] = Cube.back[1][2];
        Cube.up[2][2] = Cube.back[2][2];

        Cube.back[0][2] = temp[0];
        Cube.back[1][2] = temp[1];
        Cube.back[2][2] = temp[2];
        Rotate(Cube.right, Clockwise);
        return Cube;
    }
    else if (action == 7){      //3正向，下面逆时针旋转90度
        char temp[3];
        temp[0] = Cube.front[2][0];
        temp[1] = Cube.front[2][1];
        temp[2] = Cube.front[2][2];

        Cube.front[2][0] = Cube.right[2][2];
        Cube.front[2][1] = Cube.right[1][2];
        Cube.front[2][2] = Cube.right[0][2];

        Cube.right[0][2] = Cube.back[0][0];
        Cube.right[1][2] = Cube.back[0][1];
        Cube.right[2][2] = Cube.back[0][2];

        Cube.back[0][0] = Cube.left[2][0];
        Cube.back[0][1] = Cube.left[1][0];
        Cube.back[0][2] = Cube.left[0][0];

        Cube.left[0][0] = temp[0];
        Cube.left[1][0] = temp[1];
        Cube.left[2][0] = temp[2];
        Rotate(Cube.down, Counter_Clockwise);
        return Cube;
    }
    else if (action == 8){      //3反向，下面顺时针旋转90度
        char temp[3];
        temp[0] = Cube.front[2][0];
        temp[1] = Cube.front[2][1];
        temp[2] = Cube.front[2][2];

        Cube.front[2][0] = Cube.left[0][0];
        Cube.front[2][1] = Cube.left[1][0];
        Cube.front[2][2] = Cube.left[2][0];

        Cube.left[0][0] = Cube.back[0][2];
        Cube.left[1][0] = Cube.back[0][1];
        Cube.left[2][0] = Cube.back[0][0];

        Cube.back[0][0] = Cube.right[0][2];
        Cube.back[0][1] = Cube.right[1][2];
        Cube.back[0][2] = Cube.right[2][2];

        Cube.right[0][2] = temp[2];
        Cube.right[1][2] = temp[1];
        Cube.right[2][2] = temp[0];
        Rotate(Cube.down, Clockwise);
        return Cube;
    }
    else if (action == 9){      //4正向
        char temp[3];
        temp[0] = Cube.front[1][0];
        temp[1] = Cube.front[1][1];
        temp[2] = Cube.front[1][2];

        Cube.front[1][0] = Cube.right[2][1];
        Cube.front[1][1] = Cube.right[1][1];
        Cube.front[1][2] = Cube.right[0][1];

        Cube.right[2][1] = Cube.back[1][0];
        Cube.right[1][1] = Cube.back[1][1];
        Cube.right[0][1] = Cube.back[1][2];

        Cube.back[1][0] = Cube.left[2][1];
        Cube.back[1][1] = Cube.left[1][1];
        Cube.back[1][2] = Cube.left[0][1];

        Cube.left[0][1] = temp[0];
        Cube.left[1][1] = temp[1];
        Cube.left[2][1] = temp[2];
        return Cube;
    }
    else if (action == 10){     //4反向
        char temp[3];
        temp[0] = Cube.front[1][0];
        temp[1] = Cube.front[1][1];
        temp[2] = Cube.front[1][2];

        Cube.front[1][0] = Cube.left[0][1];
        Cube.front[1][1] = Cube.left[1][1];
        Cube.front[1][2] = Cube.left[2][1];

        Cube.left[0][1] = Cube.back[1][2];
        Cube.left[1][1] = Cube.back[1][1];
        Cube.left[2][1] = Cube.back[1][0];

        Cube.back[1][0] = Cube.right[0][1];
        Cube.back[1][1] = Cube.right[1][1];
        Cube.back[1][2] = Cube.right[2][1];

        Cube.right[0][1] = temp[2];
        Cube.right[1][1] = temp[1];
        Cube.right[2][1] = temp[0];
        return Cube;
    }
    else if (action == 11){     //5正向，上面顺时针旋转90度
        char temp[3];
        temp[0] = Cube.front[0][0];
        temp[1] = Cube.front[0][1];
        temp[2] = Cube.front[0][2];

        Cube.front[0][0] = Cube.right[2][0];
        Cube.front[0][1] = Cube.right[1][0];
        Cube.front[0][2] = Cube.right[0][0];

        Cube.right[0][0] = Cube.back[2][0];
        Cube.right[1][0] = Cube.back[2][1];
        Cube.right[2][0] = Cube.back[2][2];

        Cube.back[2][0] = Cube.left[2][2];
        Cube.back[2][1] = Cube.left[1][2];
        Cube.back[2][2] = Cube.left[0][2];

        Cube.left[0][2] = temp[0];
        Cube.left[1][2] = temp[1];
        Cube.left[2][2] = temp[2];
        Rotate(Cube.up, Clockwise);
        return Cube;
    }
    else if (action == 12){     //5反向，上面逆时针旋转90度
        char temp[3];
        temp[0] = Cube.front[0][0];
        temp[1] = Cube.front[0][1];
        temp[2] = Cube.front[0][2];

        Cube.front[0][0] = Cube.left[0][2];
        Cube.front[0][1] = Cube.left[1][2];
        Cube.front[0][2] = Cube.left[2][2];

        Cube.left[0][2] = Cube.back[2][2];
        Cube.left[1][2] = Cube.back[2][1];
        Cube.left[2][2] = Cube.back[2][0];

        Cube.back[2][0] = Cube.right[0][0];
        Cube.back[2][1] = Cube.right[1][0];
        Cube.back[2][2] = Cube.right[2][0];

        Cube.right[0][0] = temp[2];
        Cube.right[1][0] = temp[1];
        Cube.right[2][0] = temp[0];
        Rotate(Cube.up, Counter_Clockwise);
        return Cube;
    }
    else if (action == 13){     //6正向，前面顺时针旋转90度
        char temp[3];
        temp[0] = Cube.down[0][0];
        temp[1] = Cube.down[0][1];
        temp[2] = Cube.down[0][2];

        Cube.down[0][0] = Cube.right[2][2];
        Cube.down[0][1] = Cube.right[2][1];
        Cube.down[0][2] = Cube.right[2][0];

        Cube.right[2][0] = Cube.up[2][0];
        Cube.right[2][1] = Cube.up[2][1];
        Cube.right[2][2] = Cube.up[2][2];

        Cube.up[2][0] = Cube.left[2][0];
        Cube.up[2][1] = Cube.left[2][1];
        Cube.up[2][2] = Cube.left[2][2];

        Cube.left[2][0] = temp[2];
        Cube.left[2][1] = temp[1];
        Cube.left[2][2] = temp[0];
        Rotate(Cube.front, Clockwise);
        return Cube;
    }
    else if (action == 14){     //6反向，前面逆时针旋转90度
        char temp[3];
        temp[0] = Cube.down[0][0];
        temp[1] = Cube.down[0][1];
        temp[2] = Cube.down[0][2];

        Cube.down[0][0] = Cube.left[2][2];
        Cube.down[0][1] = Cube.left[2][1];
        Cube.down[0][2] = Cube.left[2][0];

        Cube.left[2][0] = Cube.up[2][0];
        Cube.left[2][1] = Cube.up[2][1];
        Cube.left[2][2] = Cube.up[2][2];

        Cube.up[2][0] = Cube.right[2][0];
        Cube.up[2][1] = Cube.right[2][1];
        Cube.up[2][2] = Cube.right[2][2];

        Cube.right[2][0] = temp[2];
        Cube.right[2][1] = temp[1];
        Cube.right[2][2] = temp[0];
        Rotate(Cube.front, Counter_Clockwise);
        return Cube;
    }
    else if (action == 15){     //7正向
        char temp[3];
        temp[0] = Cube.down[1][0];
        temp[1] = Cube.down[1][1];
        temp[2] = Cube.down[1][2];

        Cube.down[1][0] = Cube.right[1][2];
        Cube.down[1][1] = Cube.right[1][1];
        Cube.down[1][2] = Cube.right[1][0];

        Cube.right[1][0] = Cube.up[1][0];
        Cube.right[1][1] = Cube.up[1][1];
        Cube.right[1][2] = Cube.up[1][2];

        Cube.up[1][0] = Cube.left[1][0];
        Cube.up[1][1] = Cube.left[1][1];
        Cube.up[1][2] = Cube.left[1][2];

        Cube.left[1][0] = temp[2];
        Cube.left[1][1] = temp[1];
        Cube.left[1][2] = temp[0];
        return Cube;
    }
    else if (action == 16){     //7反向
        char temp[3];
        temp[0] = Cube.down[1][0];
        temp[1] = Cube.down[1][1];
        temp[2] = Cube.down[1][2];

        Cube.down[1][0] = Cube.left[1][2];
        Cube.down[1][1] = Cube.left[1][1];
        Cube.down[1][2] = Cube.left[1][0];

        Cube.left[1][0] = Cube.up[1][0];
        Cube.left[1][1] = Cube.up[1][1];
        Cube.left[1][2] = Cube.up[1][2];

        Cube.up[1][0] = Cube.right[1][0];
        Cube.up[1][1] = Cube.right[1][1];
        Cube.up[1][2] = Cube.right[1][2];

        Cube.right[1][0] = temp[2];
        Cube.right[1][1] = temp[1];
        Cube.right[1][2] = temp[0];
        return Cube;
    }
    else if (action == 17){     //8正向，后面逆时针旋转90度
        char temp[3];
        temp[0] = Cube.down[2][0];
        temp[1] = Cube.down[2][1];
        temp[2] = Cube.down[2][2];

        Cube.down[2][0] = Cube.right[0][2];
        Cube.down[2][1] = Cube.right[0][1];
        Cube.down[2][2] = Cube.right[0][0];

        Cube.right[0][0] = Cube.up[0][0];
        Cube.right[0][1] = Cube.up[0][1];
        Cube.right[0][2] = Cube.up[0][2];

        Cube.up[0][0] = Cube.left[0][0];
        Cube.up[0][1] = Cube.left[0][1];
        Cube.up[0][2] = Cube.left[0][2];

        Cube.left[0][0] = temp[2];
        Cube.left[0][1] = temp[1];
        Cube.left[0][2] = temp[0];
        Rotate(Cube.back, Counter_Clockwise);
        return Cube;
    }
    else{                       //8反向，后面顺时针旋转90度
        char temp[3];
        temp[0] = Cube.down[2][0];
        temp[1] = Cube.down[2][1];
        temp[2] = Cube.down[2][2];

        Cube.down[2][0] = Cube.left[0][2];
        Cube.down[2][1] = Cube.left[0][1];
        Cube.down[2][2] = Cube.left[0][0];

        Cube.left[0][0] = Cube.up[0][0];
        Cube.left[0][1] = Cube.up[0][1];
        Cube.left[0][2] = Cube.up[0][2];

        Cube.up[0][0] = Cube.right[0][0];
        Cube.up[0][1] = Cube.right[0][1];
        Cube.up[0][2] = Cube.right[0][2];

        Cube.right[0][0] = temp[2];
        Cube.right[0][1] = temp[1];
        Cube.right[0][2] = temp[0];
        Rotate(Cube.front, Clockwise);
        return Cube;
    }
}

void ReverseMove(CubeNode Cube, int action){
    int j;
    if (action % 2 == 1) j = action + 1;
    else j = action - 1;
    Move(Cube, j);
}
    
int main() {
    CubeNode MyCube;

    MyCube.back[0][0] = 'g'; MyCube.back[0][1] = 'g'; MyCube.back[0][2] = 'y';
    MyCube.back[1][0] = 'g'; MyCube.back[1][1] = 'g'; MyCube.back[1][2] = 'y';
    MyCube.back[2][0] = 'g'; MyCube.back[2][1] = 'w'; MyCube.back[2][2] = 'w';

    MyCube.up[0][0] = 'y'; MyCube.up[0][1] = 'g'; MyCube.up[0][2] = 'g';
    MyCube.up[1][0] = 'w'; MyCube.up[1][1] = 'p'; MyCube.up[1][2] = 'g';
    MyCube.up[2][0] = 'w'; MyCube.up[2][1] = 'p'; MyCube.up[2][2] = 'g';

    MyCube.front[0][0] = 'b'; MyCube.front[0][1] = 'b'; MyCube.front[0][2] = 'y';
    MyCube.front[1][0] = 'b'; MyCube.front[1][1] = 'b'; MyCube.front[1][2] = 'w';
    MyCube.front[2][0] = 'b'; MyCube.front[2][1] = 'b'; MyCube.front[2][2] = 'w';

    MyCube.down[0][0] = 'y'; MyCube.down[0][1] = 'y'; MyCube.down[0][2] = 'b';
    MyCube.down[1][0] = 'y'; MyCube.down[1][1] = 'r'; MyCube.down[1][2] = 'r';
    MyCube.down[2][0] = 'w'; MyCube.down[2][1] = 'y'; MyCube.down[2][2] = 'b';

    MyCube.right[0][0] = 'r'; MyCube.right[0][1] = 'p'; MyCube.right[0][2] = 'p';
    MyCube.right[1][0] = 'r'; MyCube.right[1][1] = 'y'; MyCube.right[1][2] = 'b';
    MyCube.right[2][0] = 'r'; MyCube.right[2][1] = 'p'; MyCube.right[2][2] = 'p';

    MyCube.left[0][0] = 'p'; MyCube.left[0][1] = 'p'; MyCube.left[0][2] = 'p';
    MyCube.left[1][0] = 'r'; MyCube.left[1][1] = 'w'; MyCube.left[1][2] = 'r';
    MyCube.left[2][0] = 'r'; MyCube.left[2][1] = 'w'; MyCube.left[2][2] = 'r';
    
    clock_t startTime = clock();//计时开始
    nodes.push(MyCube);
    DFS_Search();
    clock_t endTime = clock();//计时结束
    cout << "运行时间：" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}
