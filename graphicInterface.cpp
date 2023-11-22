//�ṩͼ�ν���֧��
#include"head.h"
#include <graphics.h>
Graphic::Graphic(int L) {
    setlocale(LC_ALL, "chs");//�������������ʽ
    this->p = (node *) malloc(300 * sizeof(node));
    this->lx = 80, this->ly = 130; //���̵�һ��������
    this->round = 0;
    this->L = L;
    memset(this->g, 0, sizeof(this->g));
    setcaption("������"); //���ô��ڵı���
    initgraph(50 * L + 750 + 30, 100 + 50 * L + 100 + 50); //���ô��ڴ�С���
    setbkcolor(EGERGB(82, 137, 11)); //���ô��ڱ���ɫΪ��ɫ
    setbkmode(TRANSPARENT);//�����������ʱ�ı���ɫΪ͸��
    ege_enable_aa(true);//���ÿ����
    setcolor(EGEARGB(255, 5, 2, 2)); //����������ɫΪ��ɫ
    setfillcolor(EGEARGB(117, 140, 81, 11)); //���������ɫΪh��ɫ
}

void Graphic::creat_menu(int i, bool r) { //���Ƶ�i���˵���,rΪ0��ʾԭɫ��Ϊ1��ʾѡ��ɫ
    //ege_fillrect(this->lx + this->L * 20, this->ly + 3, 650, 616);//���ƾ���
    int x = this->lx + this->L * 20, y = this->ly + 3;
    string s[7] = {"���VS�˻�����ģʽ��6�㲩������", "���VS�˻�������ģʽ��8�㲩������", "�˻�VS��ң���ģʽ��6�㲩������",
                   "�˻�VS��ң�����ģʽ��8�㲩������", "�˻�VS�˻�����ģʽ��6�㲩������", "�˻�VS�˻�������ģʽ��8�㲩������",
                   "���VS��ң�����ʾ��"
    };

    setfillcolor(EGERGB(82, 137, 11)); //���������ɫΪ��ɫ
    ege_fillrect(x, y + 88 * i, 650, 80);//���ƾ���
    if (r) {
        setfillcolor(EGERGBA(213, 213, 213, 155)); //���������ɫ
        ege_fillrect(x, y + 88 * i, 650, 80); //���ƾ���
        setcolor(EGERGBA(255, 255, 255, 155)); //����������ɫΪ��ɫ
        setfont(40, 0, "�����п�"), xyprintf(x + 10, y + 88 * i + 20, "%s", s[i].c_str());
        setcolor(EGEARGB(255, 5, 2, 2)); //����������ɫΪ��ɫ
    } else {
        setfillcolor(EGERGBA(213, 213, 213, 155)); //���������ɫ
        ege_fillrect(x, y + 88 * i, 650, 80); //���ƾ���
        setfont(40, 0, "�����п�"), xyprintf(x + 10, y + 88 * i + 20, "%s", s[i].c_str());
    }
}

int Graphic::menu() {//���ݲ˵��ĵ������ģʽ��Ϣ

    for (int i = 0; i < 7; i++)this->creat_menu(i, 0); //���Ʋ˵���
    this->creat_menu(0, 1);
    int u = 0;
    int t = 1;
    while (mousemsg() || t) {
        mouse_msg msg = getmouse();
        if (msg.is_wheel()) { //����ƶ���Ϣ
            if (msg.wheel > 0) { //�˵����ƶ�
                u = (u - 1 + 7) % 7;
                this->creat_menu(u, 1);
                this->creat_menu((u + 1) % 7, 0);
            } else { //�˵����ƶ�
                u = (u + 1) % 7;
                this->creat_menu(u, 1);
                this->creat_menu((u - 1 + 7) % 7, 0);
            }

        }
        if ((msg.is_left() || msg.is_right()) && msg.is_down()) { //���������Ϸ�ʱ���������ӵ��ӳ��
            break;
        }
    }
    setfillcolor(EGERGB(82, 137, 11)); //���������ɫΪ��ɫ
    ege_fillrect(this->lx + this->L * 20, this->ly + 3, 650, (this->L - 1) * 50 - 3);//���ƾ���
    this->creat_checkerboard();
    return u;
}

