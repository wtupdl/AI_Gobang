#include"head.h"
int tt = 0;

AiCalcule::AiCalcule(int L) {//构造函数，初始化
    this->L = L;//棋盘规格
    memset(this->p, this->Vacancy, sizeof(this->p));//棋盘初始化为无棋子
    memset(this->d, 0, sizeof(this->d));//各赢法得分为0
    memset(this->data, 0, sizeof(this->data));
    memset(this->f, 0, sizeof(this->f));
    this->cp = (node *) malloc(300 * sizeof(node)); //存放走法顺序
    this->creat_grade();//保存棋型得分
}

int AiCalcule::getgrade(int x, int y) { //评估落子点（x，y）的得分，用于启发式搜索
    int r1 = 0, r2 = 0;
    int res1, res2, x1, y1;
    //横向更新，方向为1
    res1 = 0, res2 = 0, x1 = x, y1 = max(1, y - 5);
    for (int i = 0; i < 6; i++) {
        if (y1 + i == y) {
            res1 = res1 * 10 + this->Initiative;
            res2 = res2 * 10 + this->Gote;
        } else {
            res1 = res1 * 10 + this->p[x1][y1 + i]; //计算出第一个棋型
            res2 = res2 * 10 + this->p[x1][y1 + i]; //计算出第一个棋型
        }
    }
    r1 += this->data[res1]; //更新该赢法得分
    r2 += this->data[res2];
    y1++;
    while (y1 + 5 <= this->L && y1 <= y) {
        res1 = (res1 % 100000) * 10 + this->p[x1][y1 + 5];
        res2 = (res2 % 100000) * 10 + this->p[x1][y1 + 5];
        r1 += this->data[res1]; //更新该赢法得分
        r2 += this->data[res2];
        y1++;
    }
    //纵向更新，方向为2
    res1 = 0, res2 = 0, x1 = max(1, x - 5), y1 = y;
    for (int i = 0; i < 6; i++) {
        if (x1 + i == x) {
            res1 = res1 * 10 + this->Initiative;
            res2 = res2 * 10 + this->Gote;
        } else {
            res1 = res1 * 10 + this->p[x1 + i][y1]; //计算出第一个棋型
            res2 = res2 * 10 + this->p[x1 + i][y1]; //计算出第一个棋型
        }
    }
    r1 += this->data[res1]; //更新该赢法得分
    r2 += this->data[res2];
    x1++;
    while (x1 + 5 <= this->L && x1 <= x) {
        res1 = (res1 % 100000) * 10 + this->p[x1 + 5][y1];
        res2 = (res2 % 100000) * 10 + this->p[x1 + 5][y1];
        r1 += this->data[res1]; //更新该赢法得分
        r2 += this->data[res2];
        x1++;
    }
    //左上到右下更新
    res1 = 0, res2 = 0, x1 = x - min(x - 1, min(y - 1, 5)), y1 = y - min(x - 1, min(y - 1, 5));
    if (min(this->L - x1 + 1, this->L - y1 + 1) == 5) { //当前赢法只有五个子
        for (int i = 0; i < 5; i++) {
            if (x1 + i == x && y1 + i == y) {
                res1 = res1 * 10 + this->Initiative;
                res2 = res2 * 10 + this->Gote;
            } else {
                res1 = res1 * 10 + this->p[x1 + i][y1 + i];
                res2 = res2 * 10 + this->p[x1 + i][y1 + i];
            }
        }
        res1 = res1 + this->Gote * 100000;
        res2 = res2 + this->Initiative * 100000;
        r1 += this->data[res1]; //更新该赢法得分
        r2 += this->data[res2]; //更新该赢法得分
    } else if (min(this->L - x1 + 1, this->L - y1 + 1) > 5) { //当前赢法超过五个
        for (int i = 0; i < 6; i++) {
            if (x1 + i == x && y1 + i == y) {
                res1 = res1 * 10 + this->Initiative;
                res2 = res2 * 10 + this->Gote;
            } else {
                res1 = res1 * 10 + this->p[x1 + i][y1 + i];
                res2 = res2 * 10 + this->p[x1 + i][y1 + i];
            }
        }
        r1 += this->data[res1]; //更新该赢法得分
        r2 += this->data[res2]; //更新该赢法得分
        x1++, y1++;
        while (x1 + 5 <= this->L && x1 <= x && y1 + 5 <= this->L && y1 <= y) {
            res1 = (res1 % 100000) * 10 + this->p[x1 + 5][y1 + 5];
            res2 = (res2 % 100000) * 10 + this->p[x1 + 5][y1 + 5];
            r1 += this->data[res1]; //更新该赢法得分
            r2 += this->data[res2]; //更新该赢法得分
            x1++, y1++;
        }
    }
    //左下到右上更新
    res1 = 0, res2 = 0, x1 = x + min(this->L - x, min(y - 1, 5)), y1 = y - min(this->L - x, min(y - 1, 5));
    if (min(x1, this->L - y1 + 1) == 5) { //当前赢法只有五个子
        for (int i = 0; i < 5; i++) {
            if (x1 - i == x && y1 + i == y) {
                res1 = res1 * 10 + this->Initiative;
                res2 = res2 * 10 + this->Gote;
            } else {
                res1 = res1 * 10 + this->p[x1 - i][y1 + i];
                res2 = res2 * 10 + this->p[x1 - i][y1 + i];
            }
        }
        res1 = res1 + this->Gote * 100000;
        res2 = res2 + this->Initiative * 100000;
        r1 += this->data[res1]; //更新该赢法得分
        r2 += this->data[res2]; //更新该赢法得分
    } else if (min(x1, this->L - y1 + 1) > 5) { //当前赢法超过五个
        for (int i = 0; i < 6; i++) {
            if (x1 - i == x && y1 + i == y) {
                res1 = res1 * 10 + this->Initiative;
                res2 = res2 * 10 + this->Gote;
            } else {
                res1 = res1 * 10 + this->p[x1 - i][y1 + i];
                res2 = res2 * 10 + this->p[x1 - i][y1 + i];
            }
        }
        r1 += this->data[res1]; //更新该赢法得分
        r2 += this->data[res2]; //更新该赢法得分
        x1--, y1++;
        while (x1 - 5 >= 1 && x1 >= x && y1 + 5 <= this->L && y1 <= y) {
            res1 = (res1 % 100000) * 10 + this->p[x1 - 5][y1 + 5];
            res2 = (res2 % 100000) * 10 + this->p[x1 - 5][y1 + 5];
            r1 += this->data[res1]; //更新该赢法得分
            r2 += this->data[res2]; //更新该赢法得分
            x1--, y1++;

        }

    }
    return abs(r1) + abs(r2);
    //if(this->round&1)return abs(r1) +abs(r2)/2;
    //else return abs(r1)/2 +abs(r2);
}

