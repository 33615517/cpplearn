#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#include <string.h>
#pragma comment(lib,"winmm.lib")

#define max_n 20
#define MAX_RANK 10
int volume = 78;

/*
* 控制台工具
*/
void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void gotoXY(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void clear(int x, int y, int w, int h)
{
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; j++) putchar(' ');
    }
}
void SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void setPrintColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//----------------------------数据设计--------------------------------------
int bomb[max_n][max_n];
int show[max_n][max_n];
int bombcount;
int n;

int curX = 0;
int curY = 0;
int menuSel = 0;

//---------------------排行榜预制数据-----------------------
typedef struct
{
    char name[20];
    int time;
}Rank;
Rank rank[MAX_RANK] = {
    {"云海学长",12},
    {"东东哥",18},
    {"吴祖镕",25},
    {"淡烦",33},
    {"x",114514}
};
int rank_num = 5;

void rankview()
{
    system("cls");
    //冒泡排序
    for (int i = 0; i < rank_num - 1; i++)
    {
        for (int j = 0; j < rank_num - 1 - i; j++)
        {
            if (rank[j].time > rank[j + 1].time)
            {
                Rank temp = rank[j];
                rank[j] = rank[j + 1];
                rank[j + 1] = temp;
            }
        }
    }

    //打印排行榜
    printf("==========================\n");
    printf("        扫雷排行榜\n");
    printf("==========================\n");
    printf("名次    姓名      用时(秒)\n");
    printf("--------------------------\n");
    for (int i = 0; i < rank_num; i++)
    {
        printf("%2d     %-8s   %d\n", i + 1, rank[i].name, rank[i].time);
    }
    printf("==========================\n");
    printf("按任意键返回菜单\n");
    _getch();
}

//----------------------------service-----------------------------------
void Initmap()
{
    int i, j;
    for (i = 0; i < max_n; i++)
    {
        for (j = 0; j < max_n; j++)
            bomb[i][j] = 0;
    }
    for (i = 0; i < max_n; i++)
    {
        for (j = 0; j < max_n; j++)
            show[i][j] = 0;
    }
}

void setbomb()
{
    int count = 0;
    int x, y;
    srand((unsigned int)time(NULL));
    while (count < bombcount)
    {
        x = rand() % n;
        y = rand() % n;
        if (bomb[x][y] == 0)
        {
            bomb[x][y] = 1;
            count++;
        }
    }
}

int around_bomb(int x, int y)
{
    int bll_count = 0;
    for (int i = y - 1; i <= y + 1; i++)
    {
        if (i >= 0 && i < n)
        {
            for (int j = x - 1; j <= x + 1; j++)
            {
                if (j >= 0 && j < n)
                {
                    if (!(i == y && j == x))
                    {
                        if (bomb[i][j] == 1)
                        {
                            bll_count++;
                        }
                    }
                }
            }
        }
    }
    return bll_count;
}

int iswin()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (bomb[i][j] == 0 && show[i][j] != 1) {
                return 0;
            }
        }
    }
    return 1;
}

int playermove(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        return 0;
    }

    if (show[y][x] == 1 || show[y][x] == 2) {
        return 0;
    }

    if (bomb[y][x] == 1) {
        show[y][x] = 1;
        return 2;
    }

    show[y][x] = 1;

    if (around_bomb(x, y) == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i != 0 || j != 0) {
                    if (y + i >= 0 && y + i < n && x + j >= 0 && x + j < n && show[y + i][x + j] == 0) {
                        playermove(x + j, y + i);
                    }
                }
            }
        }
    }

    return 1;
}

int add_flag(int x, int y)
{
    if (show[y][x] == 0)
    {
        show[y][x] = 2;
        return 1;
    }
    else if (show[y][x] == 2)
    {
        show[y][x] = 0;
        return 2;
    }
    else
    {
        return 0;
    }
}

int timer(int sui)
{
    static long long start = 0;
    if (sui == -1)
    {
        start = time(NULL);
        return 0;
    }
    long long now = time(NULL);
    return (int)(now - start);
}

void selectlevel()
{
    int choice;
    system("cls");
    printf("==========================\n");
    printf("      请选择游戏难度\n");
    printf("==========================\n");
    printf("  1. 初级 (9x9,   10颗地雷)\n");
    printf("  2. 中级 (12x12, 20颗地雷)\n");
    printf("  3. 高级 (16x16, 30颗地雷)\n");
    printf("==========================\n");
    printf("请按对应数字键选择：\n");
    choice = _getch();
    switch (choice)
    {
    case '1': n = 9;   bombcount = 10; break;
    case '2': n = 12;  bombcount = 20; break;
    case '3': n = 16;  bombcount = 30; break;
    default:  n = 9;    bombcount = 10; break;
    }
    Initmap();
    setbomb();
}

