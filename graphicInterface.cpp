//提供图形界面支持
#include"head.h"
#include <graphics.h>
Graphic::Graphic(int L) {
    setlocale(LC_ALL, "chs");//设置文字输出格式
    this->p = (node *) malloc(300 * sizeof(node));
    this->lx = 80, this->ly = 130; //棋盘第一个点坐标
    this->round = 0;
    this->L = L;
    memset(this->g, 0, sizeof(this->g));
    setcaption("五子棋"); //设置窗口的标题
    initgraph(50 * L + 750 + 30, 100 + 50 * L + 100 + 50); //设置窗口大小规格
    setbkcolor(EGERGB(82, 137, 11)); //设置窗口背景色为绿色
    setbkmode(TRANSPARENT);//设置输出文字时的背景色为透明
    ege_enable_aa(true);//设置抗锯齿
    setcolor(EGEARGB(255, 5, 2, 2)); //设置线条颜色为黑色
    setfillcolor(EGEARGB(117, 140, 81, 11)); //设置填充颜色为h黄色
}

void Graphic::creat_menu(int i, bool r) { //绘制第i个菜单框,r为0表示原色，为1表示选中色
    //ege_fillrect(this->lx + this->L * 20, this->ly + 3, 650, 616);//绘制矩形
    int x = this->lx + this->L * 20, y = this->ly + 3;
    string s[7] = {"玩家VS人机（简单模式：6层博弈树）", "玩家VS人机（困难模式：8层博弈树）", "人机VS玩家（简单模式：6层博弈树）",
                   "人机VS玩家（困难模式：8层博弈树）", "人机VS人机（简单模式：6层博弈树）", "人机VS人机（困难模式：8层博弈树）",
                   "玩家VS玩家（无提示）"
    };

    setfillcolor(EGERGB(82, 137, 11)); //设置填充颜色为绿色
    ege_fillrect(x, y + 88 * i, 650, 80);//绘制矩形
    if (r) {
        setfillcolor(EGERGBA(213, 213, 213, 155)); //设置填充颜色
        ege_fillrect(x, y + 88 * i, 650, 80); //绘制矩形
        setcolor(EGERGBA(255, 255, 255, 155)); //设置线条颜色为黑色
        setfont(40, 0, "华文行楷"), xyprintf(x + 10, y + 88 * i + 20, "%s", s[i].c_str());
        setcolor(EGEARGB(255, 5, 2, 2)); //设置线条颜色为黑色
    } else {
        setfillcolor(EGERGBA(213, 213, 213, 155)); //设置填充颜色
        ege_fillrect(x, y + 88 * i, 650, 80); //绘制矩形
        setfont(40, 0, "华文行楷"), xyprintf(x + 10, y + 88 * i + 20, "%s", s[i].c_str());
    }
}

int Graphic::menu() {//根据菜单的点击返回模式信息

    for (int i = 0; i < 7; i++)this->creat_menu(i, 0); //绘制菜单框
    this->creat_menu(0, 1);
    int u = 0;
    int t = 1;
    while (mousemsg() || t) {
        mouse_msg msg = getmouse();
        if (msg.is_wheel()) { //鼠标移动信息
            if (msg.wheel > 0) { //菜单上移动
                u = (u - 1 + 7) % 7;
                this->creat_menu(u, 1);
                this->creat_menu((u + 1) % 7, 0);
            } else { //菜单下移动
                u = (u + 1) % 7;
                this->creat_menu(u, 1);
                this->creat_menu((u - 1 + 7) % 7, 0);
            }

        }
        if ((msg.is_left() || msg.is_right()) && msg.is_down()) { //当左键点击合法时，返还落子点的映射
            break;
        }
    }
    setfillcolor(EGERGB(82, 137, 11)); //设置填充颜色为绿色
    ege_fillrect(this->lx + this->L * 20, this->ly + 3, 650, (this->L - 1) * 50 - 3);//绘制矩形
    this->creat_checkerboard();
    return u;
}

