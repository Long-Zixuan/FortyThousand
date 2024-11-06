#pragma warning(disable:4996)
//Version 2.1.1
#include<bits/stdc++.h>
#include <fstream>
using namespace std;
#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<easyx.h>
#include<cmath>
#include<WinUser.h>
#include <fstream>
#include <ctime>

#pragma comment(lib,"Winmm.lib")

//#define High 900

//#define Width 720

#define NONE -1

int High = 900;
int Width = 720;
int Mhigh = 0;
int Mweigh = 0;

int rW = GetSystemMetrics(SM_CXSCREEN); // 屏幕宽度 像素
int rH = GetSystemMetrics(SM_CYSCREEN); // 屏幕高度 像素


class Plane
{
public:
    int position_x, position_y;
    //static int score;
    static int impactTime;
    int angle;
    Plane(int x, int y)
    {
        this->angle = 0;
        this->position_x = x;
        this->position_y = y;


    }
};


//int Plane::score = 0;
int Plane::impactTime = 100;

class Bullet
{
public:
    double bullet_x, bullet_y;

    Bullet(double x, double y)
    {
        this->bullet_x = x;
        this->bullet_y = y;

    }
};

class EnemyBullet
{
public:
    int bullet_x, bullet_y;
    int angle;
    static int speed;
    static int creatSpeed;
    static int moveSpeed;
    EnemyBullet(int x, int y, int angle)
    {
        this->bullet_x = x;
        this->bullet_y = y;
        this->angle = angle;
    }
};


class Enemy
{
public:
    int enemy_x, enemy_y;
    static int speed;
    static int creatSpeed;
    bool isExplode;
    int heath;
    static int transeAngle;
    Enemy(int x, int y)
    {
        this->heath = 10;
        this->isExplode = false;
        this->enemy_x = x;
        this->enemy_y = y;
    }
};

int EnemyBullet::speed = 0;
int EnemyBullet::creatSpeed = 0;
int Enemy::transeAngle = 40;

int Enemy::speed = 0;
int Enemy::creatSpeed = 0;

int creatBulletEnemy = 250, enemyBulletSpeed = 25;

int transeAngle;

char diff;

int startup(Enemy& enemy);

void show(Plane& plane, Enemy& enemy);

void updateWithoutInput(Plane& plane, Enemy& enemy);

void updateWithInput(Plane& plane, Enemy& enemy);

int LZXrand();

void button(int x, int y, int w, int h, TCHAR* text);

void dialogue();

vector<Bullet*> BList;

vector<EnemyBullet*> EBList;

IMAGE image_bk;
/// ////////////////
//IMAGE image_plane1;

//IMAGE image_plane2;
IMAGE main1[6];
IMAGE main2[6];

/////////////////////
IMAGE image_bullet1;

IMAGE image_bullet2;
/////////////////////
//IMAGE image_enemy1;

//IMAGE image_enemy2;
IMAGE boss1[6];
IMAGE boss2[6];
//////////////////////

IMAGE die_plane1;

IMAGE die_plane2;

/// ////////////////

IMAGE image_enemybullet1;

IMAGE image_enemybullet2;

/// ///////////////////
IMAGE die_enemy1;
IMAGE die_enemy2;
/// ///////////////

IMAGE ui;

////////////////
IMAGE start_memu_bk;
IMAGE start_button;
IMAGE start_buttonmask;
IMAGE exit_button;
IMAGE exit_buttonmask;
IMAGE easy_button;
IMAGE easy_buttonmask;
IMAGE hard_button;
IMAGE hard_buttonmask;
IMAGE chose_diff_bk;
IMAGE again_button;
IMAGE again_buttonmask;
/////////////////////
IMAGE vivi1;
IMAGE vivi2;
IMAGE diabk;
IMAGE bottonbk;

IMAGE hard;
IMAGE easy;

IMAGE zhihui;

int enemyMoveSpeed;

string difficulty;

int changeZhaoshi = 500;
int zhaoshiTime = 0;

int bossNum = 0;
int mainNum = 0;
int animation = 50;
void check();