void teamview()
{
    system("cls");
    printf("\t团队成员\n");
    printf("\t组长：吴祖镕\n");
    printf("\t副组长：could\n");
    printf("\t架构师：王展翼\n");
    printf("\t技术官：淡烦\n");
    printf("\t产品经理：随缘随性随心\n");
    printf("\t产品经理：。\n");
    printf("\t开发人员：布噜噜\n");
    printf("\t开发人员：。\n");
    printf("\t------------------------------\n");
    printf("\t分工：\n");
    printf("\t吴祖镕：setbomb函数、selectlevel函数\n");
    printf("\tcould：loseview函数、winview函数\n");
    printf("\t王展翼：rankview函数、gameview-Show函数\n");
    printf("\t淡烦：iswin函数、playmove函数\n");
    printf("\t随缘随性随心：timer函数、setting函数\n");
    printf("\t（产品经理）。：menuview函数、gameview函数\n");
    printf("\t布噜噜：around-bomb函数、teamview函数\n");
    printf("\t（信息官）。：Initmap函数、add-flag函数\n");
    printf("\n按任意键返回菜单...\n");
    _getch();
}

void gameview_ShowBoard()
{
    system("cls");
    int i, j;

    printf("==================== 扫雷游戏 ====================\n");
    printf("操作：WASD移动 | 回车翻开 | F插旗 | B返回菜单\n");
    printf("===================================================\n\n");

    for (i = 0; i < n; i++)
    {
        printf("   ");
        for (j = 0; j < n; j++)
        {
            int isCur = (i == curY && j == curX);

            if (show[i][j] == 0)
            {
                SetColor(isCur ? 14 : 15);
                printf(isCur ? "[■]" : " ■ ");
            }
            else if (show[i][j] == 2)
            {
                SetColor(12);
                printf(isCur ? "[F]" : " F ");
            }
            else if (show[i][j] == 9)
            {
                SetColor(12);
                printf(isCur ? "[*]" : " * ");
            }
            else if (show[i][j] == 1)
            {
                int cnt = around_bomb(j, i);
                if (cnt == 0)
                {
                    SetColor(8);
                    printf(isCur ? "[□]" : " □ ");
                }
                else
                {
                    int color[] = { 0,9,10,11,12,13,14,15,7 };
                    SetColor(color[cnt]);
                    printf(isCur ? "[%d]" : " %d ", cnt);
                }
            }
            SetColor(7);
        }
        printf("\n");
    }

    printf("\n===================================================\n");
    SetColor(15); printf(" ■ 未翻开");
    SetColor(8);  printf("   □ 已翻开");
    SetColor(12); printf("   F 旗子");
    SetColor(11); printf("   数字=周围雷数");
    SetColor(7);
    printf("\n===================================================\n");
}

void loseview()
{
    system("cls");
    mciSendStringA("play music\\lose.wav", 0, NULL, NULL);

    printf("========================================\n");
    printf("              游 戏 失 败\n");
    printf("========================================\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (bomb[i][j] == 1) {
                show[i][j] = 9;
            }
            else {
                show[i][j] = 1;
            }
        }
    }
    gameview_ShowBoard();

    printf("\n云海学长被东东哥抓到，把女装照拍下来发到了图灵院大群！\n");
    printf("按回车回到主菜单\n");
    getchar();
    getchar();
}

void winview()
{
    system("cls");
    mciSendStringA("play music\\win.wav", 0, NULL, NULL);

    int use_time = timer(0);
    printf("========================================\n");
    printf("         恭 喜 胜 利 ！\n");
    printf("========================================\n");
    printf("你成功帮云海学长找到了女装！\n");
    printf("用时:%d 秒\n", use_time);
    char name[20];
    printf("请输入昵称：");
    scanf("%s", name);
    if (rank_num < MAX_RANK) {
        strcpy(rank[rank_num].name, name);
        rank[rank_num].time = use_time;
        rank_num++;
    }
    printf("按回车回到主菜单\n");
    getchar();
    getchar();
}