void Graphic::creat_checkerboard() { //��������

    int L = this->L;
    //initgraph(50 * L + 750 + 30, 100 + 50 * L + 100 + 50); //���ô��ڴ�С���
    setbkcolor(EGERGB(82, 137, 11)); //���ô��ڱ���ɫΪ��ɫ
    //setbkmode(TRANSPARENT);//�����������ʱ�ı���ɫΪ͸��
    //ege_enable_aa(true);//���ÿ����
    //���Ʊ���
    setcolor(BLACK);
    setfont(50, 0, "�����п�"), xyprintf(50 * this->L / 2 - 80, 20, "AI������");
    setfont(15, 0, "����"), xyprintf(50 * this->L / 2 + 130, 50, "����wtupdl");
    setfillcolor(EGEARGB(255, 189, 183, 107)); //���������ɫΪ��ɫ
    ege_fillrect(this->lx, this->ly, (this->L - 1) * 50, (this->L - 1) * 50); //���һ��������Ϊ����������
    //������������������
    setcolor(EGEARGB(255, 5, 2, 2)); //����������ɫΪ��ɫ
    setlinewidth(3); //�����������
    setfont(20, 0, "����");
    for (int i = 0; i < this->L; i++) {
        int x1, y1, x2, y2;
        x1 = this->lx - 2, y1 = this->ly + 50 * i, x2 = this->lx + (this->L - 1) * 50 + 2, y2 = y1 = this->ly + 50 * i;
        ege_line(x1, y1, x2, y2); //����ˮƽ����
        x1 = this->lx + i * 50, y1 = this->ly, x2 = this->lx + i * 50, y2 = this->ly + (this->L - 1) * 50;
        ege_line(x1, y1, x2, y2); //������ֱ����
        if (i + 1 < 10) { //��������
            xyprintf(this->lx - 35 - 4, this->ly + 50 * i - 8, "%d", i + 1);
            xyprintf(this->lx + 50 * i - 5, this->ly - 45, "%d", i + 1);
        } else {
            xyprintf(this->lx - 35 - 8, this->ly + 50 * i - 8, "%d", i + 1);
            xyprintf(this->lx + 50 * i - 11, this->ly - 45, "%d", i + 1);
        }
    }
    //���������ʾ��
    setlinewidth(2); //�����������
    ege_rectangle(this->lx + this->L * 50, this->ly + 3, 650, (this->L - 1) * 50 - 3);
    //���ƻغ���ʾ��Ϣ
    setcolor(EGERGB(36, 19, 19));
    if (this->round & 1)setfont(45, 0, "�����п�"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "���ֻغ�");
    else setfont(45, 0, "�����п�"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "���ֻغ�");
    //�������ڶ�λ��С��
    int x2 = (this->L + 1) / 2, y2 = (this->L + 1) / 2, l = (this->L + 1) / 4;
    setfillcolor(EGEARGB(250, 2, 5, 5)); //���������ɫΪ��ɫ
    int x = x2, y = y2;
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //�������
    x = x2 - l, y = y2 - l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //�������
    x = x2 - l, y = y2 + l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //�������
    x = x2 + l, y = y2 - l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //�������
    x = x2 + l, y = y2 + l;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //�������
}

void Graphic::exchange() { //����غ���ʾ��Ϣ
    setfillcolor(EGEARGB(255, 82, 137, 11)); //���������ɫΪ��ɫ
    ege_fillrect(this->lx + this->L * 50, this->ly - 60, 646, 60);
    if (this->round & 1) { //���ֻغ�
        setcolor(EGERGB(245, 245, 250));
        setfont(45, 0, "�����п�"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "���ֻغ�");
    } else { //���ֻغ�
        setcolor(EGERGB(36, 19, 19));
        setfont(45, 0, "�����п�"), xyprintf(this->lx + this->L * 50 + 200, this->ly - 50, "���ֻغ�");
    }
    this->update();
}

void Graphic::clear_prompt_right() { //����ұ���ʾ�����ʾ��Ϣ
    setfillcolor(EGEARGB(255, 82, 137, 11)); //���������ɫΪ��ɫ
    ege_fillrect(this->lx + this->L * 50 + 2, this->ly + 6, 646, (this->L - 1) * 50 - 8);
    this->update();
}

