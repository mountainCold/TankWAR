#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std; 
#pragma once
#define  空地 0
#define  铁墙 1
#define  土墙 2
#define  草丛 30
#define  基地 10
#define  食物 9
#define  我方坦克1 4
#define  我方坦克2 5
#define  敌方坦克1 6
#define  敌方坦克2 7
#define  敌方坦克3 8
#define  我方子弹1 14
#define  我方子弹2 15
#define  敌方子弹1 16
#define  敌方子弹2 17
#define  敌方子弹3 18
extern HANDLE g_hout ; //输出句柄
extern HANDLE g_hint ;  //输入句柄
extern int Map[50][60]; //地图信息
extern int g_InitMap[50][60]; //被读取地图
extern int g_EditMap[50][60]; //待编辑地图
extern int g_ReadMap[50][60]; //游戏载入地图
extern bool g_Game;
extern COORD MousePos;
extern int gLevel;//当前关卡数
extern int gContinue;//继续游戏
extern int gMode;//游戏模式单人or双人
extern int gMCount;//Map 索引文件个数
extern int gRCount;//Record 索引文件个数
extern char (*gPMapName)[20];//地图索引名称数组

extern char (*gPRecordName)[20];//存档索引名称数组
typedef struct BULLET
{
	char dir; //子弹的方向
	int grade=1;//子弹的强度
	int Bsign; //子弹的标志符，14,15为己方子弹，16,17,18为敌方子弹
	int x=0; //子弹位置坐标
	int y=0;//子弹位置坐标
	const char* v = "○"; //子弹的形状
}Bullet;
typedef struct TANK
{
	char dir; //坦克的朝向
	int heart; //坦克的生命值
	int Tsign; //坦克标志符，4,5为己方坦克，6,7,8为敌方坦克
	int bulletStat; // 子弹状态 ，0表示已经发射 1可以发射
	int x;  //表示坦克中心位置的横坐标
	int y; //表示坦克中心位置的纵坐标
	Bullet bul; //子弹
}Tank;
extern Bullet b4;
extern Bullet b5;
extern Bullet b6;
extern Bullet b7;
extern Bullet b8;
extern Tank t4;
extern Tank t5;
extern Tank t6;
extern Tank t7;
extern Tank t8;
extern Tank *Ptank[5];
extern Bullet *Pbullet[5];
/*
功能：制造坦克
参数： 4,5,6,7,8分别表示制造己方1,2号，敌方1.2.3号坦克
*/
Tank MakeTank(int x,int heart=3);