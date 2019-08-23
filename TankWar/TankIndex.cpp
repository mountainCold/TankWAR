#include<stdio.h>
#include<conio.h>

#include "data.h"
#include "draw.h"
#include "logic.h"

int main()
{	
	system("mode con cols=140 lines=50");
	InitMap();
	ReadName();
	ReadMap(*gPMapName);
	CopyMap(g_ReadMap, g_InitMap);
	char ch = 0;
	for (int i=0;i<5;i++)
	{
		*Ptank[i] = MakeTank(i + 4);//初始化坦克
		*Pbullet[i] = (*Ptank[i]).bul;//初始化子弹
	}
	SetConsoleTitle("坦克大战");
	WriteChar(28, 18, "坦克大战");
	bool bhome = true;
	int hmess = -1;
	while (bhome)
	{
		HomePage();
		ShowCuror();
		if (gContinue ==1)
		{
			WriteChar(24, 20, "7  继续游戏");
		}

		WriteChar(24, 22, "1  单人游戏");
		WriteChar(24, 24, "2  双人游戏");
		WriteChar(24, 26, "3  地图编辑");
		WriteChar(24, 28, "4  选择地图");
		WriteChar(24, 30, "5  读取存档");
		WriteChar(24, 32, "6  退出游戏");
		hmess = MessageListener();

		if (MousePos.X >= 48 && MousePos.X <= 76 && MousePos.Y == 22)
		{
			hmess = 1;
		}
		else if (MousePos.X >= 48 && MousePos.X <= 76 && MousePos.Y == 24)
		{
			hmess = 2;
		}		else if (MousePos.X >= 48 && MousePos.X <= 76 && MousePos.Y == 20)
		{
			hmess = 7;
		}
		else if (MousePos.X >= 48 && MousePos.X <= 76 && MousePos.Y == 26)
		{
			hmess = 3;
		}
		else if (MousePos.X >= 48 && MousePos.X <= 76 && MousePos.Y == 28)
		{
			hmess = 4;
		}
		else if (MousePos.X >= 48 && MousePos.X <= 76 && MousePos.Y == 30)
		{
			hmess = 5;
		}
		else if (MousePos.X >= 48 && MousePos.X <= 76 && MousePos.Y == 32)
		{
			hmess = 6;
		}
		MousePos = { 0,0 };
		if (hmess ==1)
		{
			for (int i = 0; i < 5; i++)
			{
				*Ptank[i] = MakeTank(i + 4);//初始化坦克
				*Pbullet[i] = (*Ptank[i]).bul;//初始化子弹
			}
			CopyMap(Map, g_ReadMap);
			gMode = 1;
			StartGame(gMode);
		}
		else if (hmess ==2)
		{

			for (int i = 0; i < 5; i++)
			{
				*Ptank[i] = MakeTank(i + 4);//初始化坦克
				*Pbullet[i] = (*Ptank[i]).bul;//初始化子弹
			}
			CopyMap(Map, g_ReadMap);
			gMode = 2;
			StartGame(gMode);
		}
		else if (hmess ==7)
		{
			if (gContinue ==1)
			{
				StartGame(gMode);
			}

		}
		else if (hmess == 3)
		{
			InitMap();
			EditMap();
		}
		else if (hmess == 4)
		{
			MapManage();
		}
		else if (hmess == 5)
		{
			RecordManage();
		}
		else if (hmess == 6)
		{
			bhome = false;
		}
		if (gLevel>1)
		{
			StartGame(gMode);
		}
		
	}
		
		
}