void gameview() {
    timer(-1);
    curX = 0;
    curY = 0;

    while (1) {
        gameview_ShowBoard();
        char input = _getch();

        if (input == 'w' || input == 'W') {
            if (curY > 0) curY--;
        }
        else if (input == 's' || input == 'S') {
            if (curY < n - 1) curY++;
        }
        else if (input == 'a' || input == 'A') {
            if (curX > 0) curX--;
        }
        else if (input == 'd' || input == 'D') {
            if (curX < n - 1) curX++;
        }
        else if (input == '\r') {
            int res = playermove(curX, curY);
            if (res == 2) {
                loseview();
                return;
            }
            if (iswin() == 1) {
                winview();
                return;
            }
        }
        else if (input == 'f' || input == 'F') {
            add_flag(curX, curY);
        }
        else if (input == 'b' || input == 'B') {
            return;
        }
        else if (input == 'z' || input == 'Z')
        {
            mciSendStringA("play music\\egg.wav", NULL, 0, NULL);
        }
    }
}

void setting()
{
    static int init_flag = 0;
    static int vol = 50;
    char cmd[256];
    char button;
    if (init_flag == 0)
    {
        sprintf(cmd, "open \"lose.wav\" type waveaudio alias bgm");
        mciSendStringA(cmd, NULL, 0, NULL);
        sprintf(cmd, "open \"win.wav\" type waveaudio alias vic");
        mciSendStringA(cmd, NULL, 0, NULL);
        init_flag = 1;
    }
    while (1)
    {
        system("cls");
        printf("\n\n\n\n\n\n");
        printf("=======================================================设置菜单=========================================================\n");
        printf("=======================================================当前音量：%d=====================================================\n", vol);
        printf("================================================= + 增加音量  - 减少音量 =================================================\n");
        printf("=======================================================按B返回菜单=======================================================\n");

        button = _getch();
        if (button == '+')
        {
            if (vol < 100) {
                vol++;
                sprintf(cmd, "setaudio bgm volume to %d", vol * 10);
                mciSendStringA(cmd, NULL, 0, NULL);
                sprintf(cmd, "setaudio vic volume to %d", vol * 10);
                mciSendStringA(cmd, NULL, 0, NULL);
            }
        }
        else if (button == '-')
        {
            if (vol > 0)
            {
                vol--;
                sprintf(cmd, "setaudio bgm volume to %d", vol * 10);
                mciSendStringA(cmd, NULL, 0, NULL);
                sprintf(cmd, "setaudio vic volume to %d", vol * 10);
                mciSendStringA(cmd, NULL, 0, NULL);
            }
        }
        else if (button == 'b' || button == 'B')
        {
            break;
        }
    }
}

/*
* 修复后的 menuview（只改这里，保证每次切换界面都会清屏，不会重叠）
*/
/*
* 修复后的 menuview（增加了排行榜选项）
*/
void menuview() {

    int XY[5][2] = { {64, 5}, {64, 8}, {64, 11}, {64, 14}, {64, 17} };
    const char* s1[5] = { "开始游戏", "团队介绍", "游戏设置", "排行榜", "退出游戏" };
    static int chose = 0;

    while (1) {

        system("cls");

        // 绘制菜单标题
        gotoXY(58, 2);
        setPrintColor(7);
        printf("掩护云海学长换女装吧");

        // 绘制菜单选项
        for (int i = 0; i < 5; i++) {
            gotoXY(XY[i][0], XY[i][1]);
            printf("%s", s1[i]);
        }

        // 高亮当前选中项
        setPrintColor(0xE7);
        gotoXY(XY[chose][0], XY[chose][1]);
        printf("%s", s1[chose]);
        setPrintColor(7);

        // 背景说明
        gotoXY(42, 19);
        printf("背景:海学长居然要女装,让我们一起掩护云海学长，让他成功女装不被发现");

        // 操作提示
        setPrintColor(4);
        gotoXY(55, 22);
        printf("操作提示：按ws移动光标 按回车选择");
        setPrintColor(7);

        // 接收用户输入
        char input = _getch();
        if (input == 'w' || input == 'W') {
            chose--;
            if (chose < 0) chose = 4;  // 5个选项，最大是4
        }
        if (input == 's' || input == 'S') {
            chose++;
            if (chose > 4) chose = 0;
        }
        if (input == '\r') {
            system("cls");
            switch (chose) {
            case 0:
                selectlevel();
                gameview();
                break;
            case 1:
                teamview();
                break;
            case 2:
                setting();
                break;
            case 3:
                rankview();  // <--- 排行榜！
                break;
            case 4:
                exit(0);
                break;
            }
        }
    }
}

int main() {
    system("mode con cols=120 lines=30");
    HideCursor();
    n = 9;
    bombcount = 10;

    printf("正在启动《掩护云海学长换女装》系统...\n");
    Sleep(1000);
    system("cls");

    while (1) {
        menuview();
    }
    return 0;
}