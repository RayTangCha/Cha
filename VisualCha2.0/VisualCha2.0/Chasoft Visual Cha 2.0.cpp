/*
    VisualCha2.0 (C)2022 Chasoft,Inc.
    (c)Chasoft, Inc.
    to get easyx, visit https://easyx.cn/
    to get Visual Studio, visit https://visualstudio.microsoft.com/vs/
    press Ctrl+F5 to compile script
*/
#define _CRT_SECURE_NO_WARNINGS 1
#include<graphics.h>
#include<cstdio>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<windows.h>
std::ofstream ofs;
std::ifstream ifs;
IMAGE imgwhole, imgsquare;
short gamemap[9][12], chaplacex, chaplacey,preyplacex,preyplacey,score,speedlevel=1000,legacy;
bool undead ,skin;
//the functions the user sees
void gamef();
void accountf();
void buyf();
int main();
void rulef();
//that's all
void waitclick() { //start interface
    MOUSEMSG msg;
    do msg = GetMouseMsg();
    while (msg.uMsg != WM_LBUTTONDOWN);
    if (msg.x > 170 && msg.x < 470 && msg.y>80 && msg.y < 140) gamef();
    else if (msg.x > 170 && msg.x < 470 && msg.y>160 && msg.y < 220) accountf();
    else if (msg.x > 170 && msg.x < 470 && msg.y>240 && msg.y < 300) buyf();
    else if (msg.x > 170 && msg.x < 470 && msg.y>300 && msg.y < 320) system("start https://baike.baidu.com/item/%E7%8C%B9/2137773?fr=aladdin");
    else if (msg.x > 170 && msg.x < 470 && msg.y>320 && msg.y < 340) rulef();
    else waitclick();
}
void wholeimagestart() {
    loadimage(&imgwhole, "C:\\Program Files (x86)\\Visual Cha\\ucraine.jpg", 640, 480);
    putimage(0, 0, &imgwhole);
}
void wholeimagegame() {
    loadimage(&imgwhole, "C:\\Program Files (x86)\\Visual Cha\\Homeofcha.jpg", 640, 480);
    putimage(0, 0, &imgwhole);
    setfillcolor(GREEN);
    settextstyle(40, 0, "Broadway");
    outtextxy(80, 0, _T("VisualCha2.0"));
    setlinecolor(BLACK);
    roundrect(80, 60, 560, 420, 20, 20);
    outtextxy(360, 0, _T("Score:"));
    char scoredisplay[100];
    sprintf_s(scoredisplay,"%d",score);
    outtextxy(480, 0, scoredisplay);
    settextstyle(20, 0, "Broadway");
    outtextxy(80, 40, _T("Time:"));
    sprintf_s(scoredisplay, "%d", clock());
    outtextxy(480, 40, scoredisplay);
}
void putmellon(int x, int y) {
    loadimage(&imgsquare, "C:\\Program Files (x86)\\Visual Cha\\Mellon.jpeg", 40, 40);
    putimage(x*40+80, y*40+60, &imgsquare);
}
void putruntu(int x, int y) {
    loadimage(&imgsquare, "C:\\Program Files (x86)\\Visual Cha\\runtu.jpg", 40, 40);
    putimage(x * 40 + 80, y * 40 + 60, &imgsquare);
}
void putcha(int x, int y) {
    loadimage(&imgsquare, "C:\\Program Files (x86)\\Visual Cha\\cha.jpeg", 40, 40);
    putimage(x*40 + 80, y*40 + 60, &imgsquare);//normal skin
    if (skin) {
        setfillcolor(GREEN);
        fillrectangle(x * 40 + 80, y * 40 + 60, x * 40 + 120, y * 40 + 80);
    }//green hat skin
}
void puthole(int x, int y) {
    loadimage(&imgsquare, "C:\\Program Files (x86)\\Visual Cha\\hole.jpg", 40, 40);
    putimage(x * 40 + 80, y * 40 + 60, &imgsquare);
}
void putruby(int x, int y) {
    loadimage(&imgsquare, "C:\\Program Files (x86)\\Visual Cha\\ruby.jpeg", 40, 40);
    putimage(x * 40 + 80, y * 40 + 60, &imgsquare);
}
void initgame() {
    ifs.open("C:\\Users\\Public\\VChaFiles.txt", std::ios::in|std::ios::app);
    ifs >> score;
    legacy = score;
    ifs.close();
    srand(time(0));
    gamemap[0][0] = 1;
    preyplacex = rand() % 9 + 4;
    preyplacey = rand() % 6 + 4;
    gamemap[preyplacey][preyplacex] = 5;
    for (int rowmove = 3; rowmove < 9; rowmove++)gamemap[rowmove][rand() % 12] = rand() % 3 + 2;
    undead = 1;
}
void scoremove() {
    if (gamemap[chaplacey][chaplacex] == 2) {
        score += 5;
    }
    if (gamemap[chaplacey][chaplacex] == 3) {
        undead = 0;
        MessageBox(GetHWnd(), " You're sucked into the black hole", "Report", MB_OK | MB_ICONEXCLAMATION);
    }
    if (gamemap[chaplacey][chaplacex] == 4) {
        score += 10;
    }
    if (gamemap[chaplacey][chaplacex] == 5) {
        undead=0;
        MessageBox(GetHWnd(), " You're killed by Run Tu", "Report", MB_OK | MB_ICONEXCLAMATION);
    }
}
void keypress() {
    int y = _getch();
    if (y== 224){
        int x = _getch();
        if (x== 72) {
            if (chaplacey) {
                gamemap[chaplacey][chaplacex] = 0;
                chaplacey--;
                scoremove();
                gamemap[chaplacey][chaplacex] = 1;
            }
            else MessageBox(GetHWnd(), " Illegal Operation", "Warning", MB_OK | MB_ICONERROR);
        }
        if (x== 75) {
            if (chaplacex) {
                gamemap[chaplacey][chaplacex] = 0;
                chaplacex--;
                scoremove();
                gamemap[chaplacey][chaplacex] = 1;
            }
            else MessageBox(GetHWnd(), " Illegal Operation", "Warning", MB_OK | MB_ICONERROR);
        }
        if (x== 77) {
            if (11-chaplacex) {
                gamemap[chaplacey][chaplacex] = 0;
                chaplacex++;
                scoremove();
                gamemap[chaplacey][chaplacex] = 1;
            }
            else MessageBox(GetHWnd(), " Illegal Operation", "Warning", MB_OK | MB_ICONERROR);
        }
        if (x== 80) {
            if (8 - chaplacey) {
                gamemap[chaplacey][chaplacex] = 0;
                chaplacey++;
                scoremove();
                gamemap[chaplacey][chaplacex] = 1;
            }
            else MessageBox(GetHWnd(), " Illegal Operation", "Warning", MB_OK | MB_ICONERROR);
        }
    }
    if (y == 27)undead = 0;
}
void moveline() {
    srand(clock()+time(0));
    for (int rowmove = 1; rowmove < 9; rowmove++) for (int colmove = 0; colmove < 12; colmove++)gamemap[rowmove - 1][colmove] = gamemap[rowmove][colmove];
    for (int nummove = 0; nummove < rand() % 3 + 1; nummove++)gamemap[8][rand() % 12] = rand() % 3 + 2;
    chaplacey--;
}
//those functions
void gamef() {
    MessageBox(GetHWnd(), "We support Russia", "SUPPORT", NULL);
    initgame();
    bool stoppress=0;
    while (undead) {
        EndBatchDraw();
        BeginBatchDraw();
        cleardevice();
        wholeimagegame();
        //draw graph
        for (int rowmove = 0; rowmove < 9; rowmove++) {
            for (int colmove = 0; colmove < 12; colmove++) {
                if (gamemap[rowmove][colmove] == 1) putcha(colmove, rowmove);
                else if (gamemap[rowmove][colmove] == 2) putmellon(colmove, rowmove);
                else if (gamemap[rowmove][colmove] == 3) puthole(colmove, rowmove);
                else if (gamemap[rowmove][colmove] == 4) putruby(colmove, rowmove);
                else if (gamemap[rowmove][colmove] == 5) putruntu(colmove, rowmove);
            }
        }
        //move cha
        if (_kbhit()&&(!stoppress)) keypress();
        if (clock() % speedlevel < 10) {
            moveline();
            stoppress = 1;
        }
        else stoppress = 0;
        ofs.open("C:\\Users\\Public\\VChaFiles.txt", std::ios::out | std::ios::trunc);
        ofs << score;
        ofs.close();
    }
}
void accountf() {
    cleardevice();
    wholeimagestart();
    outtextxy(80, 0, _T("VisualCha2.0"));
    outtextxy(80, 40, _T("Your amount:"));
    char scoredisplay[100];
    sprintf_s(scoredisplay, "%d", clock());
    outtextxy(400, 40, scoredisplay);
    outtextxy(80, 80, _T("Your skin:"));
    if(skin)outtextxy(400, 80, _T("SPEC"));
    else outtextxy(400, 80, _T("NORM"));
    _getch();
}
void buyf() {
    cleardevice();
    wholeimagestart();
    outtextxy(80, 0, _T("VisualCha2.0"));
    outtextxy(80, 60, _T("Buy Skin:Not Availible"));
    settextstyle(20, 0, "Copper Black", 0, 0, 0, 0, 0, 0);
    outtextxy(80, 60, _T("Buy Skin:Not Availible"));
    _getch();
}
void rulef() {
    cleardevice();
    wholeimagestart();
    outtextxy(80, 0, _T("VisualCha2.0"));
    outtextxy(120, 60, _T("Cha(You)"));
    outtextxy(120, 100, _T("Black Hole (Deadly)"));
    outtextxy(120, 140, _T("Mellon (Yum)"));
    outtextxy(120, 180, _T("Ruby (Precious)"));
    outtextxy(120, 220, _T("Run Tu (Danger)"));
    putcha(0, 0);
    puthole(0, 1);
    putmellon(0, 2);
    putruby(0, 3);
    putruntu(0, 4);
    _getch();
}
//that's all
int main(){
    initgraph(640,480,NOCLOSE);
    wholeimagestart();
    settextstyle(60, 40, "Copper Black");
    settextcolor(BROWN);
    setbkmode(TRANSPARENT);
    outtextxy(80, 0, _T("VisualCha2.0"));
    settextstyle(20, 0, "Copper Black");
    outtextxy(320, 60, _T("(C)2022 Chasoft,Inc."));
    settextcolor(GREEN);
    setlinecolor(BLUE);
    settextstyle(50, 0, "Broadway");
    rectangle(170, 80, 470, 140);
    rectangle(170, 160, 470, 220);
    rectangle(170, 240, 470, 300);
    outtextxy(175, 80, _T("Start Game"));
    outtextxy(175, 160, _T("See Account"));
    outtextxy(175, 240, _T("Buy Things"));
    settextcolor(BLUE);
    settextstyle(20, 0, "Copper Black",0,0,0,0,1,0);
    outtextxy(175, 300, _T("What's Cha?"));
    outtextxy(175, 320, _T("See Rules"));
    settextstyle(50, 0, "Copper Black",0,0,0,0,0,0);
    settextcolor(CYAN);
    waitclick();
    closegraph();
    return 0;
}