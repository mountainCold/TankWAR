#include "logic.h"
#include "draw.h"
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <tchar.h>
void ShowCuror()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hout, &cci);
}
void AutoMoveForOPPTank(Tank& tank,int nT)
{
	if (tank.x > 1 || tank.y > 1 || tank.x < 58 || tank.y < 48)
	{
		WriteTank(tank);
	}
	int num = 0;
	char ch = 0;
	srand(tank.Tsign* (int)time(NULL));
	num = rand() % 7;
	if (num == 0)
	{
		ch = 'w';
	}
	if (num == 1||num==4)
	{
		ch = 's';
	}
	if (num == 2)
	{
		ch = 'a';
	}
	if (num == 3)
	{
		ch = 'd';
	}
	if (num>=5)
	{
		OpenFire(tank,'j');
	}
	if (nT>=9)
	{
		if (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd')
		{
			if (tank.x > 1 || tank.y > 1 || tank.x < 58 || tank.y < 48)
			{
				tank.dir = ch;
				WriteTank(tank);
			
			}
		}
		OpCodeDetection(tank, ch);
	} 
	
}
int TankMoveDetection(Tank& tank)
{
	for (int i=tank.x-1;i<tank.x+2;i++)
	{
		for (int j = tank.y - 1; j < tank.y + 2; j++)
		{
			if (Map[j][i]>=4&& Map[j][i] <= 8&& Map[j][i] !=tank.Tsign|| 
				Map[j][i] == 1 || Map[j][i] == 2 || Map[j][i] == 10)//遇到边界移动回滚
			{
				return 1;
			}
			if (Map[j][i]==草丛)
			{
				Map[j][i] += tank.Tsign;
			}
			if (Map[j][i] == 食物)
			{
				Map[j][i] = 0;
				tank.heart += 1;
			}
		}
	}
	
	return 0;
}
int BulletCollisionDetection(Bullet bullet)
{
	if (Map[bullet.y][bullet.x]==铁墙)
	{
		if (bullet.Bsign<=15)
		{
			PlaySound("sound\\触界.wav", NULL, SND_FILENAME | SND_ASYNC);
		}
		
		return 1;
	}
	else if (Map[bullet.y][bullet.x]==土墙)
	{
		PlaySound("sound\\土墙爆炸.wav", NULL, SND_FILENAME | SND_ASYNC);
		Map[bullet.y][bullet.x] = 0;
		WriteChar(bullet.x, bullet.y,"  ");
		return 1;
	}
	else if (Map[bullet.y][bullet.x] == 基地)
	{
		g_Game = false;
		return 1;
	}
	else if (Map[bullet.y][bullet.x] == 草丛)
	{
		Map[bullet.y][bullet.x] += bullet.Bsign;
		return 草丛;
	}
	else if (Map[bullet.y][bullet.x] == 食物)
	{
		return 草丛;
	}
	//子弹遇到坦克
	else if (Map[bullet.y][bullet.x] >= 我方坦克1&&Map[bullet.y][bullet.x] <= 敌方坦克3)
	{
		int x = bullet.Bsign % 10;
		int y = Map[bullet.y][bullet.x];
		// 是同阵营的子弹 没有任何影响
		if (x>= 我方坦克1 &&x <= 我方坦克2&& y >= 我方坦克1 && y <= 我方坦克2||
			x >= 敌方坦克1 && x <= 敌方坦克3 && y >= 敌方坦克1 && y <= 敌方坦克3)
		{
			return 0;
		}
		// 不同阵营子弹
		else 
		{
			PlaySound("sound\\命中爆炸.wav", NULL, SND_FILENAME | SND_ASYNC);
			for (int i=0;i<5;i++)
			{
				if ((*Ptank[i]).Tsign == Map[bullet.y][bullet.x])
				{
					DelTank(*Ptank[i]);
					if ((*Ptank[i]).bulletStat==0)
					{
						ClearBullet(*Pbullet[i]);
					}	
					(*Ptank[i]).heart--;
					if ((*Ptank[i]).heart>0)
					{ 					
						*Ptank[i] = MakeTank((*Ptank[i]).Tsign,(*Ptank[i]).heart);
					}
					else
					{
						
						*Ptank[i] = MakeTank((*Ptank[i]).Tsign,0);
					}
				}				
			}
			return 1;
			
		}
	}
	//子弹遇到子弹
	else if (Map[bullet.y][bullet.x] >= 我方子弹1 && Map[bullet.y][bullet.x] <= 敌方子弹3)
	{
		int x = bullet.Bsign;
		int y = Map[bullet.y][bullet.x];
		//同阵营
		if (x >= 我方子弹1 && x <= 我方子弹2 && y >= 我方子弹1 && y <= 我方子弹2 ||
			x >= 敌方子弹1 && x <= 敌方子弹3 && y >= 敌方子弹1 && y <= 敌方子弹3)
		{
			return 0;
		}
		//不同阵营
		else
		{		
			PlaySound("sound\\炮弹爆炸.wav", NULL, SND_FILENAME | SND_ASYNC);
			for (int i=0;i<5;i++)
			{
				if ((*Pbullet[i]).Bsign == y)
				{

					ClearBullet((*Pbullet[i]));
					(*Ptank[i]).bulletStat = 1;
				}

			}
			ClearBullet(bullet);
			return 1;
		}

	}
	//遇到草丛怪
	else if (Map[bullet.y][bullet.x]>草丛)
	{
		int Mnum =Map[bullet.y][bullet.x] - 草丛;
		if (Mnum >= 我方坦克1 && Mnum <= 敌方坦克3)
		{

			int x = bullet.Bsign % 10;
			int y = Map[bullet.y][bullet.x];
			// 是同阵营的坦克 没有任何影响
			if (x >= 我方坦克1 && x <= 我方坦克2 && Mnum >= 我方坦克1 && Mnum <= 我方坦克2 ||
				x >= 敌方坦克1 && x <= 敌方坦克3 && Mnum >= 敌方坦克1 && Mnum <= 敌方坦克3)
			{
				return 草丛;
			}
			// 不同阵营坦克
			else
			{
				PlaySound("sound\\命中爆炸.wav", NULL, SND_FILENAME | SND_ASYNC);
				for (int i = 0; i < 6; i++)
				{
					if ((*Ptank[i]).Tsign == Mnum)
					{
						DelTank(*Ptank[i]);
						if ((*Ptank[i]).bulletStat == 0)
						{
							ClearBullet(*Pbullet[i]);
						}
						(*Ptank[i]).heart--;
						if ((*Ptank[i]).heart > 0)
						{
							*Ptank[i] = MakeTank((*Ptank[i]).Tsign, (*Ptank[i]).heart);
						}
						else
						{

							*Ptank[i] = MakeTank((*Ptank[i]).Tsign, 0);
						}
						return 1;
					}
					
				}
			
				return 1;
			}
		}
		//子弹遇到子弹
		if (Map[bullet.y][bullet.x] >= 我方子弹1 && Map[bullet.y][bullet.x] <= 敌方子弹3)
		{
			int x = bullet.Bsign;
			int y = Map[bullet.y][bullet.x];
			//同阵营
			if (x >= 我方子弹1 && x <= 我方子弹2 && Mnum >= 我方子弹1 && Mnum <= 我方子弹2 ||
				x >= 敌方子弹1 && x <= 敌方子弹3 && Mnum >= 敌方子弹1 && Mnum <= 敌方子弹3)
			{
				return 草丛;
			}
			//不同阵营
			else
			{
				PlaySound("sound\\炮弹爆炸.wav", NULL, SND_FILENAME | SND_ASYNC);
				for (int i = 0; i < 5; i++)
				{
					if ((*Pbullet[i]).Bsign == Mnum)
					{

						ClearBullet((*Pbullet[i]));
						(*Ptank[i]).bulletStat = 1;
					}

				}
				ClearBullet(bullet);
				return 1;
			}

		}
	}
	else {
		return 0;
	}
	return 0;
}
void OpCodeDetection(Tank& tank, char ch)
{
	int flag = 0;	
	switch (ch)
		{
		case 'w':
		{
			--tank.y;
			if (TankMoveDetection(tank) != 0)
			{
				flag = 1;
				++tank.y;
			}
		}break;
		case 's':
		{
			++tank.y;
			if (TankMoveDetection(tank) != 0)
			{
				flag = 1;
				--tank.y;
			}
		}break;
		case 'a':
		{
			--tank.x;
			if (TankMoveDetection(tank) != 0)
			{
				flag = 1;
				++tank.x;
			}

		}break;
		case 'd':
		{
			++tank.x;
			if (TankMoveDetection(tank) != 0)
			{
				flag = 1;
				--tank.x;
			}
		}break;
		
		default:
			flag = 1;
			break;
		}	
	if (flag==0)
	{
		if (tank.x > 2 || tank.y > 2 || tank.x < 58 || tank.y < 48)
		{
			WriteTank(tank);
			ClearTank(tank);
		}
	}
	
}
void OpenFire(Tank &tank,char ch)
{
	if (ch == 'j')
	{
		if (tank.bulletStat == 1)
		{

			tank.bulletStat = 0;
			int numT = tank.Tsign - 4;
			*Pbullet[numT] = tank.bul;
		}

	}
}
void GameShows()
{
	SetConsoleTitle("正在游戏");
	WriteChar(62, 2, "坦克大战", 7);
	WriteChar(61, 4, "游戏说明:", 7);
	WriteChar(61, 6, "Space :", 7);
	WriteChar(64, 6, "键暂停:", 7);
	WriteChar(61, 8, "ESC", 7);
	WriteChar(63, 8, "键强制退出", 7);
	WriteChar(61, 10, "1|2号玩家:", 7);
	WriteChar(61, 12, "w|5   上", 7);
	WriteChar(61, 14, "s|2   下", 7);
	WriteChar(61, 16, "a|1   左", 7);
	WriteChar(61, 18, "d|3   右", 7);
	WriteChar(61, 20, "j|4    开火", 7);
	WriteChar(60, 21, "==================", 7);
	WriteChar(61, 22, "敌军数量：", 7);
	WriteTank(62, 24, 6);
	WriteChar(65, 24, "X", 7);
	WriteTank(62, 28, 7);
	WriteChar(65, 28, "X", 7);
	WriteTank(62, 32, 8);
	WriteChar(65, 32, "X", 7);
	WriteChar(61, 35, "我方生命：", 7);
	WriteTank(62, 37, 4);
	WriteChar(65, 37, "X", 7);
}
void StartGame(int x)
{
	system("cls");
	PlaySound("sound\\开始音乐.wav", NULL, SND_FILENAME | SND_ASYNC);
	int Tnum = 0,Anum=0, Fnum=0, Bnum = 0;//定时敌我坦克和子弹,和食物
	int Bfood = 0; //食物是否存在 0不存在 1存在
	int fonums = 0; //刷新次数
	int Foodx = 0;
	int Foody = 0;
	gContinue = 0;
	char ch = 0;
	char ch1 = 0;
	char ch2 = 0;
	char bch1 = 0;
	char bch2 = 0;
	g_Game = true;	
	//文字描述
	GameShows();
 	for (int i = 0; i < 5; i++)
 	{
		if ((*Ptank[i]).bulletStat == 0)
 		{
 			if (WriteBullet(Pbullet[i]) != 0)
 			{
 				(*Ptank[i]).bulletStat = 1;
 			}
 		}
 	}
	WriteTank(t4);
	WriteTank(t6);
	WriteTank(t7);
	WriteTank(t8);

	WriteMap();
	if (x>1)
	{
		WriteTank(62, 41, 5);
		WriteChar(65, 41, "X", 7);
		WriteTank(t5);
	}
	while (g_Game)
	{
		int kills = 0;//等于三时游戏结束！
		ShowCuror();	
		if (Tnum >= 6)
		{
			Tnum = 0;
		
			KeyListener(ch1,ch2,bch1,bch2);
			if (ch1 ==32)
			{
				system("cls");
				ch = 0;
				DwFrame(22, 42, 16, 28, 5);
				SetConsoleTitle("游戏暂停");
				while (ch != 32)
				{
				
					WriteChar(30, 19, "游戏暂停！", 7);
					WriteChar(25, 21, "请按Escape键返回主界面", 7);
					WriteChar(25, 23, "请按空格键返回游戏", 7);
					WriteChar(25, 25, "按回车键保存本地并退出", 7);
					ch = _getch();
					
					if (ch==27)
					{
						gContinue = 1;
						g_Game = false;
						break;
					}
					if (ch == 13)
					{
						SaveRecord();
						ch = 27;
						break;
					}

				}
				system("cls");
				WriteMap();
				GameShows();
			}
			if (ch1 == 'w' || ch1 == 's' || ch1 == 'a' || ch1 == 'd')
			{
				t4.dir = ch1;
			}
			if (ch2 == 'w' || ch2 == 's' || ch2 == 'a' || ch2 == 'd')
			{
				t5.dir = ch2;
			}
			WriteTank(t4);
			OpCodeDetection(t4, ch1);
			OpenFire(t4, bch1);
			if (x > 1)
			{
				if (t4.heart == 0 && t5.heart == 0)
				{
					PlaySound("sound\\失败.wav", NULL, SND_FILENAME | SND_ASYNC);
					system("cls");
					DwFrame(22, 42, 16, 35, 5);
					SetConsoleTitle("游戏失败");
					WriteTank(29, 19, 6);
					WriteTank(29, 23, 7);
					WriteTank(29, 27, 8);
					WriteChar(33, 19, "X", 7);
					WriteChar(33, 23, "X", 7);
					WriteChar(33, 27, "X", 7);
					WriteChar(35, 19, t6.heart, 7);
					WriteChar(35, 23, t7.heart, 7);
					WriteChar(35, 27, t8.heart, 7);
					WriteChar(27, 31, "长官，请再接再厉！", 7);
					WriteChar(27, 33, "按回车键返回主界面", 7);
					ch = 0;
					while (ch != 13)
					{
						if (_kbhit() == 1)
						{
							ch = _getch();
						}
					}
					system("cls");
					g_Game = false;
				}
				WriteTank(t5);
				OpCodeDetection(t5, ch2);
				OpenFire(t5, bch2);
			}
			else
			{
				if (t4.heart == 0)
				{
					PlaySound("sound\\失败.wav", NULL, SND_FILENAME | SND_ASYNC);
					system("cls");
					DwFrame(22, 42, 16, 35, 5);
					SetConsoleTitle("游戏失败");
					WriteTank(29, 19, 6);
					WriteTank(29, 23, 7);
					WriteTank(29, 27, 8);
					WriteChar(33, 19, "X", 7);
					WriteChar(33, 23, "X", 7);
					WriteChar(33, 27, "X", 7);
					WriteChar(35, 19, t6.heart, 7);
					WriteChar(35, 23, t7.heart, 7);
					WriteChar(35, 27, t8.heart, 7);
					WriteChar(27, 31, "长官，请再接再厉！", 7);
					WriteChar(27, 33, "按回车键返回主界面", 7);
					ch = 0;
					while (ch != 13)
					{
						if (_kbhit() == 1)
						{
							ch = _getch();
						}
					}
					system("cls");
					g_Game = false;
				}
			}

		}

		for (int i=2;i<5;i++)
		{
			if (Ptank[i]->heart>0)
			{
				AutoMoveForOPPTank(*(Ptank[i]), Anum+gLevel);
			}else
			{
				kills++;
			}
		}
		if (Bfood == 0)
		{
			srand((int)time(NULL));
			if (rand()%3 ==1)
			{
				if (kills ==fonums)
				{
					srand((int)time(NULL));
					 Foodx = rand() % 56 + 1;
					 Foody = rand() % 46 + 1;
					if (WriteFood(Foodx, Foody)==1)
					{
						fonums++;
						Bfood = 1;
					}	
				}
			}
		}
		else
		{
			Fnum++;
		}
		if (kills==3)
		{
			PlaySound("sound\\胜利.wav", NULL, SND_FILENAME | SND_ASYNC);
			system("cls");
			DwFrame(22, 42, 16, 37, 5);
			SetConsoleTitle("游戏胜利");
			WriteTank(29, 19, 6);
			WriteTank(29, 23, 7);
			WriteTank(29, 27, 8);
			WriteChar(33, 19, "X", 7);
			WriteChar(33, 23, "X", 7);
			WriteChar(33, 27, "X", 7);
			WriteChar(35, 19, 3, 7);
			WriteChar(35, 23, 3, 7);
			WriteChar(35, 27, 3, 7);
			WriteChar(26, 31, "干的漂亮，指挥官阁下！", 7);
			WriteChar(26, 33, "按回车键进入下一关", 7);
			WriteChar(26, 35, "按ESc键返回主界面", 7);
			ch = 0;
			while (true)
			{
				if (_kbhit() == 1)
				{
					ch = _getch();
				}
				if (ch == 13)
				{
					t4.x = 26; t4.y = 47;
					t5.x = 33; t5.y = 47;
					t6.heart = 3 + gLevel / 3;
					t7.heart = 3 + gLevel / 3;
					t8.heart = 3 + gLevel / 3;
					ReadMap(*(gPMapName + gLevel));
					gLevel++;
					system("cls");
					g_Game = false;
					break;

				}
				else if (ch == 27)
				{
					gLevel = 1;
					system("cls");
					g_Game = false;
					break;
				}
				
			}
			
			
		}
		if (Bnum >= 0)
		{
			Bnum = 0;
			for (int i = 0; i < 5; i++)
			{
				if ((*Ptank[i]).bulletStat == 0)
				{
					if (WriteBullet(Pbullet[i]) != 0)
					{
						(*Ptank[i]).bulletStat = 1;
					}
				}
			}
		}

		WriteChar(67, 24, t6.heart, 7);
		WriteChar(67, 28, t7.heart, 7);
		WriteChar(67, 32, t8.heart, 7);
		WriteChar(67, 37, t4.heart, 7);
		if (x>1)
		{
			WriteChar(67, 41, t5.heart, 7);
		}
		Sleep(10);
		Tnum++;
		Bnum++;
		if (Anum>=9)
		{
			Anum = 0;
		}
		Anum++;
		if (Fnum>=1000)
		{
			WriteChar(Foodx, Foody, "  ");
			Map[Foody][Foodx] = 0;
			Bfood = 0;
			Fnum = 0;
		}
	}
	
	system("cls");
}
void EditMap()
{
	system("cls");

	WriteEditMap();
	WriteChar(63, 3, "坦克大战", 7);
	WriteChar(61, 5, "编辑说明:", 7);
	WriteChar(61, 7, "点击击以下图标:", 7);
	WriteChar(62, 8, "选择物体:", 7);
	WriteChar(61, 10, "左键绘制:", 7);
	WriteChar(61, 12, "点击清空:", 4);
	const char* str = "▓";
	int num = 土墙;
	WriteChar(61, 15, "▓▓   土墙", 6);
	WriteChar(61, 17, "■■   铁墙", 7);
	WriteChar(61, 19, "※※   草丛", 3);
	WriteChar(61, 21, "XXXX   空地");
	WriteChar(61, 26, "点击");
	WriteChar(63, 26, "退出", 4);
	WriteChar(61, 28, "点击");
	WriteChar(63, 28, "保存本地", 4);
	bool bedit = true;
	int nMessage = 0;
	while (bedit)
	{
		ShowCuror();
		nMessage = MessageListener(1);
		if (nMessage ==27)
		{
			bedit = false;
			system("cls");
		}else if (nMessage ==13)
		{
			SaveMap();
			
			ReadName();
		}
		if (MousePos.X > 1 && MousePos.X < 118 && MousePos.Y>0 && MousePos.Y< 49)
		{
			if (MousePos.X > 56 && MousePos.X < 62 && MousePos.Y>46 && MousePos.Y <= 48)
			{
				
			}
			else
			{
				if (num == 10)
				{
					WriteChar(MousePos.X / 2, MousePos.Y, str,9);
				}
				else if (num == 30)
				{
					WriteChar(MousePos.X / 2, MousePos.Y,str, 5);
				}
				else
				{
					WriteChar(MousePos.X / 2, MousePos.Y, str, 8 - num);
				}
				g_EditMap[MousePos.Y][MousePos.X / 2] = num;
			}
			
			
		}
		else if (MousePos.X >= 122 && MousePos.X <= 134 && MousePos.Y == 15)
		{
			str = "▓";
			num = 土墙;

		}
		else if (MousePos.X >= 122 && MousePos.X <= 134 && MousePos.Y == 17)
		{
			str = "■";
			num = 铁墙;
		}
		else if (MousePos.X >= 122 && MousePos.X <= 134 && MousePos.Y == 19)
		{
			
			str = "※";
			num = 草丛;
		}
		else if (MousePos.X >= 122 && MousePos.X <= 134 && MousePos.Y == 21)
		{
			
			str = "  ";
			num = 空地;
		}
		else if (MousePos.X >= 122 && MousePos.X <= 134 && MousePos.Y == 26)
		{
			bedit = false;
			system("cls");
		}
		else if (MousePos.X >= 122 && MousePos.X <= 134 && MousePos.Y == 12)
		{
			
			for (int i=2;i<118;i++)
			{
				for (int j=1;j<49;j++)
				{
					if (i > 56 && i < 62 && j>46 && j <= 48)
					{

					}
					else
					{
						WriteChar(i / 2, j, "  ");
						Map[j][i / 2] = 0;
					}
				}
			}

		}
		else if (MousePos.X >= 122 && MousePos.X <= 134 && MousePos.Y == 28)
		{
	
			SaveMap();
			ReadName();
			bedit = false;
		}
		MousePos = { 0,0 };
	}
	
	system("cls");
}
int MessageListener(int x)
{
	
	INPUT_RECORD ir = { 0 };
	DWORD dwCount = 0;
	DWORD dwt = 0;
	bool stat = true;
	GetConsoleMode(g_hint, &dwt);

	SetConsoleMode(g_hint, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT |dwt);
	
	//CONSOLE_SCREEN_BUFFER_INFO csbi;
	while (stat)
	{
		ReadConsoleInput(
			g_hint,  //输出句柄，固定写法  传入参数
			&ir,     //用于获取在控制台上的信息   传出参数
			1,       //ir 的个数            传入参数
			&dwCount //传出的，读取了多少个信息

		);
		if (ir.EventType == MOUSE_EVENT)
		{

			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (MousePos.X > 1 && MousePos.X < 118 && MousePos.Y>0 && MousePos.Y < 49)
				{
					if (x == 0)
					{
						PlaySound("sound\\鼠标点击.wav", NULL, SND_FILENAME | SND_ASYNC);
					}
				}					
				MousePos = ir.Event.MouseEvent.dwMousePosition;
				stat = false;
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
	

			}
			return 0;
		}
		else if (ir.EventType == KEY_EVENT)
		{
			return KeyListener();
		}
		return 0;
	}
	return 0;
}
void KeyListener(char& ch1,char& ch2, char& bch1, char& bch2)
{
	if (KEYDOWN(27))
	{
		g_Game = false;
		gLevel = 1;
	
	}
	if (KEYDOWN(13))
	{
		if (t4.heart>1&&t5.heart ==0)
		{
			t4.heart--;
			t5.heart++;
		}
		if (t5.heart > 1 && t4.heart == 0)
		{
			t5.heart--;
			t4.heart++;
		}
	}
	if (KEYDOWN(87)!=0)
	{
		ch1 = 'w';
	}
	else if (KEYDOWN(83))
	{
		ch1 = 's';
	}
	else if (KEYDOWN(32))
	{
		ch1 = 32;
	}
	else if (KEYDOWN(65))
	{
		ch1 = 'a';
	}
	else if (KEYDOWN(68))
	{
		ch1 = 'd';
	}
	else {
		ch1 = 0;
	}
	if (KEYDOWN(101))
	{
		ch2 = 'w';
	}else if (KEYDOWN(98))
	{
		ch2 = 's';
	}else if (KEYDOWN(97))
	{
		ch2 = 'a';
	}else if (KEYDOWN(99))
	{
		ch2 = 'd';
	}
	else
	{
		ch2 = 0;
	}
	if (KEYDOWN(74))
	{
		bch1 = 'j';
	}
	else
	{
		bch1 = 0;
	}
	 if (KEYDOWN(100))
	{
		bch2 = 'j';
	 }
	 else
	 {
		 bch2 = 0;
	 }

}
int KeyListener()
{
	if (KEYDOWN(27)) //27 Escape 键
	{
		return 27;
	}
	else if (KEYDOWN(13)) //13 Enter 键
	{
		return 13;
	}else if (KEYDOWN(32)) //32 Space 键
	{
		return 32;
	}
	else if (KEYDOWN(97))
	{
		return 1;
	}else if (KEYDOWN(98))
	{
		return 2;
	}else if (KEYDOWN(99))
	{
		return 3;
	}else if (KEYDOWN(100))
	{
		return 4;
	}else if (KEYDOWN(101))
	{
		return 5;
	}else if (KEYDOWN(102))
	{
		return 6;
	}else if (KEYDOWN(103))
	{
		return 7;
	}else if (KEYDOWN(104))
	{
		return 8;
	}else if (KEYDOWN(105))
	{
		return 9;
	}
	return 0;
	

}
void DwFrame(int x1, int x2, int y1, int y2, int n)
{

	for (int j = y1; j < y2; j++)
	{
		WriteChar(x1, j, "□", n % 7 + 2);
	}
	for (int jj = y1; jj <= y2; jj++)
	{
		WriteChar(x2, jj, "□", n % 7 + 2);
	}

	for (int ii = x1; ii < x2; ii++)
	{
		WriteChar(ii, y1, "□", n % 7 + 2 | 3);
	}
	for (int i = x1; i < x2; i++)
	{
		WriteChar(i, y2, "□", n % 7 + 2 | 5);
	}
}
void ReadRecord(char* mName)
{
	char str[30] ;
	strcpy_s(str, 30, "data//");
	strcat_s(str, 30, mName);
	strcat_s(str, 30, ".rec");

	
	FILE* pfile;
	errno_t err = fopen_s(&pfile, str, "rb");

	if (err != 0)
	{
		return;
	}
	//先读初始地图
	fread(Map, sizeof(Map), 1, pfile);
	//再读坦克
	fread(&t4, sizeof(Tank), 1, pfile);
	t4.bul.v= "○";
	fread(&t5, sizeof(Tank), 1, pfile);
	t5.bul.v = "○";
	fread(&t6, sizeof(Tank), 1, pfile);
	t6.bul.v = "○";
	fread(&t7, sizeof(Tank), 1, pfile);
	t7.bul.v = "○";
	fread(&t8, sizeof(Tank), 1, pfile);
	t8.bul.v = "○";
	//然后读子弹
	fread(&b4, sizeof(Bullet), 1, pfile);
	b4.v = "○";
	fread(&b5, sizeof(Bullet), 1, pfile);
	b5.v = "○";
	fread(&b6, sizeof(Bullet), 1, pfile);
	b6.v = "○";
	fread(&b7, sizeof(Bullet), 1, pfile);
	b7.v = "○";
	fread(&b8, sizeof(Bullet), 1, pfile);
	b8.v = "○";
	
	//读游戏模式 单人or双人
	fread(&gMode, 4, 1, pfile);
	fclose(pfile);
}
void SaveRecord()
{
	char mName[20];
	system("cls");
	DwFrame(18, 38, 16, 24, 5);
	WriteChar(22, 20, "请输入存档名称:", 7);
	COORD cor = { 48,22 };
	SetConsoleCursorPosition(g_hout, cor);
	scanf_s("%s",mName, 20);
	SaveName(mName, 1);
	system("cls");
	char str[30];
	strcpy_s(str, 30, "data//");
	strcat_s(str, 30, mName);
	strcat_s(str, 30, ".rec");

	FILE* pfile;
	errno_t err = fopen_s(&pfile, str, "wb");

	if (err != 0)
	{
		return;
	}
	//先存初始地图
	WriteMap();
	fwrite(Map, sizeof(Map), 1, pfile);
	//再存坦克
	fwrite(&t4, sizeof(Tank), 1, pfile);
	fwrite(&t5, sizeof(Tank), 1, pfile);
	fwrite(&t6, sizeof(Tank), 1, pfile);
	fwrite(&t7, sizeof(Tank), 1, pfile);
	fwrite(&t8, sizeof(Tank), 1, pfile);
	//然后存子弹
	fwrite(&b4, sizeof(Bullet), 1, pfile);
	fwrite(&b5, sizeof(Bullet), 1, pfile);
	fwrite(&b6, sizeof(Bullet), 1, pfile);
	fwrite(&b7, sizeof(Bullet), 1, pfile);
	fwrite(&b8, sizeof(Bullet), 1, pfile);
	//存游戏模式 单人or双人
	fwrite(&gMode, 4, 1, pfile);
	fclose(pfile);
}
void ReadMap(char* mName)
{
	char str[30];
	strcpy_s(str, 30, "data//");
	strcat_s(str, 30, mName);
	strcat_s(str, 30, ".map");

	FILE* pfile;
	errno_t err = fopen_s(&pfile, str, "rb");;
	if (err != 0)
	{
		
		return;
	}
	fread(g_InitMap, sizeof(Map), 1, pfile);
	
	fclose(pfile);
}
void SaveMap()
{
 	char mName[20];
 	system("cls");
 	DwFrame(18, 38, 16, 24, 5);
 	WriteChar(22, 20, "请输入地图名称:", 7);
 	COORD cor = { 48,22 };
 	SetConsoleCursorPosition(g_hout, cor);
 	scanf_s("%s",mName, 20);
	SaveName(mName, 0);
 	system("cls");
	char str[30];
	strcpy_s(str, 30, "data//");
	strcat_s(str, 30, mName);
	strcat_s(str, 30, ".map");

	FILE* pfile;
	errno_t err = fopen_s(&pfile, str, "wb");

	if (err != 0)
	{

		return;
	}
	fwrite(g_EditMap, sizeof(Map), 1, pfile);
	
	fclose(pfile);
}
void SaveName(char* pst, int n)
{
	FILE* pfile;
	errno_t err = fopen_s(&pfile, "data\\Name.tank", "wb");
	if (err != 0)
	{
		return;
	}
	if(n == 0)
	{
		gMCount++;
		fwrite(&gMCount, 4, 1, pfile);
		fwrite(&gRCount, 4, 1, pfile);
		gPMapName = (char(*)[20]) realloc(gPMapName, 20 * gMCount);
		strcpy_s(*(gPMapName + gMCount - 1), 20, pst);
		fwrite(gPMapName, 20*gMCount, 1, pfile);
		if (gRCount!=0)
		{
			fwrite(gPRecordName, 20 * gRCount, 1, pfile);
		}
	
	}
	else if (n == 1)
	{
		gRCount++;
		fwrite(&gMCount, 4, 1, pfile);
		fwrite(&gRCount, 4, 1, pfile);
		if (gMCount!=0)
		{
			fwrite(gPMapName, 20 * gMCount, 1, pfile);
		}

		gPRecordName = (char(*)[20]) realloc(gPRecordName, 20 * gRCount);
		strcpy_s(*(gPRecordName + gRCount - 1), 20, pst);
		fwrite(gPRecordName, 20 * gRCount, 1, pfile);
	}
	

	
	fclose(pfile);
}
void SaveName()
{
	FILE* pfile;
	errno_t err = fopen_s(&pfile, "data\\Name.tank", "wb");
	if (err != 0)
	{
		return;
	}
	fwrite(&gMCount, 4, 1, pfile);
	fwrite(&gRCount, 4, 1, pfile);
	if (gMCount != 0)
	{

		fwrite(gPMapName, 20 * gMCount, 1, pfile);
	}
	if (gRCount != 0)
	{
		fwrite(gPRecordName, 20 * gRCount, 1, pfile);
	}
	fclose(pfile);
}
void ReadName()
{
	FILE* pfile;
	errno_t err = fopen_s(&pfile, "data\\Name.tank", "rb");
	if (err != 0)
	{
		return;
	}
	fread(&gMCount, 4, 1, pfile);
	fread(&gRCount, 4, 1, pfile);
	if (gMCount!=0)
	{
		gPMapName = (char(*)[20])calloc(gMCount, 20);
		fread(gPMapName, 20*gMCount, 1, pfile);
	}
	if (gRCount!=0)
	{
		gPRecordName = (char(*)[20])calloc(gRCount, 20);
		fread(gPRecordName, 20*gRCount, 1, pfile);
	}
	
	


	fclose(pfile);
}
void RecordManage()
{
	SetConsoleTitle("档案管理");
	int page = 1;
	system("cls");
	DwFrame(17, 43, 10, 31, 6);
	bool stat = true;
	int code = 0;
	int sub = -1;
	int del = -1;
	while (stat)
	{
		ShowCuror();
		int n = gRCount / 7 + 1;
		WriteChar(22, 12, "档案列表", 7);
		WriteChar(29, 12, page, 7);
		WriteChar(30, 12, "/", 7);
		WriteChar(31, 12, n, 7);
		WriteChar(19, 13, "序号", 7);
		WriteChar(23, 13, "档案名称", 7);
		WriteChar(19, 30, "按", 7);
		WriteChar(20, 30, "ESC", 5);
		WriteChar(22, 30, "键返回", 7);
		WriteChar(27, 30, "回车键", 5);
		WriteChar(30, 30, "确认", 7);
		WriteChar(34, 30, "请选择序号:", 7);
		WriteChar(19, 15, "1", 7);
		WriteChar(19, 17, "2", 7);
		WriteChar(19, 19, "3", 7);
		WriteChar(19, 21, "4", 7);
		WriteChar(19, 23, "5", 7);
		WriteChar(19, 25, "6", 7);
		WriteChar(19, 27, "7", 7);
		int tem = 0;
		bool sure = false;

		if (page == 1)
		{
			WriteChar(28, 12, "≮", 4);

		}
		else
		{
			WriteChar(28, 12, "<<", 4);
			if (MousePos.X >= 56 && MousePos.X <= 58 && MousePos.Y == 12)
			{
				for (int i = (page - 1) * 7; i < 7 + (page - 1) * 7; i++)
				{
					WriteChar(23, 15 + tem, "                                 ", 7);
					tem += 2;
				}
				page--;

			}
		}
		if (page == n)
		{
			WriteChar(32, 12, "≯", 4);
		}
		else
		{
			WriteChar(32, 12, ">>", 4);
			if (MousePos.X >= 64 && MousePos.X <= 66 && MousePos.Y == 12)
			{
				for (int i = (page - 1) * 7; i < 7 + (page - 1) * 7; i++)
				{
					WriteChar(23, 15 + tem, "                                 ", 7);
					tem += 2;
				}
				page++;
			}
		}

		int code = MessageListener();
		if (code>=1&&code<=7)
		{
			sub = (page - 1) * 7 + code - 1;
		}
		else if (code == 27)
		{
			stat = false;
		}
		else if (code == 13)
		{
			sure = true;
			stat = false;
		}
		code = 0;
		if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 15)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 0;
			}
			else
			{
				sub = (page - 1) * 7 + 0;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 17)
		{	
			
			
			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 1;
			}
			else
			{
				sub = (page - 1) * 7 + 1;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 19)
		{			

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 2;
			}
			else
			{
				sub = (page - 1) * 7 + 2;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 21)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 3;
			}
			else
			{
				sub = (page - 1) * 7 + 3;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 23)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 +4;
			}
			else
			{
				sub = (page - 1) * 7 + 4;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 25)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 5;
			}
			else
			{
				sub = (page - 1) * 7 + 5;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 25)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 +6;
			}
			else
			{
				sub = (page - 1) * 7 + 6;
			}
		}
		else if (MousePos.X >= 40 && MousePos.X <= 50 && MousePos.Y == 30)
		{
			stat = false;
			MousePos = { 0,0 };
		}
		else if (MousePos.X >= 52 && MousePos.X <= 60 && MousePos.Y == 30)
		{
			sure = true;
			MousePos = { 0,0 };
		}
		else
		{
			sub = -1;
			del = -1;
		}
		if (sure)
		{
			if (del>=0)
			{
				ClearFile(*(gPRecordName + del),1);
				DeleteName(1, del);
				SaveName();
				ReadName();
			
			}else if (sub>=0)
			{
				ReadRecord(*(gPRecordName + sub));
				StartGame(gMode);
				stat = false;
			}
			
		}
					
		for (int i = (page - 1) * 7; i < 7 + (page - 1) * 7; i++)
		{

			if (i < gRCount)
			{
				WriteChar(23, 15 + tem, "                                 ", 9);
				if (i ==sub)
				{
					WriteChar(23, 15 + tem, *(gPRecordName + i), 9);
				}
				else {
					WriteChar(23, 15 + tem, *(gPRecordName+ i), 7);
				}
				if (del ==i)
				{
					WriteChar(34, 15 + tem, "删除", 9);
				}
				else
				{
					WriteChar(34, 15 + tem, "删除", 7);
				}
				

			}
			else
			{
				WriteChar(23, 15 + tem, "                                 ", 9);
			}
			tem += 2;

		}
		
	
	}
	
	system("cls");


}
void MapManage()
{
	SetConsoleTitle("地图管理");

	int page = 1;
	system("cls");
	DwFrame(17, 43, 10, 31, 6);
	bool stat = true;
	int code = 0;
	int  sub = -1;
	int del = -1;
	while (stat)
	{
		int n = gMCount / 7 + 1;
		ShowCuror();
		WriteChar(22, 12, "地图列表", 7);
		WriteChar(29, 12, page, 7);
		WriteChar(30, 12, "/", 7);
		WriteChar(31, 12, n, 7);
		WriteChar(19, 13, "序号", 7);
		WriteChar(23, 13, "地图名称", 7);
		WriteChar(19, 30, "按", 7);
		WriteChar(20, 30, "ESC", 5);
		WriteChar(22, 30, "键返回", 7);
		WriteChar(27, 30, "回车键", 5);
		WriteChar(30, 30, "确认", 7);
		WriteChar(34, 30, "请选择序号:", 7);
		WriteChar(19, 15, "1", 7);
		WriteChar(19, 17, "2", 7);
		WriteChar(19, 19, "3", 7);
		WriteChar(19, 21, "4", 7);
		WriteChar(19, 23, "5", 7);
		WriteChar(19, 25, "6", 7);
		WriteChar(19, 27, "7", 7);
		int tem = 0;
		bool sure = false;
		if (page == 1)
		{
			WriteChar(28, 12, "≮", 4);

		}
		else
		{
			WriteChar(28, 12, "<<", 4);
			if (MousePos.X >= 56 && MousePos.X <= 58 && MousePos.Y == 12)
			{
				for (int i = (page - 1) * 7; i < 7 + (page - 1) * 7; i++)
				{	
					WriteChar(23, 15 + tem, "                                 ", 7);					
					tem += 2;
				}
				page--;

			}
		}
		if (page == n)
		{
			WriteChar(32, 12, "≯", 4);
		}
		else
		{
			WriteChar(32, 12, ">>", 4);
			if (MousePos.X >= 64 && MousePos.X <= 66 && MousePos.Y == 12)
			{
				for (int i = (page - 1) * 7; i < 7 + (page - 1) * 7; i++)
				{
					WriteChar(23, 15 + tem, "                                 ", 7);
					tem += 2;
				}
				page++;
			}
		}


		int code = MessageListener();
		if (code >= 1 && code <= 7)
		{
			sub = (page - 1) * 7 + code - 1;
		}
		else if (code == 27)
		{
			stat = false;
		}
		else if (code == 13)
		{
			sure = true;
			stat = false;
		}
		code = 0;

		if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 15)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 0;
			}
			else
			{
				sub = (page - 1) * 7 + 0;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 17)
		{


			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 1;
			}
			else
			{
				sub = (page - 1) * 7 + 1;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 19)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 2;
			}
			else
			{
				sub = (page - 1) * 7 + 2;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 21)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 3;
			}
			else
			{
				sub = (page - 1) * 7 + 3;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 23)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 4;
			}
			else
			{
				sub = (page - 1) * 7 + 4;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 25)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 5;
			}
			else
			{
				sub = (page - 1) * 7 + 5;
			}
		}
		else if (MousePos.X >= 38 && MousePos.X <= 82 && MousePos.Y == 25)
		{

			if (MousePos.X >= 68)
			{
				del = (page - 1) * 7 + 6;
			}
			else
			{
				sub = (page - 1) * 7 + 6;
			}
		}
		else if (MousePos.X >= 40 && MousePos.X <= 50 && MousePos.Y == 30)
		{
			stat = false;
			MousePos = { 0,0 };
		}
		else if (MousePos.X >= 52 && MousePos.X <= 60 && MousePos.Y == 30)
		{
			sure = true;
			stat = false;
			MousePos = { 0,0 };
		}
		else
		{
			sub = -1;
			del = -1;
		}
		if (sure)
		{
			if (del >= 0)
			{
				ClearFile(*(gPMapName + del), 0);
				DeleteName(0, del);
				SaveName();
				ReadName();
			}
			else if (sub>=0)
			{
				ReadMap(*(gPMapName + sub));
				CopyMap(g_ReadMap, g_InitMap);
			}

		}

		for (int i = (page - 1) * 7; i < 7 + (page - 1) * 7; i++)
		{

			if (i < gMCount)
			{
				WriteChar(23, 15 + tem, "                                 ", 9);
				if (i == sub)
				{
					WriteChar(23, 15 + tem, *(gPMapName + i), 9);
				}
				else {
					WriteChar(23, 15 + tem, *(gPMapName + i), 7);
				}
				if (del == i)
				{
					WriteChar(34, 15 + tem, "删除", 9);
				}
				else
				{
					WriteChar(34, 15 + tem, "删除", 7);
				}
			}
			else
			{
				WriteChar(23, 15 + tem, "                                 ", 9);
			}
			tem += 2;

		}


	}
	system("cls");


}
void CopyMap(int a[][60], int b[][60])
{
	for (int i= 0;i<50;i++)
	{
		for (int j = 0; j < 60; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}
void ClearFile(char* name, int mark)
{
	system("cls");
	char str[30];
	if (mark ==0)
	{
		strcpy_s(str, 30, "data//");
		strcat_s(str, 30, name);
		strcat_s(str, 30, ".map");
	}else if (mark ==1)
	{
		strcpy_s(str, 30, "data//");
		strcat_s(str, 30, name);
		strcat_s(str, 30, ".rec");
	}
	else
	{
		return;
	}
	if (remove(str) ==0)
	{
		printf("删除 成功");
		
	}
	else
	{
		perror("remove");
	}
	system("cls");
	
}
void DeleteName(int mark,int index)
{
	if (mark==0)
	{
		for (int i = 0; i < gMCount-1; i++)
		{
			if (i >= index)
			{
				strcpy_s(*(gPMapName + i), 20, *(gPMapName + i + 1));
			}
		}
		gMCount--;
		gPMapName = (char(*)[20])realloc(gPMapName, gMCount*20 );
		char* p = *(gPMapName + 0);
		char* p1 = *(gPMapName + 1);
		char* p2 = *(gPMapName + 2);
	}
	else if (mark == 1)
	{
		for (int i = 0; i < gRCount - 1; i++)
		{
			if (i >= index)
			{
				strcpy_s(*(gPRecordName + i), 20, *(gPRecordName + i + 1));
			}
		}
		gRCount--;
		gPRecordName = (char(*)[20])realloc(gPRecordName, gRCount*20 );
	}
	
}
