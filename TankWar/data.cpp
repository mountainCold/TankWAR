#include "data.h"

HANDLE g_hout = GetStdHandle(STD_OUTPUT_HANDLE); 
HANDLE g_hint = GetStdHandle(STD_INPUT_HANDLE); 
int Map[50][60] = { 0 };
int g_InitMap[50][60] = { 0 };
int g_EditMap[50][60] = { 0 }; //待编辑地图
int g_ReadMap[50][60] = { 0 }; //游戏载入地图
bool g_Game =true;
int gContinue =0;
extern int gLevel =1;//当前关卡数
int gMode = 1;
int gMCount = 0;
int gRCount = 0;
char(*gPMapName)[20] = { 0 };
char(*gPRecordName)[20] = { 0 };
COORD MousePos = { 0,0 };
Bullet b4;
Bullet b5;
Bullet b6;
Bullet b7;
Bullet b8;
Tank t4;
Tank t5;
Tank t6;
Tank t7;
Tank t8;
Tank *Ptank[5] = { &t4,&t5,&t6,&t7,&t8 };
Bullet* Pbullet[5] = { &b4,&b5,&b6,&b7,&b8 };
Tank MakeTank(int x,int heart)
{
	
	Tank tank;
	tank.bulletStat=1;	
	tank.Tsign = x;
	tank.heart = heart;
	if (x==4)
	{
		tank.dir = 'w';
		tank.x = 26;
		tank.y = 47;
		tank.bul.Bsign = 14;
		
	}
	else if (x==5)
	{
		tank.dir = 'w';
		tank.x = 33;
		tank.y = 47;
		tank.bul.Bsign = 15;
	}else if (x==6)
	{
		tank.dir = 's';
		tank.x = 2;
		tank.y = 2;
		tank.bul.Bsign = 16;
	}else if (x==7)
	{
		tank.dir = 's';
		tank.x = 29;
		tank.y = 2;
		tank.bul.Bsign = 17;
	}else if (x==8)
	{
		tank.dir = 's';
		tank.x = 57;
		tank.y = 2;
		tank.bul.Bsign = 18;
	}
	tank.bul.dir = tank.dir;
	return tank;
}