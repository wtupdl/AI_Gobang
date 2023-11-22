#include<iostream>
#include<math.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<ctime>
#include <fcntl.h>
#include <io.h>
#include <clocale>
#include "graphics.h"

using namespace std;

class node {
public:
    //棋子坐标和当前位置得分
    int x, y, grade;

    node(int x, int y, int grade) {
        this->x = x, this->y = y;
        this->grade = grade;
    }

    node() {

    }

    void set(int x, int y, int grade) {
        this->x = x, this->y = y;
        this->grade = grade;
    }

    bool operator<(const node &a) const { //重载运算符，使其默认按grade升序排序
        //if (this->grade == a.grade)return this->x * 15 + this->y > a.x * 15 + a.y;
        return this->grade > a.grade;
    }

    bool operator>(const node &a) const { //重载运算符
        //if (this->grade == a.grade)return this->x * 15 + this->y < a.x * 15 + a.y;
        return this->grade < a.grade;
    }
};


struct Graphic { // 前端部分，提供图形库支持
    int lx, ly; //棋盘第一个点坐标
    int L, round; //棋盘规格，已有棋子数量
    node *p;//保存落子顺序
    bool g[20][20];//判断该位置是否已经下了棋子
    Graphic(int L);//构造函数，用于初始化
    void creat_menu(int i, bool r); //绘制第i个菜单框,r为0表示原色，为1表示选中色
    int menu();//根据菜单的点击返回模式信息
    void creat_checkerboard();//创建棋盘
    void clear_checkerboard();//清除棋盘
    void drop_piece(int x, int y); //在（x,y）列落子
    void clear_piece(); //清除当前最后一步的棋子的棋子
    void setNum();//为棋子编号,最后一个棋子编号为红，上一个编号为其他
    void print_prompt_right(int x, int y, int tt, int grade, double t, int l); //打印右边提示，位置，计算次数，得分，计算时间,写在第几行
    void clear_prompt_right();//清除右边提示框的提示信息
    void print_prompt_down(int x, int y); //打印下方的走法提示信息
    void print_prompt_gameover_down(int t, double tt);//打印下方回合结束信息,t为结果，tt为时间
    void clear_prompt_down();//清除下方提示框的提示信息
    void exchange();//变更回合提示信息
    int getmouses();////获取鼠标点击信息
    void update();//更新界面
};

struct AiCalcule { // 后端计算，提供走法支持{;
    int grade = 0, round = 0;//初始得分，初始落子数
    const int inf = (1 << 23);
    const int Initiative = 1, Gote = 2, Vacancy = 0; // 先手，后手代表数字
    int L;//棋盘规格
    int p[20][20], d[20][20][5], data[222223]; //棋盘, 各赢法得分，各棋型分数
    int f[20][20];//记录棋子周围的棋子数量，用于判断是否可以走
    node *cp;//保存落子顺序
    AiCalcule(int L);//构造函数，用于初始化
    void creat_grade();//保存棋型得分
    void upgrade(int x, int y, int t, int res); //更新赢法得分
    void update(int x, int y); //在(x,y)更新后,更新相关赢法得分
    bool upcf(int x, int y); //更新cf数组
    void dropPiece(int x, int y); //在位置（x,y）落子,结果不存放在cp数组中
    void dropPiece(int x, int y, bool g); //在位置（x,y）落子,结果存放在cp数组中
    void clearPiece(int x, int y); //清除位置（x,y）的子
    void clearPiece(); //清除最后一步的落子
    int gameover();//判断游戏输赢（-1,0,1，2）：后手胜，未结束，先手胜，平
    int getgrade(int x, int y); //启发函数
    int dfs(int T, int piece, int a, int b); //搜索
    node getInitiative(int T, Graphic qd); //获取先手最优走法,T为博弈树最大深度
    node getGote(int T, Graphic qd); //获取后手最优解法,T为博弈树最大深度
    void heap_sort(node *p, int len);

    void adjust_heap(node *p, int f, int len);

    void ds();
};