int main()
{
    check();
begin:Plane plane = Plane(High / 2, Width / 2);
    Enemy enemy = Enemy(High / 4, Width / 2);
    int jud = startup(enemy);                   //初始化
    bool hadDia = false;
    if (jud)
    {
        return 0;
    }
    HWND hwnd = GetHWnd();
    while (1)                   //游戏循环执行
    {
        show(plane, enemy);                 //显示画面
        if (Plane::impactTime <= 0)
        {
            //string text = "You die";
            mciSendString("close bkmusic", NULL, 0, NULL);
            //MessageBox(hwnd, text.c_str(), "You die", MB_OK);

            break;
        }

        if (enemy.heath <= 0)
        {
            int tmpScore;
            FILE *file = fopen("file\\highestScore.txt","r");
            if(file!=NULL)
            {
                fscanf(file, "%d", &tmpScore);
                //rewind(file);
                
                if(tmpScore<Plane::impactTime)
                {
                    FILE* file = fopen("file\\highestScore.txt", "w+");
                    fprintf(file, "%d", Plane::impactTime);
                    
                }
               
            }
            else
            {
                FILE* file = fopen("file\\highestScore.txt", "w+");
                fprintf(file, "%d", 0);
            }
            fclose(file);
            mciSendString("close bkmusic", NULL, 0, NULL);
            //if(Plane::impactTime>)
            //MessageBox(hwnd, "You win!", "You win", MB_OK);
            break;
        }
        if ((difficulty == "Easy" && enemy.heath <= 100 && !hadDia) || (enemy.heath <= 150 && difficulty == "Hard" && !hadDia))
        {


            dialogue();
            hadDia = true;
        }
        updateWithoutInput(plane, enemy);   //与用户输入无关的更新

        updateWithInput(plane, enemy);      //与用户输入有关的更新
    }
    putimage(0, 700-Mhigh, &bottonbk);
    putimage(448, 500 - Mhigh, &vivi1, NOTSRCERASE);
    putimage(448, 500 - Mhigh, &vivi2, SRCINVERT);
    putimage(240, 800 - Mhigh, &exit_buttonmask, SRCAND);
    putimage(240, 800 - Mhigh, &exit_button, SRCPAINT);
    putimage(20, 800 - Mhigh, &again_buttonmask, SRCAND);
    putimage(20, 800 - Mhigh, &again_button, SRCPAINT);
    FlushBatchDraw();
    while (true)
    {
        MOUSEMSG mousemsg;
        //TCHAR text1[] = _T("Play again");
        //TCHAR text2[] = _T("Exit game");
        //button(220, 220, 170, 50, text1);
        //button(220, 280, 170, 50, text2);


        if (MouseHit())
        {
            mousemsg = GetMouseMsg();
            if (mousemsg.uMsg == WM_LBUTTONDOWN)
            {
                if (mousemsg.x >= 20 && mousemsg.x <= 20 + 200 && mousemsg.y >= 800 - Mhigh && mousemsg.y <= 800 - Mhigh + 110)
                {
                    BList.clear();
                    EBList.clear();
                    //Plane::score = 0;
                    goto begin;
                }
                if (mousemsg.x >= 240 && mousemsg.x <= 240 + 200 && mousemsg.y >= 800 - Mhigh && mousemsg.y <= 800 - Mhigh + 110)
                {
                    break;
                }
            }
        }
        //FlushBatchDraw();
    }
    return 0;
}

void check()
{
    FILE* file = fopen("file\\highestScore.txt", "r");

    if(file==NULL)
    {
        file = fopen("file\\highestScore.txt", "w+");
    }
    fclose(file);
}

void dialogue()
{
    /*string dia[3];
    //vector<string>dia;
    dia[0] = "The enemy only has";
    dia[1] = "half of their health now";
    dia[2] = "We must defeat her";
    for(int i=0;i<3;i++)
    {
        putimage(0, 700, &diabk);
        putimage(448, 500, &vivi1, NOTSRCERASE);
        putimage(448, 500, &vivi2, SRCINVERT);
        string tmp = "";
        for(int j=0;j<dia[i].size(); j++)
        {
            tmp += dia[i][j];
            TCHAR s1[] = _T("黑体");
            settextstyle(30, 0, s1);
            settextcolor(RGB(237, 65, 255));
            outtextxy(0,800,tmp.c_str());
            FlushBatchDraw();
            Sleep(50);
        }
        //_getch();

        cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
        getchar();
    }*/




    const TCHAR* dia[3];
    //vector<string>dia;
    dia[0] = _T("敌人只有一半的血量了");
    dia[1] = _T("我必须战胜她");
    //dia[1] = "half of their health now";
    //dia[2] = "We must defeat her";
    for (int i = 0; i < 2; i++)
    {
        //putimage(0, 700, &diabk);
        //putimage(448, 500, &vivi1, NOTSRCERASE);
        //putimage(448, 500, &vivi2, SRCINVERT);
        string tmp = "";
        for (int j = 0; j < lstrlen(dia[i]); j++)
        {
            putimage(0, 700 - Mhigh, &diabk);
            putimage(448, 500 - Mhigh, &vivi1, NOTSRCERASE);
            putimage(448, 500 - Mhigh, &vivi2, SRCINVERT);
            tmp += dia[i][j];
            TCHAR s1[] = _T("黑体");
            settextstyle(30, 0, s1);
            settextcolor(RGB(237, 65, 255));
            outtextxy(0, 800 - Mhigh, tmp.c_str());
            FlushBatchDraw();
            Sleep(50);
        }
        //_getch();

        cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');
        getchar();
    }
}

