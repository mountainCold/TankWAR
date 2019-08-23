#include "draw.h"
#include <stdio.h>
#include "logic.h"
#include <time.h>
void WriteChar(int x, int y, const char* str, WORD color )
{
	if (x<0||y<0||x>70||y>50)
	{
		return;
	}
	COORD pos = { 2 * x,y };
	SetConsoleTextAttribute(g_hout, color);
	SetConsoleCursorPosition(g_hout, pos);
	printf(str);
	SetConsoleTextAttribute(g_hout, 7);
}
void WriteChar(int x, int y, int heath, WORD color)
{
	if (x < 0 || y < 0 || x>70 || y>50)
	{
		return;
	}
	COORD pos = { 2 * x,y };
	SetConsoleTextAttribute(g_hout, color);
	SetConsoleCursorPosition(g_hout, pos);
	printf("%d",heath);
	SetConsoleTextAttribute(g_hout, 7);
}
void WriteTank(Tank &tank)
{
	if (tank.heart<=0)
	{
		return;
	}
	int x = tank.x;
	int y = tank.y;
	int color = tank.Tsign;
	for (int i = x - 1; i < x + 2; i++)
		{
			for (int j = y - 1; j < y + 2; j++)
			{
				if (Map[j][i] < 30)
				{
					Map[j][i] = tank.Tsign;
				}
			
			}
		}

	switch (tank.dir)
		{
		case 'w':
		{		
			tank.bul.x = x;
			tank.bul.y = y - 1;
			if (Map[y - 1][x-1]<30)
			{
				WriteChar(x - 1, y - 1, "  ", color);
			}
			if (Map[y - 1][x + 1] < 30)
			{
				WriteChar(x + 1, y - 1, "  ", color);
			}
			if (Map[y - 1][x ] < 30)
			{
				WriteChar(x, y - 1, "��", color);
			}
			if (Map[y ][x ] < 30)
			{
				WriteChar(x, y, "��");
			}
			if (Map[y ][x - 1] < 30)
			{
				WriteChar(x - 1, y, "��", color);
			}
			if (Map[y ][x + 1] < 30)
			{
				WriteChar(x + 1, y, "��", color);
			}
			if (Map[y + 1][x - 1] < 30)
			{
				WriteChar(x - 1, y + 1, "��", color);
			}
			if (Map[y + 1][x + 1] < 30)
			{
				WriteChar(x + 1, y + 1, "��", color);
			}
			if (Map[y + 1][x ] < 30)
			{
				WriteChar(x, y + 1, "  ", color);
			}

		}break;
		case 's':
		{
			
			tank.bul.x = x;
			tank.bul.y = y + 1;
			

			if (Map[y + 1][x - 1] < 30)
			{
				WriteChar(x - 1, y + 1, "  ", color);
			}
			if (Map[y + 1][x + 1] < 30)
			{
				WriteChar(x + 1, y +1, "  ", color);
			}
			if (Map[y + 1][x] < 30)
			{
				WriteChar(x, y+ 1, "��", color);
			}
			if (Map[y][x] < 30)
			{
				WriteChar(x, y, "��");
			}
			if (Map[y][x - 1] < 30)
			{
				WriteChar(x - 1, y, "��", color);
			}
			if (Map[y][x + 1] < 30)
			{
				WriteChar(x + 1, y, "��", color);
			}
			if (Map[y - 1][x - 1] < 30)
			{
				WriteChar(x - 1, y- 1, "��", color);
			}
			if (Map[y - 1][x + 1] < 30)
			{
				WriteChar(x + 1, y -1, "��", color);
			}
			if (Map[y- 1][x] < 30)
			{
				WriteChar(x, y- 1, "  ", color);
			}

		}break;
		case 'a':
		{
			
			tank.bul.x = x - 1;
			tank.bul.y = y;
			
			if (Map[y + 1][x - 1] < 30)
			{
				WriteChar(x - 1, y + 1, "  ", color);
			}
			if (Map[y - 1][x - 1] < 30)
			{
				WriteChar(x - 1, y - 1, "  ", color);
			}
			if (Map[y ][x-1] < 30)
			{
				WriteChar(x-1, y , "��", color);
			}
			if (Map[y][x] < 30)
			{
				WriteChar(x, y, "��");
			}
			if (Map[y+1][x ] < 30)
			{
				WriteChar(x , y+1, "��", color);
			}
			if (Map[y-1][x] < 30)
			{
				WriteChar(x, y-1, "��", color);
			}
			if (Map[y + 1][x + 1] < 30)
			{
				WriteChar(x + 1, y + 1, "��", color);
			}
			if (Map[y - 1][x + 1] < 30)
			{
				WriteChar(x + 1, y - 1, "��", color);
			}
			if (Map[y ][x+1] < 30)
			{
				WriteChar(x+1, y , "  ", color);
			}
	

		}break;
		case 'd':
		{
			
			tank.bul.x = x + 1;
			tank.bul.y = y;
			
			if (Map[y + 1][x + 1] < 30)
			{
				WriteChar(x + 1, y + 1, "  ", color);
			}
			if (Map[y - 1][x + 1] < 30)
			{
				WriteChar(x + 1, y - 1, "  ", color);
			}
			if (Map[y][x + 1] < 30)
			{
				WriteChar(x + 1, y, "��", color);
			}
			if (Map[y][x] < 30)
			{
				WriteChar(x, y, "��");
			}
			if (Map[y + 1][x] < 30)
			{
				WriteChar(x, y + 1, "��", color);
			}
			if (Map[y - 1][x] < 30)
			{
				WriteChar(x, y - 1, "��", color);
			}
			if (Map[y + 1][x - 1] < 30)
			{
				WriteChar(x - 1, y + 1, "��", color);
			}
			if (Map[y - 1][x - 1] < 30)
			{
				WriteChar(x - 1, y - 1, "��", color);
			}
			if (Map[y][x - 1] < 30)
			{
				WriteChar(x - 1, y, "  ", color);
			}

		}break;
		default:
			break;
		}
	tank.bul.dir = tank.dir;

}
void WriteTank(int x, int y,int color)
{
	WriteChar(x - 1, y - 1, "  ", color);
	WriteChar(x + 1, y - 1, "  ", color);
	WriteChar(x, y - 1, "��", color);
	WriteChar(x, y, "��");
	WriteChar(x - 1, y, "��", color);
	WriteChar(x + 1, y, "��", color);
	WriteChar(x - 1, y + 1, "��", color);
	WriteChar(x + 1, y + 1, "��", color);
	WriteChar(x, y + 1, "  ", color);
}
void ClearTank(Tank tank)
{
	int x = tank.x;
	int y = tank.y;
	int color = 0;
	switch (tank.dir)
		{
		case 'w':
		{

			// 		WriteChar(x, y - 1, "  ", color);
			// 		WriteChar(x, y, "  ");
			// 		WriteChar(x - 1, y, "  ", color);
			//		WriteChar(x + 1, y, "  ", color);
		if (Map[y + 2][x - 1] <30)
		{
			Map[y + 2][x - 1] = 0;
			WriteChar(x - 1, y + 2, "  ", color);
		}
		else
		{
			Map[y + 2][x - 1] = �ݴ�;
		}
		if (Map[y + 2][x + 1] <30)
		{
			Map[y + 2][x + 1] = 0;
			WriteChar(x + 1, y + 2, "  ", color);
		}
		else
		{
			Map[y + 2][x + 1] = �ݴ�;
		}
		if (Map[y + 2][x] < 30)
		{
			Map[y + 2][x] = 0;
			WriteChar(x, y + 2, "  ", color);
		}
		else
		{
			Map[y + 2][x] = �ݴ�;

		}
				

		}break;
		case 'a':
		{
			// 		WriteChar(x, y + 1, "  ", color);
			// 		WriteChar(x, y, "  ");
			// 		WriteChar(x - 1, y, "  ", color);
			// 		WriteChar(x + 1, y, "  ", color);
			if (Map[y - 1][x + 2] < 30)
			{
				Map[y - 1][x + 2] = 0;
				WriteChar(x + 2, y -1, "  ", color);
			}
			else
			{
				Map[y -1][x + 2] = �ݴ�;
			}
			if (Map[y +1][x + 2] < 30)
			{
				Map[y + 1][x + 2] = 0;
				WriteChar(x + 2, y+1, "  ", color);
			}
			else
			{
				Map[y +1][x + 2] = �ݴ�;
			}
			if (Map[y ][x + 2] < 30)
			{
				Map[y][x + 2] = 0;
				WriteChar(x+2, y, "  ", color);
			}
			else
			{
				Map[y ][x + 2] = �ݴ�;

			}
						
		}break;
		case 's':
		{
			// 		WriteChar(x - 1, y, "  ", color);
			// 		WriteChar(x, y, "  ");
			// 		WriteChar(x, y - 1, "  ", color);
			// 		WriteChar(x, y + 1, "  ", color);
			if (Map[y - 2][x - 1] < 30)
			{
				Map[y - 2][x - 1] = 0;
				WriteChar(x - 1, y - 2, "  ", color);
			}
			else
			{
				Map[y - 2][x - 1] = �ݴ�;
			}
			if (Map[y - 2][x + 1] < 30)
			{
				Map[y - 2][x+1] = 0;
				WriteChar(x + 1, y - 2, "  ", color);
			}
			else
			{
				Map[y - 2][x + 1] = �ݴ�;
			}
			if (Map[y - 2][x] < 30)
			{
				Map[y - 2][x] = 0;
				WriteChar(x, y - 2, "  ", color);
			}
			else
			{
				Map[y - 2][x] = �ݴ�;

			}
			
		}break;
		case 'd':
		{
			// 		WriteChar(x + 1, y, "  ", color);
			// 		WriteChar(x, y, "  ");
			// 		WriteChar(x, y - 1, "  ", color);
			// 		WriteChar(x, y + 1, "  ", color);
			if (Map[y - 1][x - 2] < 30)
			{
				Map[y - 1][x - 2] = 0;
				WriteChar(x - 2, y - 1, "  ", color);
			}
			else
			{
				Map[y - 1][x - 2] = �ݴ�;
			}
			if (Map[y + 1][x - 2] < 30)
			{
				Map[y + 1][x - 2] = 0;
				WriteChar(x - 2, y + 1, "  ", color);
			}
			else
			{
				Map[y + 1][x - 2] = �ݴ�;
			}
			if (Map[y][x - 2] < 30)
			{
				Map[y ][x - 2] = 0;
				WriteChar(x - 2, y, "  ", color);
			}
			else
			{
				Map[y][x - 2] = �ݴ�;

			}
		
		}break;
		}
	
}
void DelTank(Tank tank)
{
	for (int i=tank.x-1;i<tank.x+2;i++)
	{
		for (int j = tank.y - 1; j < tank.y + 2; j++)
		{
			if (Map[j][i]>=30)
			{
				Map[j][i] = �ݴ�;
			}
			else
			{
				WriteChar(i, j, "  ");
				Map[j][i] = 0;
			}
			
		}
	}

}
int WriteFood(int x,int y)
{

	if (Map[y][x] ==0)
	{
		WriteChar(x, y, "��",9);
		Map[y][x] = 9;
		return 1;
	}
	return 0;
}
int WriteBullet(Bullet* Bul)
{	
	if (Bul->x > 58 || Bul->x < 1 || Bul->y > 48 || Bul->y < 1)
	{
		return 1;
	}	
	ClearBullet(*Bul);	
	switch (Bul->dir)
	{
	case 'w':
	{
		--Bul->y;
	}break;
	case 's':
	{
		++Bul->y;
	}break;
	case 'a':
	{
		--Bul->x;
	
	}break;
	case 'd':
	{
		++Bul->x;	
	}break;
	default:
		break;
	}
	int bnum = BulletCollisionDetection(*Bul);
	if (bnum==1)
	{		
		return 1;
	}if (bnum == �ݴ�)
	{
		return 0;
	}
	WriteChar(Bul->x, Bul->y, Bul->v);
	Map[Bul->y][Bul->x] = Bul->Bsign;
	return 0;
}
void ClearBullet(Bullet bullet)
{
	if (Map[bullet.y][bullet.x] < 30 && Map[bullet.y][bullet.x] != ʳ��)
	{
		WriteChar(bullet.x, bullet.y, "  ");
		Map[bullet.y][bullet.x] = 0;
	}
	else if (Map[bullet.y][bullet.x]  == ʳ��)
	{
		Map[bullet.y][bullet.x] = ʳ��;
	}
	else
	{
		Map[bullet.y][bullet.x] = �ݴ�;
	}

}
void WriteMap()
{
	//���߽�
	for (int i = 59; i < 70; i++)
	{
		for (int j = 0; j < 50; j++)
		{	
			if (i == 59 || i == 69 || j == 0 || j == 49)
			{
				WriteChar(i, j, "��");
			}
		}
	}	
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (Map[j][i] == ��ǽ)
			{
				WriteChar(i, j, "��",7);
			}
			if (Map[j][i] == ��ǽ)
			{
				WriteChar(i, j, "��",6);
			}
			if (Map[j][i] >= �ݴ�)
			{
				WriteChar(i, j, "��",5);
			}
			if (Map[j][i] == ����)
			{
				WriteChar(i, j, "��",9);
			}
		}
	}	
}
void WriteEditMap()
{
	//���߽�
	for (int i = 59; i < 70; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 59 || i == 69 || j == 0 || j == 49)
			{
				WriteChar(i, j, "��");
			}
		}
	}
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (g_EditMap[j][i] == ��ǽ)
			{
				WriteChar(i, j, "��", 7);
			}
			if (g_EditMap[j][i] == ��ǽ)
			{
				WriteChar(i, j, "��", 6);
			}
			if (g_EditMap[j][i] >= �ݴ�)
			{
				WriteChar(i, j, "��", 5);
			}
			if (g_EditMap[j][i] == ����)
			{
				WriteChar(i, j, "��", 9);
			}
		}
	}
}
void InitMap()
{
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (i == 0 || i == 59 || j == 0 || j == 49)
			{
				g_EditMap[j][i] = ��ǽ;
			}
		}
	}
	for (int j = 46; j < 49; j++)
	{
		for (int i = 28; i < 32; i++)
		{
			if (i > 28 && i < 31 && j>46 && j <= 48)
			{
				g_EditMap[j][i] = ����;
			}
 			else
 			{
 				//g_EditMap[j][i] = ��ǽ;
 				g_EditMap[j][i] = ��ǽ;
			}
		}
	}


}

void HomePage()
{
	for (int i=0;i<70;i+=4)
	{
		for (int j=0;j<50;j++)
		{
			if (i>23&&i<43&&j>15&&j<35)
			{
			}
			else
			{
				if (j%4==0)
				{
					WriteChar(i, j, "̹",70);
				}if (j%4==1)
				{
					WriteChar(i, j, "��",61);
				}if (j%4==2)
				{
					WriteChar(i, j, "��",82);
				}if (j%4==3)
				{
					WriteChar(i, j, "ս",53);
				}
			}
		}
	}
}