void Graphic::print_prompt_right(int x, int y, int tt, int grade, double t, int l) { //��ӡ�ұ���ʾ��λ�ã�����������÷֣�����ʱ��,д�ڵڼ���
    //grade = -(1 << 30);
    setcolor(EGEARGB(2, 5, 2, 2)); //����������ɫΪ��ɫ
    int x1 = this->lx + this->L * 50 + 10, y1 = this->ly + 6 + (l) * 30;
    setfont(25, 0, "�����п�"), xyprintf(x1, y1, "λ�ã�%d,%d��:����%d��,��ʱ%.3fs,�÷�Ϊ%d", x, y, tt, t, grade);
    this->update();
}

void Graphic::print_prompt_down(int x, int y) { //��ӡ�·����߷���ʾ��Ϣ
    int x1 = this->lx + 100, y1 = this->ly + this->L * 50;
    setfont(50, 0, "�����п�"), setcolor(BLACK);
    if (this->round & 1)xyprintf(x1, y1, "���ֻغϣ�ϵͳ�Ƽ��߷�Ϊ��%d,%d��", x, y);
    else xyprintf(x1, y1, "���ֻغϣ�ϵͳ�Ƽ��߷�Ϊ��%d,%d��", x, y);
    this->update();
}

void Graphic::print_prompt_gameover_down(int t, double tt) {//��ӡ�·��غϽ�����Ϣ,gΪ�����ttΪʱ��
    int x1 = this->lx + 100, y1 = this->ly + this->L * 50;
    setfont(50, 0, "�����п�"), setcolor(BLACK);
    if (t == 2)xyprintf(x1, y1, "��Ϸ������ƽ�֣��غ�ʱ��Ϊ%.3fS", tt);
    else if (t == 1)xyprintf(x1, y1, "��Ϸ���������ֻ�ʤ���غ�ʱ��Ϊ%.3fS", tt);
    else if (t == -1)xyprintf(x1, y1, "��Ϸ���������ֻ�ʤ���غ�ʱ��Ϊ%.3fS", tt);
    this->update();
}

void Graphic::clear_prompt_down() { //����·���ʾ�����ʾ��Ϣ
    setfillcolor(EGEARGB(255, 82, 137, 11)); //���������ɫΪ��ɫ
    int x1 = this->lx + 50, y1 = this->ly + this->L * 50 - 30;
    ege_fillrect(x1, y1, 1000, 80);
    this->update();
}

void Graphic::drop_piece(int x, int y) { //�ڣ�x,y��������
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    this->g[x][y] = 1;
    this->p[this->round] = node(x, y, 0);
    if (this->round & 1) { //�����
        setfillcolor(EGEARGB(250, 245, 245, 250)); //���������ɫΪ��ɫ
    } else { //�����
        setfillcolor(EGEARGB(250, 2, 5, 5)); //���������ɫΪ��ɫ
    }
    ege_fillellipse(x1 - 23, y1 - 23, 46, 46);//����
    this->clear_prompt_right();//����Ҳ���ʾ����Ϣ
    this->round += 1;//�����������
    this->exchange();//����غ���ʾ��Ϣ
    this->clear_prompt_down();
    this->setNum();
    this->update();
}