void AiCalcule::heap_sort(node *p, int len) {
    //sort(p+1,p+len+1);
    //return;
    if (len <= 15) {
        sort(p + 1, p + len + 1);
    } else {
        for (int i = 7; i >= 1; --i) //1.创建堆make_heap, 从最后一个非叶子节点开始
            adjust_heap(p, i, 15);
        for (int i = 16; i <= len; i++) {
            if (p[i] < p[1]) {
                p[1] = p[i];
                adjust_heap(p, 1, 15);
            }
        }
        for (int i = 15; i >= 1; --i) { //2. 堆排序, 此时 [1, len] 为一个堆
            swap(p[1], p[i]);      //将　堆顶元素(数组首位)　与　堆末元素(数组末位) 互换.
            adjust_heap(p, 1, i - 1); // 此时堆末元素已经有序(存的是最大值),
        }// 剩余堆的范围变成了 [1, len-1], 但由于上一步的交换可能破坏堆的性质, 故要进行调整

    }
}

void AiCalcule::adjust_heap(node *p, int f, int len) {
    int l, r;
    int m = 0;
    p[0] = p[f];
    while (1) {
        l = f << 1, r = f << 1 | 1;
        if (l <= len && p[l] > p[m])m = l;
        if (r <= len && p[r] > p[m])m = r;
        if (m != 0) {
            p[f] = p[m];
            f = m;
            m = 0;
        } else {
            p[f] = p[0];
            return;
        }
    }
}

