#pragma once
#include "data.h"
#define KEYDOWN(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)
/*
功能 敌方坦克随机移动
参数 敌方坦克 移动间隔
*/
void AutoMoveForOPPTank(Tank& tank,int nT);
/*
功能 坦克移动检测 坦克不能向界外，或其他坦克上面移动
参数 坦克
返回值 0可以正常移动 1遇到障碍物
*/
int TankMoveDetection(Tank& tank);
/*子弹碰撞检测
功能 判断子弹是否遇到障碍物 并作出相应的响应
返回值 0子弹继续飞行 1子弹消失
*/
int BulletCollisionDetection(Bullet bullet);
/*
方向逻辑判断
*/
void OpCodeDetection(Tank& tank, char ch);
/*
游戏时的说明性文字
*/
void GameShows();
/*开始游戏
功能 游戏运行页面逻辑
参数 几人游戏
*/
void StartGame(int x);
/*编辑地图
功能 自定义编辑地图
参数 需要编辑的地图
*/
void EditMap();
/*
事件监听器
*/
int MessageListener (int x =0);
/*
多按键监听 
*/
void KeyListener(char& ch1,char& ch2, char& bch1, char& bch2);
/*
单按键监听
*/
int KeyListener();
/*射击*/
void OpenFire(Tank& tank, char ch);
/*
隐藏光标
*/
void ShowCuror();
/*
功能：删除数组指针中的某一元素
参数：mark 0表示gPMapName 1表示 gPRecordName
	 元素下标
*/
void DeleteName(int mark,int index);
/*
功能 删除文件 
参数 文件名  和标志符 0表示gPMapName 1表示 gPRecordName
*/
void ClearFile(char* name, int mark);
/*
保存地图
*/
void SaveMap();

/*
读取地图
参数 地图名称
*/
void ReadMap(char* mName);
/*
保存地图
*/
void SaveRecord();
/*
地图拷贝
参数 将第二个地图信息拷贝到第一个地图中
*/
void CopyMap(int a[][60], int b[][60]);
/*
读取地图
参数 地图名称
*/
void ReadRecord(char* mName);
/*
档案管理
*/
void RecordManage();
/*
画方框
参数 四个点的坐标
*/
void DwFrame(int x1, int x2, int y1, int y2, int n);
/*
保存索引
参数  pst 需要保存的索引名  int n 标识符 声明是地图（0）还是存档（1）
*/
void SaveName(char* pst, int n);
void SaveName();
/*
读取索引
*/
void ReadName();
/*地图管理
*/
void MapManage();