int LZXrand()
{
    time_t t;
    t = time(NULL);
    t = t % 10;
    int res;
    while (1)
    {
        res = rand();
        if (res + t >= 0 && (res + t) <= Width - 50)
        {
            break;
        }
    }
    return res;
}

/*void button(int x, int y, int w, int h, TCHAR* text)
{
    setbkmode(TRANSPARENT);
    setfillcolor(RGB(237, 65, 255));
    fillroundrect(x, y, x + w, y + h, 10, 10);
    // 输出字符串（MBCS 字符集）
    TCHAR s1[] = _T("黑体");
    settextstyle(50, 0, s1);
    //TCHAR s[50] = _T("hello");
    settextcolor(RGB(255, 255, 255));
    int tx = x + (w - textwidth(text)) / 2;
    int ty = y + (h - textheight(text)) / 2;

    outtextxy(tx, ty, text);

}*/

bool hadStart = false;
int highestScore;
int startup(Enemy& enemy)                   //数据初始化
{
    
    int UIWidth = 500;
    if(rH<=768)
    {
        UIWidth = 450;
        High = 540;
        Mhigh = 360;
        //Width = 400;
    }
    FILE* file = fopen("file//highestScore.txt", "r");
    if (file != NULL)
    {
        
        fscanf(file, "%d", &highestScore);
        
    }
    else
    {
        highestScore = -1;
    }
    fclose(file);
    initgraph(Width + UIWidth, High);
    if(rH<=768)
    {
        loadimage(&zhihui, "src\\zhihui_540p.png");
    }
    else
    {
        loadimage(&zhihui, "src\\zhihui.png");
    }
    
    putimage(0, 0, &zhihui);
    FlushBatchDraw();
    Sleep(1000);
    setbkmode(TRANSPARENT);
    TCHAR s1[] = _T("黑体");
    settextstyle(50, 0, s1);
    settextcolor(RGB(255, 255, 255));
    loadimage(&image_bk, "src\\EasyXFightPlane\\background.jpg");
    loadimage(&ui, "src\\EasyXFightPlane\\ui.jpg");
    //loadimage(&image_plane1, "src\\EasyXFightPlane\\main_character_back1.jpg");
    //loadimage(&image_plane2, "src\\EasyXFightPlane\\main_character_back2.jpg");
    loadimage(&main1[0], "src\\main1.bmp");
    loadimage(&main1[1], "src\\main2.bmp");
    loadimage(&main1[2], "src\\main3.bmp");
    loadimage(&main1[3], "src\\main4.bmp");
    loadimage(&main1[4], "src\\main5.bmp");
    loadimage(&main1[5], "src\\main6.bmp");
    loadimage(&main2[0], "src\\main1_mask.bmp");
    loadimage(&main2[1], "src\\main2_mask.bmp");
    loadimage(&main2[2], "src\\main3_mask.bmp");
    loadimage(&main2[3], "src\\main4_mask.bmp");
    loadimage(&main2[4], "src\\main5_mask.bmp");
    loadimage(&main2[5], "src\\main6_mask.bmp");
    loadimage(&image_bullet1, "src\\EasyXFightPlane\\our_bullet1.jpg");
    loadimage(&image_bullet2, "src\\EasyXFightPlane\\our_bullet2.jpg");
    loadimage(&image_enemybullet1, "src\\EasyXFightPlane\\boss_bullet1.jpg");
    loadimage(&image_enemybullet2, "src\\EasyXFightPlane\\boss_bullet2.jpg");
    //loadimage(&image_enemy1, "src\\EasyXFightPlane\\boss1.jpg");
    //loadimage(&image_enemy2, "src\\EasyXFightPlane\\boss2.jpg");
    loadimage(&boss1[0], "src\\boss1.bmp");
    loadimage(&boss1[1], "src\\boss2.bmp");
    loadimage(&boss1[2], "src\\boss3.bmp");
    loadimage(&boss1[3], "src\\boss4.bmp");
    loadimage(&boss1[4], "src\\boss5.bmp");
    loadimage(&boss1[5], "src\\boss6.bmp");
    loadimage(&boss2[0], "src\\boss1_mask.bmp");
    loadimage(&boss2[1], "src\\boss2_mask.bmp");
    loadimage(&boss2[2], "src\\boss3_mask.bmp");
    loadimage(&boss2[3], "src\\boss4_mask.bmp");
    loadimage(&boss2[4], "src\\boss5_mask.bmp");
    loadimage(&boss2[5], "src\\boss6_mask.bmp");
    loadimage(&die_plane1, "src\\EasyXFightPlane\\main_character_die1.jpg");
    loadimage(&die_plane2, "src\\EasyXFightPlane\\main_character_die2.jpg");
    loadimage(&die_enemy1, "src\\EasyXFightPlane\\boss_die1.jpg");
    loadimage(&die_enemy2, "src\\EasyXFightPlane\\boss_die2.jpg");
    loadimage(&start_memu_bk, "src\\EasyXFightPlane\\startMemuBk.jpg");
    //loadimage(&start_button, "src\\EasyXFightPlane\\start_botton.jpg");
    loadimage(&start_button, "src\\play.bmp");
    loadimage(&start_buttonmask, "src\\play_mask.bmp");
    //loadimage(&exit_button, "src\\EasyXFightPlane\\exit_botton.jpg");
    loadimage(&exit_button, "src\\exit.bmp");
    loadimage(&exit_buttonmask, "src\\exit_mask.bmp");
    //loadimage(&easy_button, "src\\EasyXFightPlane\\easy_botton.jpg");
    loadimage(&easy_button, "src\\easybotton.bmp");
    loadimage(&easy_buttonmask, "src\\easybotton_mask.bmp");
    //loadimage(&hard_button, "src\\EasyXFightPlane\\hard_botton.jpg");
    loadimage(&hard_button, "src\\hardbotton.bmp");
    loadimage(&hard_buttonmask, "src\\hardbotton_mask.bmp");
    loadimage(&chose_diff_bk, "src\\EasyXFightPlane\\choosediff.jpg");
    //loadimage(&again_button, "src\\EasyXFightPlane\\again_botton.jpg");
    loadimage(&again_button, "src\\again.bmp");
    loadimage(&again_buttonmask, "src\\again_mask.bmp");
    loadimage(&vivi1, "src\\EasyXFightPlane\\ViVi1.jpg");
    loadimage(&vivi2, "src\\EasyXFightPlane\\ViVi2.jpg");
    loadimage(&diabk, "src\\EasyXFightPlane\\diabk.jpg");
    loadimage(&bottonbk, "src\\EasyXFightPlane\\bottonbk.jpg");
    loadimage(&easy, "src\\EasyXFightPlane\\easytext.png");
    loadimage(&hard, "src\\EasyXFightPlane\\hardtext.png");
    
    BeginBatchDraw();
    mciSendString("close bkmusic", NULL, 0, NULL);
    mciSendString("open src\\EasyXFightPlane\\memumusic.mp3 alias mumusic", NULL, 0, NULL);
    mciSendString("play mumusic repeat", NULL, 0, NULL);
    MOUSEMSG mousemsg;
    if (!hadStart)
    {
        while (true)
        {
            hadStart = true;
            putimage(0, 0, &start_memu_bk);
            //outtextxy(220, 160, "Choose difficulty");
            //TCHAR diff1[] = _T("Easy");
            //TCHAR diff2[] = _T("Hard");
            //button(220, 220, 170, 50, diff1);
            //button(220, 280, 170, 50, diff2);
            putimage(515, 400 - Mhigh, &start_buttonmask, SRCAND);

            putimage(515 , 400 - Mhigh, &start_button, SRCPAINT);
            putimage(515 , 600 - Mhigh, &exit_buttonmask, SRCAND);
            putimage(515 , 600 - Mhigh, &exit_button, SRCPAINT);
            settextstyle(20, 0, s1);
            outtextxy(0, 0, "Version:2.1.1");
            FlushBatchDraw();

            if (MouseHit())
            {
                mousemsg = GetMouseMsg();
                if (mousemsg.uMsg == WM_LBUTTONDOWN)
                {
                    if (mousemsg.x >= 515 && mousemsg.x <= 515 + 220 && mousemsg.y >= 400 - Mhigh && mousemsg.y <= 400 - Mhigh + 110)
                    {

                        break;
                    }
                    if (mousemsg.x >= 515 && mousemsg.x <= 515 + 220 && mousemsg.y >= 600 - Mhigh && mousemsg.y <= 600 - Mhigh + 110)
                    {
                        return 1;
                    }
                }
            }
        }
    }
    while (true)
    {
        putimage(0, 0, &chose_diff_bk);
        //outtextxy(220, 160, "Choose difficulty");
        //TCHAR diff1[] = _T("Easy");
        //TCHAR diff2[] = _T("Hard");
        //button(220, 220, 170, 50, diff1);
        //button(220, 280, 170, 50, diff2);
        putimage(515 , 400 - Mhigh, &easy_buttonmask, SRCAND);
        putimage(515 , 400 - Mhigh, &easy_button, SRCPAINT);
        putimage(515 , 600 - Mhigh, &hard_buttonmask, SRCAND);
        putimage(515 , 600 - Mhigh, &hard_button, SRCPAINT);
        FlushBatchDraw();
        if (MouseHit())
        {
            mousemsg = GetMouseMsg();
            if (mousemsg.uMsg == WM_LBUTTONDOWN)
            {
                if (mousemsg.x >= 515 && mousemsg.x <= 515 + 220 && mousemsg.y >= 400 - Mhigh && mousemsg.y <= 400 - Mhigh + 110)
                {
                    enemy.heath = 200;
                    enemyMoveSpeed = 10;
                    Plane::impactTime = 200;
                    creatBulletEnemy = 250;
                    difficulty = "Easy";
                    break;
                }
                if (mousemsg.x >= 515 && mousemsg.x <= 515 + 220 && mousemsg.y >= 600 - Mhigh && mousemsg.y <= 600 - Mhigh + 110)
                {
                    enemy.heath = 300;
                    enemyMoveSpeed = 20;
                    Plane::impactTime = 70;
                    creatBulletEnemy = 100;
                    difficulty = "Hard";
                    break;
                }
            }
        }
    }
    mciSendString("close mumusic", NULL, 0, NULL);
    mciSendString("open src\\EasyXFightPlane\\game_music.mp3 alias bkmusic", NULL, 0, NULL);
    mciSendString("play bkmusic repeat", NULL, 0, NULL);
    return 0;

}
int moveNum = 0;
void show(Plane& plane, Enemy& enemy)                     //显示画面
{

    settextcolor(RGB(237, 65, 255));
    
    putimage(0, 0+moveNum, &image_bk);
    putimage(0, -2130+moveNum, &image_bk);
    moveNum++;
    moveNum = moveNum % 2131;
    putimage(720, 0, &ui);
    if (Plane::impactTime <= 0)
    {
        //system("cls");
        string dia = "You die";
        putimage(0, 700, &diabk);
        putimage(448 , 500 - Mhigh, &vivi1, NOTSRCERASE);
        putimage(448 , 500 - Mhigh, &vivi2, SRCINVERT);
        putimage(plane.position_y - 60, plane.position_x - 50, &die_plane1, NOTSRCERASE);
        putimage(plane.position_y - 60, plane.position_x - 50, &die_plane2, SRCINVERT);
        string tmp = "";
        for (int j = 0; j < dia.size(); j++)
        {
            tmp += dia[j];
            TCHAR s1[] = _T("黑体");
            settextstyle(30, 0, s1);
            settextcolor(RGB(237, 65, 255));
            outtextxy(0, 800 - Mhigh, tmp.c_str());
            FlushBatchDraw();
            Sleep(50);
        }
        //_getch();

        cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');






        char scoreNum[4] = "";
        TCHAR s1[] = _T("黑体");
        settextstyle(50, 0, s1);
        string st1 = to_string(Plane::impactTime);
        strcpy_s(scoreNum, st1.c_str());
        outtextxy(1060, 130, scoreNum);
        //char diffc[5] = "";
        if (difficulty == "Hard")
        {
            putimage(950, 60, &hard);
        }
        else if (difficulty == "Easy")
        {
            putimage(950, 60, &easy);
        }
        //strcpy_s(diffc, difficulty.c_str());
        //outtextxy(1100, 40, diffc);
        string st2 = to_string(enemy.heath);
        char enemyHealth[4] = "";
        strcpy_s(enemyHealth, st2.c_str());
        outtextxy(1060, 240, enemyHealth);
        FlushBatchDraw();
        Sleep(2);
        getchar();
        return;
    }
    if (enemy.heath <= 0)
    {
        string dia = "You win!";
        putimage(0, 700 - Mhigh, &diabk);
        putimage(448, 500 - Mhigh, &vivi1, NOTSRCERASE);
        putimage(448, 500 - Mhigh, &vivi2, SRCINVERT);
        putimage(enemy.enemy_y - 60, enemy.enemy_x - 50, &die_enemy1, NOTSRCERASE);
        putimage(enemy.enemy_y - 60, enemy.enemy_x - 50, &die_enemy2, SRCINVERT);
        string tmp = "";
        for (int j = 0; j < dia.size(); j++)
        {
            tmp += dia[j];
            TCHAR s1[] = _T("黑体");
            settextstyle(30, 0, s1);
            settextcolor(RGB(237, 65, 255));
            outtextxy(0, 800 - Mhigh, tmp.c_str());
            FlushBatchDraw();
            Sleep(50);
        }
        //_getch();

        cin.ignore((std::numeric_limits< streamsize >::max)(), '\n');


        TCHAR s1[] = _T("黑体");
        settextstyle(50, 0, s1);

        char scoreNum[4] = "";
        string st1 = to_string(Plane::impactTime);
        strcpy_s(scoreNum, st1.c_str());
        outtextxy(1060, 130, scoreNum);
        //char diffc[5] = "";
        //strcpy_s(diffc, difficulty.c_str());
        //outtextxy(1100, 40, diffc);
        if (difficulty == "Hard")
        {
            putimage(950, 60, &hard);
        }
        else if (difficulty == "Easy")
        {
            putimage(950, 60, &easy);
        }
        string st2 = to_string(enemy.heath);
        char enemyHealth[4] = "";
        strcpy_s(enemyHealth, st2.c_str());
        outtextxy(1060, 240, enemyHealth);
        
        
        FlushBatchDraw();
        Sleep(2);
        getchar();
        return;
    }

    for (auto bul : BList)
    {
        putimage(bul->bullet_y, bul->bullet_x, &image_bullet1, NOTSRCERASE);
        putimage(bul->bullet_y, bul->bullet_x, &image_bullet2, SRCINVERT);
    }


    for (auto bul : EBList)
    {
        putimage(bul->bullet_y, bul->bullet_x, &image_enemybullet1, NOTSRCERASE);
        putimage(bul->bullet_y, bul->bullet_x, &image_enemybullet2, SRCINVERT);
    }

    putimage(enemy.enemy_y - 60, enemy.enemy_x - 50, &boss2[bossNum], SRCAND);
    putimage(enemy.enemy_y - 60, enemy.enemy_x - 50, &boss1[bossNum], SRCPAINT);

    putimage(plane.position_y - 60, plane.position_x - 50, &main2[mainNum], SRCAND);
    putimage(plane.position_y - 60, plane.position_x - 50, &main1[mainNum], SRCPAINT);
    //putimage(enemy.enemy_y - 60, enemy.enemy_x - 50, &image_enemy1, NOTSRCERASE);
    //putimage(enemy.enemy_y - 60, enemy.enemy_x - 50, &image_enemy2, SRCINVERT);
    //putimage(plane.position_y - 60, plane.position_x - 50, &image_plane1, NOTSRCERASE);
    //putimage(plane.position_y - 60, plane.position_x - 50, &image_plane2, SRCINVERT);
    char scoreNum[4] = "";
    string st1 = to_string(Plane::impactTime);
    strcpy_s(scoreNum, st1.c_str());
    outtextxy(1060, 130, scoreNum);
    //char diffc[5] = "";
    //strcpy_s(diffc, difficulty.c_str());
    //outtextxy(1100, 40, diffc);
    if (difficulty == "Hard")
    {
        putimage(950, 60, &hard);
    }
    else if (difficulty == "Easy")
    {
        putimage(950, 60, &easy);
    }
    string st2 = to_string(enemy.heath);
    char enemyHealth[4] = "";
    strcpy_s(enemyHealth, st2.c_str());
    outtextxy(1060, 240, enemyHealth);
    //outtextxy(0, 20, "When Enemy Health is 0,You win.When You Health is 0,You die");
    TCHAR s1[] = _T("黑体");
    settextstyle(20, 0, s1);
    settextcolor(RGB(255, 255, 255));
    //outtextxy(0, 0, "Press esc to pause the game   Version:Beta 2.3.1");

    settextstyle(50, 0, s1);
    //outtextxy(590, 800, "score:");
    //outtextxy(650,800,Plane::score);
    if(highestScore!=NONE)
    {
        char tmp[30];
        string highestScoreText = "最高分：" + to_string(highestScore);
        strcpy_s(tmp, highestScoreText.c_str());
        outtextxy(800, 330, tmp);
    }
    else
    {
        outtextxy(800, 330, "MSGNotFound");
    }
    FlushBatchDraw();
    Sleep(2);


}
int angle2 = 0;
int zhaoshi = 0;
int dir = LZXrand() % 9;