node AiCalcule::getInitiative(int T, Graphic qd) { //获取先手最优解法
    if (this->round == 0)return node(8, 8, 0);
    node pr(0, 0, -this->inf * 8);
    int l = 0;
    node *op = (node *) malloc(225 * sizeof(node));
    for (int i = 1; i <= this->L; i++) {
        for (int j = 1; j <= this->L; j++) {
            if (this->p[i][j] == this->Vacancy && this->upcf(i, j)) {
                op[l++] = node(i, j, this->getgrade(i, j));
            }
        }
    }
    sort(op, op + l); //排序
    clock_t startTime, endTime;
    for (int i = 0; i < min(l, 15); i++) {
        int x = op[i].x, y = op[i].y;
        int v;
        tt = 0;
        startTime = clock();//计时开始
        this->dropPiece(x, y);
        for (int k = 1; k < T; k += 2) { //迭代加深搜索
            v = this->dfs(k, this->Gote, -this->inf * 4, this->inf * 4);
            if (v > this->inf / 2)break;
        }
        this->clearPiece(x, y);
        endTime = clock();//时结束
        double t = (double) (endTime - startTime) / CLOCKS_PER_SEC; //时间转为s
        qd.print_prompt_right(x, y, tt, v, t, i); //打印右边提示，位置，计算次数，得分，写在第几行
        if (v > pr.grade)pr.set(x, y, v); //得到更优解法
        if (v > this->inf / 2)break;
    }
    free(op);
    return pr;
}

node AiCalcule::getGote(int T, Graphic qd) { //获取后手最优解法
    //if (this->round == 1)return node(7, 7, 0);
    node pr(2, 2, this->inf * 8);
    int l = 0;
    int x1 = this->cp[0].x, y1 = this->cp[0].y;
    node *op = (node *) malloc(225 * sizeof(node));
    for (int i = 1; i <= this->L; i++) {
        for (int j = 1; j <= this->L; j++) {
            if (this->p[i][j] == this->Vacancy && this->upcf(i, j)) {
                //op[l++] = node(i, j, this->getgrade(i, j));
                if (this->round > 1)op[l++] = node(i, j, this->getgrade(i, j));
                if (this->round == 1 && abs(i - x1) <= 1 && abs(j - y1) <= 1)op[l++] = node(i, j, this->getgrade(i, j));

            }
        }
    }
    sort(op, op + l); //排序
    clock_t startTime, endTime;
    for (int i = 0; i < min(l, 15); i++) {
        int x = op[i].x, y = op[i].y;
        int v;
        tt = 0;
        startTime = clock();//计时开始
        this->dropPiece(x, y);
        for (int k = 1; k < T; k += 2) { //迭代加深搜索
            v = this->dfs(k, this->Initiative, -this->inf * 4, this->inf * 4);
            if (v < -this->inf / 2)break;
        }
        this->clearPiece(x, y);
        endTime = clock();//计时结束
        double t = (double) (endTime - startTime) / CLOCKS_PER_SEC; //时间转为s
        qd.print_prompt_right(x, y, tt, v, t, i);
        if (v < pr.grade)pr.set(x, y, v); //得到更优解法
        if (v < -this->inf / 2)break;
    }
    free(op);
    return pr;
}

int AiCalcule::dfs(int T, int piece, int a, int b) {
    if (T == 0 || this->gameover() != 0)return this->grade;
    tt++;
    if (piece == this->Initiative) { //先手回合，max层
        int l = 1;
        node *op = (node *) malloc(225 * sizeof(node));
        for (int i = 1; i <= this->L; i++) {
            for (int j = 1; j <= this->L; j++) {
                if (this->p[i][j] == this->Vacancy && this->upcf(i, j)) {
                    op[l++].set(i, j, this->getgrade(i, j));
                }
            }
        }
        l--;
        this->heap_sort(op, l); //排序
        //sort(op, op + l); //排序
        int v = -this->inf << 3;
        for (int i = 1; i <= min(15, l); i++) {
            int x = op[i].x, y = op[i].y;
            this->dropPiece(x, y);
            v = max(v, this->dfs(T - 1, this->Gote, a, b));
            this->clearPiece(x, y);
            a = max(a, v);
            if (a >= b)break; //ab剪枝
        }
        free(op);
        return v;
    } else { //后手回合，min层
        int l = 1;
        node *op = (node *) malloc(225 * sizeof(node));
        for (int i = 1; i <= this->L; i++) {
            for (int j = 1; j <= this->L; j++) {
                if (this->p[i][j] == this->Vacancy && this->upcf(i, j)) {
                    op[l++].set(i, j, this->getgrade(i, j));
                }
            }
        }
        l--;
        this->heap_sort(op, l); //排序
        //sort(op, op + l); //排序
        int v = this->inf << 3;
        for (int i = 1; i <= min(15, l); i++) {
            int x = op[i].x, y = op[i].y;
            this->dropPiece(x, y);
            v = min(v, this->dfs(T - 1, this->Initiative, a, b));
            this->clearPiece(x, y);
            b = min(b, v);
            if (a >= b)break; //ab剪枝
        }
        free(op);
        return v;
    }
}