void Graphic::creat_checkerboard() { //创建棋盘

    int L = this->L;
    //initgraph(50 * L + 750 + 30, 100 + 50 * L + 100 + 50); //设置窗口大小规格
    setbkcolor(EGERGB(82, 137, 11)); //设置窗口背景色为绿色
    //setbkmode(TRANSPARENT);//设置输出文字时的背景色为透明
    //ege_enable_aa(true);//设置抗锯齿
    //绘制标题
    setcolor(BLACK);
    setfont(50, 0, "华文行楷"), xyprintf(50 * this->L / 2 - 80, 20, "AI五子棋");
    setfont(15, 0, "宋体"), xyprintf(50 * this->L / 2 + 130, 50, "——wtupdl");
    setfillcolor(EGEARGB(255, 189, 183, 107)); //设置填充颜色为黄色
    ege_fillrect(this->lx, this->ly, (this->L - 1) * 50, (this->L - 1) * 50); //填充一个矩形作为棋盘主区域
    //绘制棋盘线条和数字
    setcolor(EGEARGB(255, 5, 2, 2)); //设置线条颜色为黑色
    setlinewidth(3); //设置线条宽度
    setfont(20, 0, "宋体");
    for (int i = 0; i < this->L; i++) {
        int x1, y1, x2, y2;
        x1 = this->lx - 2, y1 = this->ly + 50 * i, x2 = this->lx + (this->L - 1) * 50 + 2, y2 = y1 = this->ly + 50 * i;
        ege_line(x1, y1, x2, y2); //绘制水平线条
        x1 = this->lx + i * 50, y1 = this->ly, x2 = this->lx + i * 50, y2 = this->ly + (this->L - 1) * 50;
        ege_line(x1, y1, x2, y2); //绘制竖直线条
        if (i + 1 < 10) { //绘制数字
            xyprintf(this->lx - 35 - 4, this->ly + 50 * i - 8, "%d", i + 1);
            xyprintf(this->lx + 50 * i - 5, this->ly - 45, "%d", i + 1);
        } else {
            xyprintf(this->lx - 35 - 8, this->ly + 50 * i - 8, "%d", i + 1);
            xyprintf(this->lx + 50 * i - 11, this->ly - 45, "%d", i + 1);
        }
    }
    //绘制左侧提示框
    setlinewidth(2); //设置线条宽度
    ege_rectangle(this->lx + this->L * 50, this->ly + 3, 650, (this->L - 1) * 50 - 3);
    //绘制回合提示信息
    setcolor(EGERGB(36, 19, 19));
    if (this->round & 1)setfont(45, 0, "华文行楷"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "后手回合");
    else setfont(45, 0, "华文行楷"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "先手回合");
    //绘制用于定位的小点
    int x2 = (this->L + 1) / 2, y2 = (this->L + 1) / 2, l = (this->L + 1) / 4;
    setfillcolor(EGEARGB(250, 2, 5, 5)); //设置填充颜色为黄色
    int x = x2, y = y2;
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //清除落子
    x = x2 - l, y = y2 - l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //清除落子
    x = x2 - l, y = y2 + l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //清除落子
    x = x2 + l, y = y2 - l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //清除落子
    x = x2 + l, y = y2 + l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //清除落子
}

void Graphic::exchange() { //变更回合提示信息
    setfillcolor(EGEARGB(255, 82, 137, 11)); //设置填充颜色为绿色
    ege_fillrect(this->lx + this->L * 50, this->ly - 60, 646, 60);
    if (this->round & 1) { //后手回合
        setcolor(EGERGB(245, 245, 250));
        setfont(45, 0, "华文行楷"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "后手回合");
    } else { //先手回合
        setcolor(EGERGB(36, 19, 19));
        setfont(45, 0, "华文行楷"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "先手回合");
    }
    this->update();
}

void Graphic::clear_prompt_right() { //清除右边提示框的提示信息
    setfillcolor(EGEARGB(255, 82, 137, 11)); //设置填充颜色为绿色
    ege_fillrect(this->lx + this->L * 50 + 2, this->ly + 6, 646, (this->L - 1) * 50 - 8);
    this->update();
}

