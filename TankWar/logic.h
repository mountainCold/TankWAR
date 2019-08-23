#pragma once
#include "data.h"
#define KEYDOWN(vk_code)((GetAsyncKeyState(vk_code)&0x8000)?1:0)
/*
���� �з�̹������ƶ�
���� �з�̹�� �ƶ����
*/
void AutoMoveForOPPTank(Tank& tank,int nT);
/*
���� ̹���ƶ���� ̹�˲�������⣬������̹�������ƶ�
���� ̹��
����ֵ 0���������ƶ� 1�����ϰ���
*/
int TankMoveDetection(Tank& tank);
/*�ӵ���ײ���
���� �ж��ӵ��Ƿ������ϰ��� ��������Ӧ����Ӧ
����ֵ 0�ӵ��������� 1�ӵ���ʧ
*/
int BulletCollisionDetection(Bullet bullet);
/*
�����߼��ж�
*/
void OpCodeDetection(Tank& tank, char ch);
/*
��Ϸʱ��˵��������
*/
void GameShows();
/*��ʼ��Ϸ
���� ��Ϸ����ҳ���߼�
���� ������Ϸ
*/
void StartGame(int x);
/*�༭��ͼ
���� �Զ���༭��ͼ
���� ��Ҫ�༭�ĵ�ͼ
*/
void EditMap();
/*
�¼�������
*/
int MessageListener (int x =0);
/*
�ఴ������ 
*/
void KeyListener(char& ch1,char& ch2, char& bch1, char& bch2);
/*
����������
*/
int KeyListener();
/*���*/
void OpenFire(Tank& tank, char ch);
/*
���ع��
*/
void ShowCuror();
/*
���ܣ�ɾ������ָ���е�ĳһԪ��
������mark 0��ʾgPMapName 1��ʾ gPRecordName
	 Ԫ���±�
*/
void DeleteName(int mark,int index);
/*
���� ɾ���ļ� 
���� �ļ���  �ͱ�־�� 0��ʾgPMapName 1��ʾ gPRecordName
*/
void ClearFile(char* name, int mark);
/*
�����ͼ
*/
void SaveMap();

/*
��ȡ��ͼ
���� ��ͼ����
*/
void ReadMap(char* mName);
/*
�����ͼ
*/
void SaveRecord();
/*
��ͼ����
���� ���ڶ�����ͼ��Ϣ��������һ����ͼ��
*/
void CopyMap(int a[][60], int b[][60]);
/*
��ȡ��ͼ
���� ��ͼ����
*/
void ReadRecord(char* mName);
/*
��������
*/
void RecordManage();
/*
������
���� �ĸ��������
*/
void DwFrame(int x1, int x2, int y1, int y2, int n);
/*
��������
����  pst ��Ҫ�����������  int n ��ʶ�� �����ǵ�ͼ��0�����Ǵ浵��1��
*/
void SaveName(char* pst, int n);
void SaveName();
/*
��ȡ����
*/
void ReadName();
/*��ͼ����
*/
void MapManage();