void updateWithoutInput(Plane& plane, Enemy& enemy)//update without user input
{
    animation--;
    if (animation <= 0)
    {
        mainNum++;
        mainNum = mainNum % 6;
        bossNum++;
        bossNum = bossNum % 6;
        animation = 50;
    }

    for (auto bul : BList)
    {
        if (bul->bullet_x > -1)
        {
            bul->bullet_x -= 20 * cos(plane.angle * 3.14 / 180);//move bullet
            bul->bullet_y -= 20 * sin(plane.angle * 3.14 / 180);
        }
    }


    for (int i = 0; i < EBList.size(); i++)//PLANE IMPACT WITH ENEMYBULLECT
    {
        if (EBList.size() == 0)
        {
            break;
        }
        if ((abs(plane.position_x - EBList[i]->bullet_x) <= 40) && (abs(plane.position_y - EBList[i]->bullet_y) <= 40))
        {
            mciSendString("close exmusic", NULL, 0, NULL);
            mciSendString("open src\\EasyXFightPlane\\explode.mp3 alias exmusic", NULL, 0, NULL);
            mciSendString("play exmusic", NULL, 0, NULL);
            Plane::impactTime--;
            EnemyBullet* tmpEmemyBullet = EBList[i];
            EBList.erase(EBList.begin() + i);
            delete(tmpEmemyBullet);
            tmpEmemyBullet = NULL;
            if (EBList.size() == 0)
            {
                break;
            }
            //EList[i]->enemy_x = -6;
        }
    }


    for (int i = 0; i < BList.size(); i++)//ENEMY IMPACT WITH BULLECT
    {
        if (BList.size() == 0)
        {
            break;
        }
        if ((abs(enemy.enemy_x - BList[i]->bullet_x) <= 60) && (abs(enemy.enemy_y - BList[i]->bullet_y) <= 60))
        {
            mciSendString("close enemymusic", NULL, 0, NULL);
            mciSendString("open src\\EasyXFightPlane\\gotEnemy.mp3 alias enemymusic", NULL, 0, NULL);
            mciSendString("play enemymusic", NULL, 0, NULL);
            enemy.heath--;
            Bullet* tmpBullet = BList[i];
            BList.erase(BList.begin() + i);
            delete(tmpBullet);
            tmpBullet = NULL;
            if (BList.size() == 0)
            {
                break;
            }
            //EList[i]->enemy_x = -6;
        }
    }
    /*if ((enemy_x == position_x) && (enemy_y == position_y))//飞机相撞
    {
        enemy_x = 0;
        enemy_y = LZXrand();
    }*/
    EnemyBullet::speed++;
    EnemyBullet::creatSpeed++;
    if (EnemyBullet::speed >= enemyBulletSpeed)//move enemybullet
    {

        for (auto bul : EBList)
        {
            bul->bullet_x += 10 * sin((bul->angle * 3.14) / 180);
            bul->bullet_y += 10 * cos((bul->angle * 3.14) / 180);
        }
        EnemyBullet::speed = 0;
    }

    transeAngle++;
    if (transeAngle >= Enemy::transeAngle)
    {
        dir = LZXrand() % 9;
        transeAngle = 0;
    }

    if (dir == 0)
    {
        if (enemy.enemy_x + 3 >= High)
        {
            dir = 2;
        }
        else
        {
            enemy.enemy_x += 1;
        }

    }
    if (dir == 1)
    {
        if (enemy.enemy_y + 3 >= Width)
        {
            dir = 3;
        }
        else
        {
            enemy.enemy_y += 1;
        }
    }
    if (dir == 2)
    {
        if (enemy.enemy_x - 3 <= 0)
        {
            dir = 0;
        }
        else
        {
            enemy.enemy_x -= 1;
        }

    }
    if (dir == 3)
    {
        if (enemy.enemy_y - 3 <= 0)
        {
            dir = 1;
        }
        else
        {
            enemy.enemy_y -= 1;
        }
    }
    if (dir == 4)
    {
        if (enemy.enemy_x + 1 >= High || enemy.enemy_y + 1 >= Width)
        {
            dir = 7;
        }
        else
        {
            enemy.enemy_x += 1;
            enemy.enemy_y += 1;
        }
    }
    if (dir == 5)
    {
        if (enemy.enemy_x + 1 >= High || enemy.enemy_y - 1 <= 0)
        {
            dir = 6;
        }
        else
        {
            enemy.enemy_x += 1;
            enemy.enemy_y -= 1;
        }
    }
    if (dir == 6)
    {
        if (enemy.enemy_x - 1 <= 0 || enemy.enemy_y + 1 >= Width)
        {
            dir = 5;
        }
        else
        {
            enemy.enemy_x -= 1;
            enemy.enemy_y += 1;
        }
    }
    if (dir == 7)
    {
        if (enemy.enemy_x - 1 <= 0 || enemy.enemy_y - 1 <= 0)
        {
            dir = 4;
        }
        else
        {
            enemy.enemy_x -= 1;
            enemy.enemy_y -= 1;
        }
    }
    if (dir == 8)
    {
        //Stay
    }


    zhaoshiTime++;
    if (zhaoshiTime >= changeZhaoshi)
    {
        zhaoshi = LZXrand() % 2;
    }

    if (zhaoshi == 1)
    {

        if (EnemyBullet::creatSpeed >= creatBulletEnemy)
        {
            for (int i = 0; i < 9; i++)
            {
                EnemyBullet* enemyBullet = new EnemyBullet(enemy.enemy_x + 50, enemy.enemy_y + -10, angle2);
                EBList.push_back(enemyBullet);
                angle2 += 5;
            }
            angle2 = angle2 % 360;
            EnemyBullet::creatSpeed = 0;
        }
    }

    if (EnemyBullet::creatSpeed >= creatBulletEnemy && zhaoshi == 0)//CREAT ENEMYBULLET
    {
        int angle = 0;
        for (int i = 0; i < 8; i++)
        {
            EnemyBullet* enemyBullet = new EnemyBullet(enemy.enemy_x + 50, enemy.enemy_y + -10, angle);
            EBList.push_back(enemyBullet);
            angle += 45;
        }

        EnemyBullet::creatSpeed = 0;

    }

    for (int i = 0; i < EBList.size(); i++)//DISTORY ENEMYBULLET
    {
        if (EBList.size() == 0)
        {
            break;
        }
        if (EBList[i]->bullet_x >= High || EBList[i]->bullet_x <= 0 || EBList[i]->bullet_y >= Width - 30 || EBList[i]->bullet_y <= 0)
        {
            EnemyBullet* tmpEnemyBullet = EBList[i];
            EBList.erase(EBList.begin() + i);
            delete(tmpEnemyBullet);
            tmpEnemyBullet = NULL;
            //EList[i]->enemy_x = -6;
            //Plane::score--;
            if (EBList.size() == 0)
            {
                break;
            }


        }
    }

    for (int i = 0; i < BList.size(); i++)//distory Bullet
    {
        if (BList.size() == 0)
        {
            break;
        }
        if (BList[i]->bullet_x <= 0)
        {
            Bullet* tmpBullet = BList[i];

            BList.erase(BList.begin() + i);

            delete(tmpBullet);
            tmpBullet = NULL;
            //BList[i]->bullet_x = -5;
            if (BList.size() == 0)
            {
                break;
            }
        }
    }
}

