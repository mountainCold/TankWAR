#pragma once
#include "data.h"
/*
���ܣ� ��������ַ�����ָ����λ�ô�ӡ����
������ 
int x ��int y λ�� ����
const char* str ��Ҫ��ӡ���ַ���
*/
void WriteChar(int x, int y, const char* str, WORD color = 7);
void WriteChar(int x, int y, int heath, WORD color = 7);
/*
���ܣ���ӡһ��̹��
������Tank ̹�˽ṹ��
*/
void WriteTank(Tank &tank);
/*
���ܣ���ӡһ��̹��
������̹�����ĵ�
*/
void WriteTank(int x, int y,int color);
/*
���� ���̹���ƶ��ۼ�
*/
void ClearTank(Tank tank);
/*
���� �����ǰ���̹��
*/
void DelTank(Tank tank);
/*
* ��������ַ�����ָ����λ�ô�ӡ����
*/
int WriteFood(int x,int y);
/*
���� ��ӡ�ӵ�
���� �ӵ�����̹��
����ֵ 0 �ӵ��������� 1�ӵ���ʧ
*/
int WriteBullet(Bullet* bul);
/*
���� �������ǰλ�õ��ӵ�
*/
void ClearBullet(Bullet bullet);
/*��¼��ͼ
���� ���Ʊ߽� �ͻ���
*/
void WriteMap();
/*���ƴ��༭��ͼ
*/
void WriteEditMap();
/*��ʼ�����༭��ͼ
*/
void InitMap(/*int Map[][60]*/);

/*���Ʒ���
���� ���ƻ�ӭ/��������
*/
void HomePage();