void Graphic::print_prompt_right(int x, int y, int tt, int grade, double t, int l) { //打印右边提示，位置，计算次数，得分，计算时间,写在第几行
    //grade = -(1 << 30);
    setcolor(EGEARGB(2, 5, 2, 2)); //设置线条颜色为黑色
    int x1 = this->lx + this->L * 50 + 10, y1 = this->ly + 6 + (l) * 30;
    setfont(25, 0, "华文行楷"), xyprintf(x1, y1, "位置（%d,%d）:计算%d次,用时%.3fs,得分为%d", x, y, tt, t, grade);
    this->update();
}

void Graphic::print_prompt_down(int x, int y) { //打印下方的走法提示信息
    int x1 = this->lx + 100, y1 = this->ly + this->L * 50;
    setfont(50, 0, "华文行楷"), setcolor(BLACK);
    if (this->round & 1)xyprintf(x1, y1, "后手回合，系统推荐走法为（%d,%d）", x, y);
    else xyprintf(x1, y1, "先手回合，系统推荐走法为（%d,%d）", x, y);
    this->update();
}

void Graphic::print_prompt_gameover_down(int t, double tt) {//打印下方回合结束信息,g为结果，tt为时间
    int x1 = this->lx + 100, y1 = this->ly + this->L * 50;
    setfont(50, 0, "华文行楷"), setcolor(BLACK);
    if (t == 2)xyprintf(x1, y1, "游戏结束，平局！回合时长为%.3fS", tt);
    else if (t == 1)xyprintf(x1, y1, "游戏结束，先手获胜！回合时长为%.3fS", tt);
    else if (t == -1)xyprintf(x1, y1, "游戏结束，后手获胜！回合时长为%.3fS", tt);
    this->update();
}

void Graphic::clear_prompt_down() { //清除下方提示框的提示信息
    setfillcolor(EGEARGB(255, 82, 137, 11)); //设置填充颜色为绿色
    int x1 = this->lx + 50, y1 = this->ly + this->L * 50 - 30;
    ege_fillrect(x1, y1, 1000, 80);
    this->update();
}

void Graphic::drop_piece(int x, int y) { //在（x,y）列落子
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    this->g[x][y] = 1;
    this->p[this->round] = node(x, y, 0);
    if (this->round & 1) { //落白子
        setfillcolor(EGEARGB(250, 245, 245, 250)); //设置填充颜色为白色
    } else { //落白子
        setfillcolor(EGEARGB(250, 2, 5, 5)); //设置填充颜色为黑色
    }
    ege_fillellipse(x1 - 23, y1 - 23, 46, 46);//落子
    this->clear_prompt_right();//清除右侧提示框信息
    this->round += 1;//变更棋子数量
    this->exchange();//变更回合提示信息
    this->clear_prompt_down();
    this->setNum();
    this->update();
}

void Graphic::clear_piece() { //清除(x,y) 的棋子
    if (this->round <= 0)return; //如果棋盘上没有棋子
    int x = this->p[this->round - 1].x, y = this->p[this->round - 1].y;
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    this->g[x][y] = 0;//变更落子点状态
    setfillcolor(EGEARGB(255, 189, 183, 107)); //设置填充颜色为黄色
    ege_fillellipse(x1 - 25, y1 - 25, 50, 50); //清除落子
    setcolor(EGEARGB(255, 5, 2, 2)); //设置线条颜色为黑色
    setlinewidth(3); //设置线条宽度
    ege_line(x1 - 25, y1, x1 + 25, y1);
    ege_line(x1, y1 - 25, x1, y1 + 25);
    if (x == 1 || x == this->L || y == 1 || y == this->L) { //如果棋子在边界
        setfillcolor(EGEARGB(255, 82, 137, 11)); //设置填充颜色为黄色
        if (x == 1)ege_fillrect(x1 - 25, y1 - 25, 50, 23);
        if (y == 1)ege_fillrect(x1 - 25, y1 - 25, 23, 50);
        if (x == this->L)ege_fillrect(x1 - 25, y1 + 2, 50, 23);
        if (y == this->L)ege_fillrect(x1 + 2, y1 - 25, 23, 50);
    }
    //绘制用于定位的小点
    int x2 = (this->L + 1) / 2, y2 = (this->L + 1) / 2, l = (this->L + 1) / 4;
    if ((x == x2 && y == y2) || (x == x2 - l && y == y2 - l) || (x == x2 + l && y == y2 - l) ||
        (x == x2 - l && y == y2 + l) || (x == x2 + l && y == y2 + l)) {
        setfillcolor(EGEARGB(250, 2, 5, 5)); //设置填充颜色为黄色
        ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //清除落子
    }
    this->round -= 1;//变更棋子数量
    this->exchange();//变更回合提示信息
    this->clear_prompt_right();//清除右侧提示框信息
    this->clear_prompt_down();
    this->setNum();//编号
    this->update();//刷新
}