void Graphic::clear_piece() { //���(x,y) ������
    if (this->round <= 0)return; //���������û������
    int x = this->p[this->round - 1].x, y = this->p[this->round - 1].y;
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    this->g[x][y] = 0;//������ӵ�״̬
    setfillcolor(EGEARGB(255, 189, 183, 107)); //���������ɫΪ��ɫ
    ege_fillellipse(x1 - 25, y1 - 25, 50, 50); //�������
    setcolor(EGEARGB(255, 5, 2, 2)); //����������ɫΪ��ɫ
    setlinewidth(3); //�����������
    ege_line(x1 - 25, y1, x1 + 25, y1);
    ege_line(x1, y1 - 25, x1, y1 + 25);
    if (x == 1 || x == this->L || y == 1 || y == this->L) { //��������ڱ߽�
        setfillcolor(EGEARGB(255, 82, 137, 11)); //���������ɫΪ��ɫ
        if (x == 1)ege_fillrect(x1 - 25, y1 - 25, 50, 23);
        if (y == 1)ege_fillrect(x1 - 25, y1 - 25, 23, 50);
        if (x == this->L)ege_fillrect(x1 - 25, y1 + 2, 50, 23);
        if (y == this->L)ege_fillrect(x1 + 2, y1 - 25, 23, 50);
    }
    //�������ڶ�λ��С��
    int x2 = (this->L + 1) / 2, y2 = (this->L + 1) / 2, l = (this->L + 1) / 4;
    if ((x == x2 && y == y2) || (x == x2 - l && y == y2 - l) || (x == x2 + l && y == y2 - l) ||
        (x == x2 - l && y == y2 + l) || (x == x2 + l && y == y2 + l)) {
        setfillcolor(EGEARGB(250, 2, 5, 5)); //���������ɫΪ��ɫ
        ege_fillellipse(x1 - 7, y1 - 7, 14, 14); //�������
    }
    this->round -= 1;//�����������
    this->exchange();//����غ���ʾ��Ϣ
    this->clear_prompt_right();//����Ҳ���ʾ����Ϣ
    this->clear_prompt_down();
    this->setNum();//���
    this->update();//ˢ��
}

void Graphic::setNum() { //Ϊ���ӱ��,���һ�����ӱ��Ϊ�죬��һ�����Ϊ����
    if (this->round <= 0)return;
    int x = this->p[this->round - 1].x, y = this->p[this->round - 1].y;
    int x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    //Ϊ��ǰ���ӱ��
    setcolor(RED), setfont(30, 0, "΢���ź�");
    if (this->round < 10)xyprintf(x1 - 7, y1 - 15, "%d", this->round);
    else if (this->round < 100)xyprintf(x1 - 13, y1 - 15, "%d", this->round);
    else xyprintf(x1 - 19, y1 - 15, "%d", this->round);
    if (this->round <= 1)return;
    //Ϊ��һ�����ӱ��
    x = this->p[this->round - 2].x, y = this->p[this->round - 2].y;
    x1 = this->lx + (y - 1) * 50, y1 = this->ly + (x - 1) * 50;
    if (this->round & 1)setcolor(BLACK);
    else setcolor(WHITE);
    //���Ʊ��
    if (this->round - 1 < 10)xyprintf(x1 - 7, y1 - 15, "%d", this->round - 1);
    else if (this->round - 1 < 100)xyprintf(x1 - 13, y1 - 15, "%d", this->round - 1);
    else xyprintf(x1 - 19, y1 - 15, "%d", this->round - 1);

}

int Graphic::getmouses() {//��ȡ�������Ϣ
    bool t = 1;
    while (mousemsg() || t) {
        mouse_msg msg = getmouse();
        if (msg.is_left() && msg.is_down()) {//���������Ϸ�ʱ���������ӵ��ӳ��
            int x = msg.x, y = msg.y;
            if (x >= this->lx && x <= this->lx + (this->L - 1) * 50 && y >= this->ly &&
                y <= this->ly + (this->L - 1) * 50) { //�����������
                x -= this->lx;
                y -= this->ly;
                int x1 = x / 50 * 50, y1 = y / 50 * 50;
                if (x - x1 > 25)x1 += 50;
                if (y - y1 > 25)y1 += 50;
                x1 /= 50, y1 /= 50;
                x1++, y1++;
                swap(x1, y1);
                if (!this->g[x1][y1])return x1 * (this->L + 1) + y1; //���õ�û������
            }
        } else if (msg.is_right() && msg.is_down()) { //���Ҽ����ʱ������-1����ʾ����
            return -1;
        }
    }
    return 0;
}

void Graphic::update() { //ˢ��
    int f = 0;
    for (; is_run(); delay_fps(60)) {
        f++;
        if (f > 3)break;
    }
}

void Graphic::clear_checkerboard() { //�������
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
////			x = (h / fp.L) + 1, y = (h % fp.L) + 1;//��ȡ�������
////			fp.drop_piece(x, y);
////		} else {//����
////			if (fp.round > 0)fp.clear_piece();
////		}
////		fp.print_prompt_down(5, 8);
////	}
//	//fp.clear_checkerboard();
//	return 0;
//}