int AiCalcule::gameover() { //判断游戏输赢（-1,0,1，2）：后手胜，未结束，先手胜，平
    if (this->grade >= this->inf / 2)return 1; //先手胜
    else if (this->grade <= -this->inf / 2) return -1; //后手胜
    else if (this->round >= this->L * this->L) return 2; //平局
    else return 0;//游戏继续
}

bool AiCalcule::upcf(int x, int y) { //判断该点是否可下
    return this->f[x][y];
}

void AiCalcule::dropPiece(int x, int y) { //落子,结果不存放在cp数组中
    int piece = this->round % 2 == 0 ? this->Initiative : this->Gote; //判断落黑还是落白
    this->p[x][y] = piece;
    this->update(x, y); //更新局面得分
    this->round++;
    for (int i = 1; i <= 3; i++) { //更新f数组
        if (x + i <= this->L) {
            ++this->f[x + i][y];
            if (y + i <= this->L) {
                ++this->f[x + i][y + i];
            }
            if (y - i >= 1) {
                ++this->f[x + i][y - i];
            }
        }
        if (x - i >= 1) {
            ++this->f[x - i][y];
            if (y + i <= this->L)++this->f[x - i][y + i];
            if (y - i >= 1)++this->f[x - i][y - i];
        }
        if (y + i <= this->L)++this->f[x][y + i];
        if (y - i >= 1)++this->f[x][y - i];
    }
}

void AiCalcule::dropPiece(int x, int y, bool g) { //在位置（x,y）落子,结果存放在cp数组中
    this->cp[this->round].set(x, y, 0); //存放走法
    this->dropPiece(x, y); //落子
}

void AiCalcule::clearPiece(int x, int y) { //清除棋子
    this->p[x][y] = this->Vacancy;
    this->update(x, y); //更新局面得分
    this->round--;
    for (int i = 1; i <= 3; i++) { //更新f数组
        if (x + i <= this->L) {
            --this->f[x + i][y];
            if (y + i <= this->L) {
                --this->f[x + i][y + i];
            }
            if (y - i >= 1) {
                --this->f[x + i][y - i];
            }
        }
        if (x - i >= 1) {
            --this->f[x - i][y];
            if (y + i <= this->L) {
                --this->f[x - i][y + i];
            }
            if (y - i >= 1) {
                --this->f[x - i][y - i];
            }
        }
        if (y + i <= this->L)--this->f[x][y + i];
        if (y - i >= 1)--this->f[x][y - i];
    }
}

void AiCalcule::clearPiece() { //清除最后一步的落子
    if (this->round <= 0)return;
    int x = this->cp[this->round - 1].x;
    int y = this->cp[this->round - 1].y;
    this->clearPiece(x, y);
}

void AiCalcule::upgrade(int x, int y, int t, int res) { //更新赢法得分
    this->grade -= this->d[x][y][t];
    this->d[x][y][t] = this->data[res];
    this->grade += this->d[x][y][t];
}

