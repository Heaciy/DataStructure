#ifndef MAP_DUNGEONBUILDER_H
#define MAP_DUNGEONBUILDER_H

#include "BiTree.h"

#define COL 15
#define ROW 15
#define MAX COL > ROW ? COL : ROW //��ͼ������
/* ��С�������С�ɷָ��ı��� */
#define MIN 5
#define LIMIT (2 * MIN - 1)
int gMap[ROW][COL];
/* ��ͼԪ�� */
#define FLOOR 0
#define WALL 1
#define DOOR 2
#define UP_STAIRS 3   //���
#define DOWN_STAIRS 4 //����

/* ����� */
typedef struct Point
{
    int x, y;
} Point;

void BuildDungeon();                     //������³�(����)��ʹ�ö��ֿռ䷨���ݹ����ɶ�����
void SplitRoom(BiTree room);             //ʹ�ö��ֿռ�ָ���ݹ����ɶ�����
void InitDungeon();                      //��ʼ������
void BuildWalls(BiTree root);            //���ݶ���������ǽ��
void BuildDoors(BiTree root);            //���ݶ������������ǽ�Ͽ���
void PutStairs(BiTree root, int stairs); //���õ��³ǵ�̨��(�����)
void PrintDungeon();                     //��ʾ���³�


#endif //MAP_DUNGEONBUILDER_H
