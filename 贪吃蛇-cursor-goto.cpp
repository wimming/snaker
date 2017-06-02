#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#define xsize 17
#define ysize 27
#define xedge 5
#define yedge 5
struct snake{
    int x;
    int y;
    char outlook;
    int arr;
};
struct position{
    int x;
    int y;
    char outlook;
};

void Gotoxy(int, int);

int main() {while (1) {
    system("color 70");
    system("cls");
    void HideCursor(); 
    HideCursor();
    char layout[xsize][ysize+1];  // 画面大小 
    char control;  // 键盘读入 
    struct position food;  // 结构体 食物 
    struct snake bit[900];  // 结构体 蛇的每节 
    struct snake end;  // 结构体 蛇尾 
    int lenth;  // 蛇长
    int speed;  // 速度（决定于难度） 
    int difficulty;  // 难度（决定于难度的字符串形式） 
    char cdifficulty[2];  // 难度的字符串形式 
    int isend;  // 是否结束游戏的标记，初始值为0，触发结束游戏条件时变为1 
    int grade;  // 分数 
    // 蛇的初始化 
    for (int i = 0; i < 900; i++) {
        bit[i].x = -1;
        bit[i].y = -1;
        bit[i].outlook = 4;
        bit[i].arr = 0;
    }
    bit[0].arr = 2;
    bit[0].outlook = 16;
    bit[0].x = 2;
    bit[0].y = 6;
    bit[1].outlook = 16;
    bit[1].x = 2;
    bit[1].y = 5;
    bit[2].outlook = 16;
    bit[2].x = 2;
    bit[2].y = 4;
    bit[3].outlook = 16;
    bit[3].x = 2;
    bit[3].y = 4;
    lenth = 3;
    // 蛇的初始化 完
    // 其他初始化 
    grade = 0;
    isend = 0;
    food.x = -1;
    food.y = -1;
    food.outlook = 15;
    // 其他初始化 完 
    // 难度选择 
    printf("选择难度（1~4之间）：");
    gets(cdifficulty);
    if (cdifficulty[0] == '1' && cdifficulty[1] == '\0') difficulty = 1;
    else if (cdifficulty[0] == '2' && cdifficulty[1] == '\0') difficulty = 2;
    else if (cdifficulty[0] == '3' && cdifficulty[1] == '\0') difficulty = 3;
    else if (cdifficulty[0] == '4' && cdifficulty[1] == '\0') difficulty = 4;
    else {
        printf("请输入正确的难度\n");
        system("pause");
        continue;
    }
    speed = pow(5-difficulty, 2);
    // 难度选择 完 
    // 初始化食物 
    srand(time(NULL));
    while (1) {
        food.x = (rand()%(xsize-2))+1;
        food.y = (rand()%(ysize-2))+1;
        int isok = 1;
        for (int i = 1; i <= lenth; i++)
        if (bit[i].x == food.x && bit[i].y == food.y)
        isok = 0;
        if (isok == 1) break;
    }
    // 初始化食物 完  
        // 初始化布局 
        for (int i = 0; i < xsize; i++)
        for (int j = 0; j < ysize; j++) {
            if ((i == 0 || i == (xsize-1)) && j != 0 && j != (ysize-1)) layout[i][j] = xedge;
            else if ((j == 0 || j == (ysize-1)) && i != 0 && i != (xsize-1)) layout[i][j] = yedge;
            else if (i == 0 && j == 0) layout[i][j] = 5;
            else if (i == 0 && j == (ysize-1)) layout[i][j] = 5;
            else if (i == (xsize-1) && j == 0) layout[i][j] = 5;
            else if (i == (xsize-1) && j == (ysize-1)) layout[i][j] = 5;
            else layout[i][j] = ' ';
        }
        // 初始化布局 完 
        // 布局 
        for (int x = 0; x < xsize; x++) {
            for (int y = 0; y < ysize; y++) {
                if (food.x == x && food.y == y) layout[x][y] = food.outlook;
                for (int i = 0; i <= lenth; i++) {
                    if (bit[i].x == x && bit[i].y == y) {
                        layout[x][y] = bit[i].outlook;
                        break;
                    }
                }
            }
            layout[x][ysize] = '\0';
        }
        // 布局 完 
        // 显示区 
        system("cls");
        for (int x = 0; x < xsize; x++) {
            for (int y = 0; y < ysize; y++)
            printf("%c", layout[x][y]);
            printf("\n");
        }
        printf("难度：%d\n\n\n", difficulty);
        printf("w s a d 控制移动，r 重新开始，空格键 暂停游戏, ESC 结束游戏\n\n");
        // 显示区 完 
    while (1) {
		Sleep(speed*40);  // 时间间隔 
        // 记录蛇尾待用 
        end.x = bit[lenth].x;
        end.y = bit[lenth].y;
        end.outlook = bit[lenth].outlook;
        // 记录蛇尾待用 完 
        // 控制区 
        if (!kbhit()) {
            for (int i = lenth; i >= 1; i--) {
                bit[i].x = bit[i-1].x;
                bit[i].y = bit[i-1].y;
                bit[i].outlook = bit[i-1].outlook;
            }
            if (bit[0].arr == 1) bit[0].x += 1;
            if (bit[0].arr == 2) bit[0].y += 1;
            if (bit[0].arr == 3) bit[0].x -= 1;
            if (bit[0].arr == 4) bit[0].y -= 1;
        } else {
            control = getch();
            if (control == 'd') {
                if (bit[0].arr == 4) {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    if (bit[0].arr == 1) bit[0].x += 1;
                    if (bit[0].arr == 2) bit[0].y += 1;
                    if (bit[0].arr == 3) bit[0].x -= 1;
                    if (bit[0].arr == 4) bit[0].y -= 1;
                } else {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    bit[0].y += 1;
                    bit[0].arr = 2;
                    bit[0].outlook = 16;
                }
            }
            else if (control == 's') {
                if (bit[0].arr == 3) {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    if (bit[0].arr == 1) bit[0].x += 1;
                    if (bit[0].arr == 2) bit[0].y += 1;
                    if (bit[0].arr == 3) bit[0].x -= 1;
                    if (bit[0].arr == 4) bit[0].y -= 1;
                } else {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    bit[0].x += 1;
                    bit[0].arr = 1;
                    bit[0].outlook = 31;
                }
            }
            else if (control == 'a') {
                if (bit[0].arr == 2) {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    if (bit[0].arr == 1) bit[0].x += 1;
                    if (bit[0].arr == 2) bit[0].y += 1;
                    if (bit[0].arr == 3) bit[0].x -= 1;
                    if (bit[0].arr == 4) bit[0].y -= 1;
                } else {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    bit[0].y -= 1;
                    bit[0].arr = 4;
                    bit[0].outlook = 17;
                }
            }
            else if (control == 'w') {
                if (bit[0].arr == 1) {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    if (bit[0].arr == 1) bit[0].x += 1;
                    if (bit[0].arr == 2) bit[0].y += 1;
                    if (bit[0].arr == 3) bit[0].x -= 1;
                    if (bit[0].arr == 4) bit[0].y -= 1;
                } else {
                    for (int i = lenth; i >= 1; i--) {
                        bit[i].x = bit[i-1].x;
                        bit[i].y = bit[i-1].y;
                        bit[i].outlook = bit[i-1].outlook;
                    }
                    bit[0].x -= 1;
                    bit[0].arr = 3;
                    bit[0].outlook = 30;
                }
            }
            else if (control == 'r') {
                break;
            }
            else if (control == ' ') {
                Gotoxy(xsize+5, 0);
                system("pause");
                Gotoxy(xsize+5, 0);
                printf("                        ");
            }
            else if (control == 27) {
                return 0;
            }
            else {
                for (int i = lenth; i >= 1; i--) {
                    bit[i].x = bit[i-1].x;
                    bit[i].y = bit[i-1].y;
                    bit[i].outlook = bit[i-1].outlook;
                }
                if (bit[0].arr == 1) bit[0].x += 1;
                if (bit[0].arr == 2) bit[0].y += 1;
                if (bit[0].arr == 3) bit[0].x -= 1;
                if (bit[0].arr == 4) bit[0].y -= 1;
            }
        }
        // 控制区 完 
        if (food.x == bit[1].x && food.y == bit[1].y) {
            bit[lenth+1].x = end.x;
            bit[lenth+1].y = end.y;
            bit[lenth+1].outlook = end.outlook;
            lenth += 1;
            grade += difficulty;
            while (1) {
                food.x = (rand()%(xsize-2))+1;
                food.y = (rand()%(ysize-2))+1;
                int isok = 1;
                for (int i = 1; i <= lenth; i++)
                if (bit[i].x == food.x && bit[i].y == food.y)
                isok = 0;
                if (isok == 1) break;
            }
        }
        // 显示区 
        Gotoxy(bit[lenth].x, bit[lenth].y);
        printf(" ");
        Gotoxy(food.x, food.y);
        printf("%c", food.outlook);
        Gotoxy(bit[0].x, bit[0].y);
        printf("%c", bit[0].outlook);
        // 显示区 完 
        // 结束区 
        if (0 == bit[0].x || 0 == bit[0].y || (xsize-1) == bit[0].x || (ysize-1) == bit[0].y) {
            isend = 1;
            Gotoxy(xsize/2-1, 0);
            printf("\a游戏结束！！请再接再厉\n得分：%d\n", grade);
            Gotoxy(xsize+5, 0);
            system("pause");
        }
        for (int i = 1; i < lenth; i++) if (bit[i].x == bit[0].x && bit[i].y == bit[0].y){
            isend = 1;
            Gotoxy(xsize/2-1, 0);
            printf("\a游戏结束！！请再接再厉\n得分：%d\n", grade);
            Gotoxy(xsize+5, 0);
            system("pause");
            break;
        }
        if (isend == 1) break;
        // 结束区 完 
    }}
}

// 以下函数均引用他人 包括注释 
void HideCursor()
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Gotoxy(int x, int y) //移动光标
{
HANDLE hout; //定义句柄变量hout
COORD coord; //定义结构体coord
coord.Y = x;
coord.X = y;
hout = GetStdHandle(STD_OUTPUT_HANDLE); //获得标准输出（屏幕）句柄
SetConsoleCursorPosition(hout, coord); //移动光标
}

