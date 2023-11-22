#include "head.h"
using namespace std;
void A(Graphic &fp, AiCalcule &op, int L, int t); //玩家VS人机,L为搜索深度,g为0表示不需提示，为1表示需要提示
void B(Graphic &fp, AiCalcule &op, int L, int t); //人机VS玩家,L为搜索深度,g为0表示不需提示，为1表示需要提示
void C(Graphic &fp, AiCalcule &op, int L1, int L2); //人机vs人机,L1为先手搜索深度,L2为后手搜索深度
void D(Graphic &fp, AiCalcule &op);//玩家VS玩家
int main() {
    clock_t startTime, endTime;
    Graphic fp(15);
    AiCalcule op(15);
    int u = fp.menu();
    startTime = clock();
    switch (u) {
        case 0:
            A(fp, op, 6, 1);
            break;
        case 1:
            A(fp, op, 8, 1);
            break;
        case 2:
            B(fp, op, 6, 1);
            break;
        case 3:
            B(fp, op, 8, 1);
            break;
        case 4:
            C(fp, op, 6, 6);
            break;
        case 5:
            C(fp, op, 8, 8);
            break;
        case 6:
            D(fp, op);
            break;
        default:
            break;
    }
    endTime = clock();//时结束
    double t = (double) (endTime - startTime) / CLOCKS_PER_SEC; //时间转为s
    fp.print_prompt_gameover_down(op.gameover(), t);//打印游戏结束信息
    fp.clear_checkerboard();//清除棋盘
    return 0;
}

void A(Graphic &fp, AiCalcule &op, int L, int t) { //玩家VS人机,g为0表示不需提升，为1表示需要提升
    if (t == 0) { //不需提示
        int ui = 1;
        int x, y;
        int h = -1;
        while (op.gameover() == 0) { //玩家VS人机
            node hh(1, 1, 1);
            if (ui & 1) { //玩家落子
                if (h < 0)h = fp.getmouses();
                if (h > 0) { //落子
                    x = h / (fp.L + 1), y = h % (fp.L + 1);//获取点击行列
                    //x = (h / fp.L) + 1, y = (h % fp.L) + 1;//获取点击行列
                    h = -1;
                    fp.drop_piece(x, y);//图形界面落子
                    op.dropPiece(x, y, 1); //后端落子
                    ui++;
                } else if (h < 0) { //悔棋
                    do {
                        fp.clear_piece();//图形界面悔棋
                        op.clearPiece();//后端悔棋
                        if (ui > 1)ui--;
                        h = fp.getmouses();
                    } while (h < 0);
                }
            } else { //ai落子
                hh = op.getGote(L, fp); //获取走法
                x = hh.x, y = hh.y;
                fp.print_prompt_down(x, y); //打印下方提升信息
                fp.drop_piece(x, y);//图形界面落子
                op.dropPiece(x, y, 1); //后端落子
                ui++;
                h = -1;
            }
        }
    } else { //需要提示
        int ui = 1;
        int x, y;
        int h = -1;
        while (op.gameover() == 0) { //玩家VS人机
            node hh(1, 1, 1);
            if (ui & 1) { //玩家落子
                hh = op.getInitiative(L, fp); //获取走法
                x = hh.x, y = hh.y;
                fp.print_prompt_down(x, y); //打印下方提升信息
                //if (h < 0)
                h = fp.getmouses();
                if (h > 0) { //落子
                    x = h / (fp.L + 1), y = h % (fp.L + 1);//获取点击行列
                    //x = (h / fp.L) + 1, y = (h % fp.L) + 1;//获取点击行列
                    h = -1;
                    fp.drop_piece(x, y);//图形界面落子
                    op.dropPiece(x, y, 1); //后端落子
                    ui++;
                } else if (h < 0) { //悔棋
                    do {
                        fp.clear_piece();//图形界面悔棋
                        op.clearPiece();//后端悔棋
                        if (ui > 1)ui--;
                        h = fp.getmouses();
                    } while (h < 0);
                }
                //hh=op.getInitiative(8,fp);
            } else { //ai落子
                hh = op.getGote(L, fp); //获取走法
                x = hh.x, y = hh.y;
                fp.print_prompt_down(x, y); //打印下方提升信息
                fp.drop_piece(x, y);//图形界面落子
                op.dropPiece(x, y, 1); //后端落子
                ui++;
            }
        }
    }
    //fp.print_prompt_gameover_down(op.gameover());//打印游戏结束信息
}

