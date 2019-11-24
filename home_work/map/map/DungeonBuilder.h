#ifndef MAP_DUNGEONBUILDER_H
#define MAP_DUNGEONBUILDER_H

#include "BiTree.h"

#define COL 15
#define ROW 15
#define MAX COL > ROW ? COL : ROW //地图最大边数
/* 最小房间和最小可分割房间的边数 */
#define MIN 5
#define LIMIT (2 * MIN - 1)
int gMap[ROW][COL];
/* 地图元素 */
#define FLOOR 0
#define WALL 1
#define DOOR 2
#define UP_STAIRS 3   //入口
#define DOWN_STAIRS 4 //出口

/* 定义点 */
typedef struct Point
{
    int x, y;
} Point;

void BuildDungeon();                     //建造地下城(地牢)，使用二分空间法，递归生成二叉树
void SplitRoom(BiTree room);             //使用二分空间分割法，递归生成二叉树
void InitDungeon();                      //初始化地牢
void BuildWalls(BiTree root);            //根据二叉树建立墙壁
void BuildDoors(BiTree root);            //根据二叉树，随机在墙上开门
void PutStairs(BiTree root, int stairs); //放置地下城的台阶(出入口)
void PrintDungeon();                     //显示地下城


#endif //MAP_DUNGEONBUILDER_H
