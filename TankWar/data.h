#include <Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std; 
#pragma once
#define  �յ� 0
#define  ��ǽ 1
#define  ��ǽ 2
#define  �ݴ� 30
#define  ���� 10
#define  ʳ�� 9
#define  �ҷ�̹��1 4
#define  �ҷ�̹��2 5
#define  �з�̹��1 6
#define  �з�̹��2 7
#define  �з�̹��3 8
#define  �ҷ��ӵ�1 14
#define  �ҷ��ӵ�2 15
#define  �з��ӵ�1 16
#define  �з��ӵ�2 17
#define  �з��ӵ�3 18
extern HANDLE g_hout ; //������
extern HANDLE g_hint ;  //������
extern int Map[50][60]; //��ͼ��Ϣ
extern int g_InitMap[50][60]; //����ȡ��ͼ
extern int g_EditMap[50][60]; //���༭��ͼ
extern int g_ReadMap[50][60]; //��Ϸ�����ͼ
extern bool g_Game;
extern COORD MousePos;
extern int gLevel;//��ǰ�ؿ���
extern int gContinue;//������Ϸ
extern int gMode;//��Ϸģʽ����or˫��
extern int gMCount;//Map �����ļ�����
extern int gRCount;//Record �����ļ�����
extern char (*gPMapName)[20];//��ͼ������������

extern char (*gPRecordName)[20];//�浵������������
typedef struct BULLET
{
	char dir; //�ӵ��ķ���
	int grade=1;//�ӵ���ǿ��
	int Bsign; //�ӵ��ı�־����14,15Ϊ�����ӵ���16,17,18Ϊ�з��ӵ�
	int x=0; //�ӵ�λ������
	int y=0;//�ӵ�λ������
	const char* v = "��"; //�ӵ�����״
}Bullet;
typedef struct TANK
{
	char dir; //̹�˵ĳ���
	int heart; //̹�˵�����ֵ
	int Tsign; //̹�˱�־����4,5Ϊ����̹�ˣ�6,7,8Ϊ�з�̹��
	int bulletStat; // �ӵ�״̬ ��0��ʾ�Ѿ����� 1���Է���
	int x;  //��ʾ̹������λ�õĺ�����
	int y; //��ʾ̹������λ�õ�������
	Bullet bul; //�ӵ�
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
���ܣ�����̹��
������ 4,5,6,7,8�ֱ��ʾ���켺��1,2�ţ��з�1.2.3��̹��
*/
Tank MakeTank(int x,int heart=3);