void B(Graphic &fp, AiCalcule &op, int L, int t) { //人机VS玩家,L为搜索深度,g为0表示不需提示，为1表示需要提示
    if (t == 0) { //不需提示
        int ui = 1;
        int x, y;
        int h = -1;
        while (op.gameover() == 0) { //玩家VS人机
            node hh(1, 1, 1);
            if (ui % 2 == 0) { //玩家落子
                if (h < 0)h = fp.getmouses();
                if (h > 0) { //落子
                    x = h / (fp.L + 1), y = h % (fp.L + 1);//获取点击行列
                    //x = (h / fp.L) + 1, y = (h % fp.L) + 1;//获取点击行列
                    h = -1;
                    fp.drop_piece(x, y);//图形界面落子
                    op.dropPiece(x, y, 1); //后端落子
                    ui++;
                } else if (h < 0) { //悔棋
                    do {
                        fp.clear_piece();//图形界面悔棋
                        op.clearPiece();//后端悔棋
                        if (ui > 1)ui--;
                        h = fp.getmouses();
                    } while (h < 0);
                }
            } else { //ai落子
                hh = op.getInitiative(L, fp); //获取走法
                x = hh.x, y = hh.y;
                fp.print_prompt_down(x, y); //打印下方提升信息
                fp.drop_piece(x, y);//图形界面落子
                op.dropPiece(x, y, 1); //后端落子
                ui++;
                h = -1;
            }
        }
    } else { //需要提示
        int ui = 1;
        int x, y;
        int h = -1;
        while (op.gameover() == 0) { //玩家VS人机
            node hh(1, 1, 1);
            if (ui % 2 == 0) { //人机落子
                hh = op.getGote(L, fp); //获取走法
                x = hh.x, y = hh.y;
                fp.print_prompt_down(x, y); //打印下方提升信息
                //if (h < 0)
                h = fp.getmouses();
                if (h > 0) { //落子
                    x = h / (fp.L + 1), y = h % (fp.L + 1);//获取点击行列
                    //x = (h / fp.L) + 1, y = (h % fp.L) + 1;//获取点击行列
                    h = -1;
                    fp.drop_piece(x, y);//图形界面落子
                    op.dropPiece(x, y, 1); //后端落子
                    ui++;
                } else if (h < 0) { //悔棋
                    do {
                        fp.clear_piece();//图形界面悔棋
                        op.clearPiece();//后端悔棋
                        if (ui > 1)ui--;
                        h = fp.getmouses();
                    } while (h < 0);
                }
                //hh=op.getInitiative(8,fp);
            } else { //玩家落子
                hh = op.getInitiative(L, fp); //获取走法
                x = hh.x, y = hh.y;
                fp.print_prompt_down(x, y); //打印下方提升信息
                fp.drop_piece(x, y);//图形界面落子
                op.dropPiece(x, y, 1); //后端落子
                ui++;
            }
        }
    }
    //fp.print_prompt_gameover_down(op.gameover());//打印游戏结束信息
}

void C(Graphic &fp, AiCalcule &op, int L1, int L2) { //人机vs人机,L1为先手搜索深度,L2为后手搜索深度
    int ui = 1;
    int x, y;
    while (op.gameover() == 0) {
        //int h=fp.getmouses();
        //if(h<0)continue;
        node hh(1, 1, 1);
        if (ui & 1)hh = op.getInitiative(L1, fp);
        else hh = op.getGote(L2, fp);
        x = hh.x, y = hh.y;
        //h=fp.getmouses();
        fp.drop_piece(x, y);//图形界面落子
        op.dropPiece(x, y, 1); //后端落子
        ui++;
    }
    //fp.print_prompt_gameover_down(op.gameover());//打印游戏结束信息
}

void D(Graphic &fp, AiCalcule &op) { //玩家VS玩家
    while (op.gameover() == 0) {
        int h = fp.getmouses();
        if (h > 0) {
            int x = h / (fp.L + 1), y = h % (fp.L + 1);//获取点击行列
            //int x = (h / fp.L) + 1, y = (h % fp.L) + 1;//获取点击行列
            fp.drop_piece(x, y);
            op.dropPiece(x, y, 1);
        } else if (h < 0) {
            fp.clear_piece();
            op.clearPiece();
        }
    }
    //fp.print_prompt_gameover_down(op.gameover());//打印游戏结束信息
}
