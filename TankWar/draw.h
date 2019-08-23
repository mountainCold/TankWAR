#pragma once
#include "data.h"
/*
功能： 将传入的字符串在指定的位置打印出来
参数： 
int x ，int y 位置 坐标
const char* str 需要打印的字符串
*/
void WriteChar(int x, int y, const char* str, WORD color = 7);
void WriteChar(int x, int y, int heath, WORD color = 7);
/*
功能：打印一个坦克
参数：Tank 坦克结构体
*/
void WriteTank(Tank &tank);
/*
功能：打印一个坦克
参数：坦克中心点
*/
void WriteTank(int x, int y,int color);
/*
功能 清除坦克移动痕迹
*/
void ClearTank(Tank tank);
/*
功能 清除当前点的坦克
*/
void DelTank(Tank tank);
/*
* 将传入的字符串在指定的位置打印出来
*/
int WriteFood(int x,int y);
/*
功能 打印子弹
参数 子弹所属坦克
返回值 0 子弹继续飞行 1子弹消失
*/
int WriteBullet(Bullet* bul);
/*
功能 ：清除当前位置的子弹
*/
void ClearBullet(Bullet bullet);
/*记录地图
功能 绘制边界 和基地
*/
void WriteMap();
/*绘制待编辑地图
*/
void WriteEditMap();
/*初始化待编辑地图
*/
void InitMap(/*int Map[][60]*/);

/*绘制封面
功能 绘制欢迎/操作界面
*/
void HomePage();