void Graphic::setNum() { //为棋子编号,最后一个棋子编号为红，上一个编号为其他
    if (this->round <= 0)return;
    int x = this->p[this->round - 1].x, y = this->p[this->round - 1].y;
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    //为当前棋子编号
    setcolor(RED), setfont(30, 0, "微软雅黑");
    if (this->round < 10)xyprintf(x1 - 7, y1 - 15, "%d", this->round);
    else if (this->round < 100)xyprintf(x1 - 13, y1 - 15, "%d", this->round);
    else xyprintf(x1 - 19, y1 - 15, "%d", this->round);
    if (this->round <= 1)return;
    //为上一个棋子编号
    x = this->p[this->round - 2].x, y = this->p[this->round - 2].y;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    if (this->round & 1)setcolor(BLACK);
    else setcolor(WHITE);
    //绘制编号
    if (this->round - 1 < 10)xyprintf(x1 - 7, y1 - 15, "%d", this->round - 1);
    else if (this->round - 1 < 100)xyprintf(x1 - 13, y1 - 15, "%d", this->round - 1);
    else xyprintf(x1 - 19, y1 - 15, "%d", this->round - 1);

}

int Graphic::getmouses() {//获取鼠标点击信息
    bool t = 1;
    while (mousemsg() || t) {
        mouse_msg msg = getmouse();
        if (msg.is_left() && msg.is_down()) {//当左键点击合法时，返还落子点的映射
            int x = msg.x, y = msg.y;
            if (x >= this->lx && x <= this->lx + (this->L - 1) * 50 && y >= this->ly &&
                y <= this->ly + (this->L - 1) * 50) { //鼠标在棋盘中
                x -= this->lx;
                y -= this->ly;
                int x1 = x / 50 * 50, y1 = y / 50 * 50;
                if (x - x1 > 25)x1 += 50;
                if (y - y1 > 25)y1 += 50;
                x1 /= 50, y1 /= 50;
                x1++, y1++;
                swap(x1, y1);
                if (!this->g[x1][y1])return x1 * (this->L + 1) + y1; //若该点没有棋子
            }
        } else if (msg.is_right() && msg.is_down()) { //当右键点击时，返还-1，表示悔棋
            return -1;
        }
    }
    return 0;
}

void Graphic::update() { //刷新
    int f = 0;
    for (; is_run(); delay_fps(60)) {
        f++;
        if (f > 3)break;
    }
}

void Graphic::clear_checkerboard() { //清除棋盘
    getch();
    closegraph();
}





//int main() {
//	//Graphic fp(15);
//	cout<<"sc"<<endl;
////	for (int i = 1; i <= 20; i++)fp.print_prompt_right(15, 15, 9999999, -1000000000, i);
////	fp.print_prompt_down(5, 8);
////	for (int i = 0; i < 100; i++) {
////		int h = fp.getmouses();
////		int x, y;
////		if (h >= 0) {
////			x = (h / fp.L) + 1, y = (h % fp.L) + 1;//获取点击行列
////			fp.drop_piece(x, y);
////		} else {//悔棋
////			if (fp.round > 0)fp.clear_piece();
////		}
////		fp.print_prompt_down(5, 8);
////	}
//	//fp.clear_checkerboard();
//	return 0;
//}