void AiCalcule::update(int x, int y) { //更新局面得分
    int res, x1, y1;
    //横向更新，方向为1
    res = 0, x1 = x, y1 = max(1, y - 5);
    for (int i = 0; i < 6; i++)res = res * 10 + this->p[x1][y1 + i]; //计算出第一个棋型
    this->upgrade(x1, y1, 1, res); //更新该赢法得分
    y1++;
    while (y1 + 5 <= this->L && y1 <= y) {
        res = (res % 100000) * 10 + this->p[x1][y1 + 5];
        this->upgrade(x1, y1, 1, res); //更新该赢法得分
        y1++;
    }
    //纵向更新，方向为2
    res = 0, x1 = max(1, x - 5), y1 = y;
    for (int i = 0; i < 6; i++)res = res * 10 + this->p[x1 + i][y1]; //计算出第一个棋型
    this->upgrade(x1, y1, 2, res); //更新该赢法得分
    x1++;
    while (x1 + 5 <= this->L && x1 <= x) {
        res = (res % 100000) * 10 + this->p[x1 + 5][y1];
        this->upgrade(x1, y1, 2, res); //更新该赢法得分
        x1++;
    }
    //左上到右下更新
    res = 0, x1 = x - min(x - 1, min(y - 1, 5)), y1 = y - min(x - 1, min(y - 1, 5));
    if (min(this->L - x1 + 1, this->L - y1 + 1) == 5) { //当前赢法只有五个子
        bool c1 = 0;
        for (int i = 0; i < 5; i++) {
            res = res * 10 + this->p[x1 + i][y1 + i];
            if (this->p[x1 + i][y1 + i] == this->Gote)c1 = 1;
        }
        if (c1)res = this->Initiative * 100000 + res;
        else res = this->Gote * 100000 + res;
        this->upgrade(x1, y1, 3, res); //更新该赢法得分
    } else if (min(this->L - x1 + 1, this->L - y1 + 1) > 5) { //当前赢法超过五个
        for (int i = 0; i < 6; i++)res = res * 10 + this->p[x1 + i][y1 + i]; //计算出第一个棋型
        this->upgrade(x1, y1, 3, res); //更新该赢法得分
        x1++, y1++;
        while (x1 + 5 <= this->L && x1 <= x && y1 + 5 <= this->L && y1 <= y) {
            res = (res % 100000) * 10 + this->p[x1 + 5][y1 + 5];
            this->upgrade(x1, y1, 3, res); //更新该赢法得分
            x1++, y1++;
        }
    }
    //左下到右上更新
    res = 0, x1 = x + min(this->L - x, min(y - 1, 5)), y1 = y - min(this->L - x, min(y - 1, 5));
    if (min(x1, this->L - y1 + 1) == 5) { //当前赢法只有五个子
        bool c1 = 0;
        for (int i = 0; i < 5; i++) {
            res = res * 10 + this->p[x1 - i][y1 + i];
            if (this->p[x1 - i][y1 + i] == this->Initiative)c1 = 1;
        }
        if (c1)res = this->Gote * 100000 + res;
        else res = this->Initiative * 100000 + res;
        this->upgrade(x1, y1, 4, res); //更新该赢法得分
    } else if (min(x1, this->L - y1 + 1) > 5) { //当前赢法超过五个
        for (int i = 0; i < 6; i++)res = res * 10 + this->p[x1 - i][y1 + i]; //计算出第一个棋型
        this->upgrade(x1, y1, 4, res); //更新该赢法得分
        x1--, y1++;
        while (x1 - 5 >= 1 && x1 >= x && y1 + 5 <= this->L && y1 <= y) {
            res = (res % 100000) * 10 + this->p[x1 - 5][y1 + 5];
            this->upgrade(x1, y1, 4, res); //更新该赢法得分
            x1--, y1++;
        }
    }
}