int cdTime = 0;

void updateWithInput(Plane& plane, Enemy& enemy) //update with user input
{

    if (1)
    {
        cdTime++;
        //使用键盘上的上下左右键控制飞机
        if ((GetAsyncKeyState(VK_LEFT) & 0x8000))//左
        {
            if (plane.position_y > 1)
            {
                plane.position_y -= 1;
            }
            else
            {

            }
        }
        if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))//右
        {
            if (plane.position_y < Width - 60)
            {
                plane.position_y += 1;
            }
            else
            {

            }
        }
        if ((GetAsyncKeyState(VK_UP) & 0x8000))//上
        {
            if (plane.position_x > 1)
            {
                plane.position_x -= 1;
            }
            else
            {

            }
        }
        if ((GetAsyncKeyState(VK_DOWN) & 0x8000))//下
        {
            if (plane.position_x < High - 50)
            {
                plane.position_x += 1;
            }
            else
            {

            }
        }

        if ((GetAsyncKeyState(0x31) & 0x8000))
        {
            plane.angle = 0;
        }
        if ((GetAsyncKeyState(0x32) & 0x8000))
        {
            plane.angle = 45;
        }
        if ((GetAsyncKeyState(0x33) & 0x8000))
        {
            plane.angle = 90;
        }
        if ((GetAsyncKeyState(0x34) & 0x8000))
        {
            plane.angle = 135;
        }
        if ((GetAsyncKeyState(0x35) & 0x8000))
        {
            plane.angle = 180;
        }
        if ((GetAsyncKeyState(0x36) & 0x8000))
        {
            plane.angle = 225;
        }
        if ((GetAsyncKeyState(0x37) & 0x8000))
        {
            plane.angle = 270;
        }
        if ((GetAsyncKeyState(0x38) & 0x8000))
        {
            plane.angle = 315;
        }
        if (cdTime >= 20)
        {
            if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
            {


                mciSendString("close gunmusic", NULL, 0, NULL);
                mciSendString("open src\\EasyXFightPlane\\f_gun.mp3 alias gunmusic", NULL, 0, NULL);
                mciSendString("play gunmusic", NULL, 0, NULL);
                Bullet* bullet1 = new Bullet(plane.position_x - 51, plane.position_y - 60);
                Bullet* bullet2 = new Bullet(plane.position_x - 51, plane.position_y + 15);
                BList.push_back(bullet1);
                BList.push_back(bullet2);
                cdTime = 0;
            }
        }

        if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000))
        {
            outtextxy(2, Width / 2, "Paushed");
            outtextxy(2, Width / 2 + 40, "Press any key to be continue");
            FlushBatchDraw();
            _getch();
            _getch();

        }

    }
}




//Project name: FortyThousand(四万)  Version:2.1.1
//LZX Started write this code in 2023/08/30   21:00
//LZX Completed this code in 2023/09/14   22:
//LZX-TC-VS2022-2023-09-14-002