void AiCalcule::creat_grade() {//保存棋型得分
    int lw, hs, cs, hr, cr, hy, cy;
    // 连五inf
    lw = this->inf;
    this->data[111111] = this->data[111110] = this->data[111112] = this->data[11111] = this->data[211111] = lw;
    lw = -this->inf;
    this->data[222222] = this->data[222220] = this->data[222221] = this->data[22222] = this->data[122222] = lw;
    // 活四500000
    hs = 10000;
    this->data[11110] = hs;
    hs = -10000;
    this->data[22220] = hs;
    // 冲四1000
    cs = 1000;
    this->data[1111] = this->data[201111] = this->data[211110] = this->data[11112] = cs;
    this->data[111100] = this->data[111102] = this->data[11011] = this->data[211011] = cs;
    this->data[110110] = this->data[110112] = this->data[101110] = this->data[101112] = cs;
    this->data[10111] = this->data[210111] = this->data[111010] = this->data[111012] = cs;
    this->data[11101] = this->data[211101] = cs;
    cs = -1000;
    this->data[2222] = this->data[102222] = this->data[122220] = this->data[22221] = cs;
    this->data[222200] = this->data[222201] = this->data[22022] = this->data[122022] = cs;
    this->data[220220] = this->data[220221] = this->data[202220] = this->data[202221] = cs;
    this->data[20222] = this->data[120222] = this->data[222020] = this->data[222021] = cs;
    this->data[22202] = this->data[122202] = cs;
    // 活三1000
    hs = 1000;
    this->data[1110] = this->data[11100] = this->data[10110] = this->data[11010] = hs;
    hs = -1000;
    this->data[2220] = this->data[22200] = this->data[20220] = this->data[22020] = hs;
    // 冲三100
    cs = 100;
    this->data[111002] = this->data[111000] = this->data[11102] = this->data[211100] = cs;
    this->data[1112] = this->data[201110] = this->data[111] = this->data[200111] = cs;
    this->data[101100] = this->data[101102] = this->data[210110] = this->data[10112] = cs;
    this->data[1011] = this->data[201011] = this->data[110100] = this->data[110102] = cs;
    this->data[211010] = this->data[11012] = this->data[1101] = this->data[201101] = cs;
    this->data[10011] = this->data[210011] = this->data[100110] = this->data[100112] = cs;
    this->data[11001] = this->data[211001] = this->data[110010] = this->data[110012] = cs;
    this->data[10101] = this->data[210101] = this->data[101010] = this->data[101012] = cs;
    cs = -100;
    this->data[222001] = this->data[222000] = this->data[22201] = this->data[122200] = cs;
    this->data[2221] = this->data[102220] = this->data[222] = this->data[100222] = cs;
    this->data[202200] = this->data[202201] = this->data[120220] = this->data[20221] = cs;
    this->data[2022] = this->data[102022] = this->data[220200] = this->data[220201] = cs;
    this->data[122020] = this->data[22021] = this->data[2202] = this->data[102202] = cs;
    this->data[20022] = this->data[120022] = this->data[200220] = this->data[200221] = cs;
    this->data[22002] = this->data[122002] = this->data[220020] = this->data[220021] = cs;
    this->data[20202] = this->data[120202] = this->data[202020] = this->data[202021] = cs;
    // 活二100
    hr = 100;
    this->data[11000] = this->data[1100] = this->data[110] = this->data[10100] = hr;
    this->data[1010] = this->data[10010] = hr;
    hr = -100;
    this->data[22000] = this->data[2200] = this->data[220] = this->data[20200] = hr;
    this->data[2020] = this->data[20020] = hr;
    // 冲二10
    cr = -10;
    this->data[110000] = this->data[110002] = this->data[211000] = this->data[11002] = cr;
    this->data[201100] = this->data[1102] = this->data[200110] = this->data[112] = cr;
    this->data[11] = this->data[200011] = this->data[101000] = this->data[101002] = cr;
    this->data[210100] = this->data[10102] = this->data[201010] = this->data[1012] = cr;
    this->data[101] = this->data[200101] = this->data[100100] = this->data[210010] = cr;
    this->data[10012] = this->data[1001] = cr;
    cr = -10;
    this->data[220000] = this->data[220001] = this->data[122000] = this->data[22001] = cr;
    this->data[102200] = this->data[2201] = this->data[100220] = this->data[221] = cr;
    this->data[22] = this->data[100022] = this->data[202000] = this->data[202001] = cr;
    this->data[120200] = this->data[20201] = this->data[102020] = this->data[2021] = cr;
    this->data[202] = this->data[100202] = this->data[200200] = this->data[120020] = cr;
    this->data[20021] = this->data[2002] = cr;
    // 活一1
    /*
    hy = 0;
    this->data[10000] = this->data[1000] = this->data[100] = this->data[10] = hy;
    hy = 0;
    this->data[20000] = this->data[2000] = this->data[200] = this->data[20] = hy;
    // 冲一0
    cy = 0;
    this->data[100000] = this->data[100002] = this->data[210000] = this->data[10002] = cy;
    this->data[201000] = this->data[1002] = this->data[200100] = this->data[102] = cy;
    this->data[200010] = this->data[12] = this->data[1] = this->data[200001] = cy;
    this->data[200000] = this->data[200001] = this->data[120000] = this->data[20001] = -cy;
    this->data[102000] = this->data[2001] = this->data[100200] = this->data[201] = -cy;
    this->data[100020] = this->data[21] = this->data[2] = this->data[100002] = -cy;
    */
}

void AiCalcule::ds() {//打印棋盘
    for (int i = 0; i < this->L; i++) {
        for (int j = 0; j < this->L; j++) {
            if (this->p[i][j] != 0)cout << this->p[i][j] << " ";
            else cout << "  ";
        }
        cout << endl;
    }
    cout << endl;
}
