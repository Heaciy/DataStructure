#include "DungeonBuilder.h"

const char TILES[] = " #+IO";

void InitDungeon()
{
    int x, y;
    /* 初始化地牢数组 */
    for (y = 0; y < ROW; y++)
        for (x = 0; x < COL; x++)
        {
            gMap[y][x] = FLOOR;
        }
    /* 修筑外墙，将地牢围起来 */
    for (x = 0; x < COL; x++)
    {
        gMap[0][x] = WALL;
        gMap[ROW - 1][x] = WALL;
    }
    for (y = 0; y < ROW; y++)
    {
        gMap[y][0] = WALL;
        gMap[y][COL - 1] = WALL;
    }
}

void PrintDungeon()
{
    int x, y;
    for (y = 0; y < ROW; y++)
    {
        for (x = 0; x < COL; x++)
            printf("%c", TILES[gMap[y][x]]);
        printf("\n");
    }
}
void BuildDungeon()
{
    BiTree root; //二叉树根节点
    /* 生成二叉树 */
    //创建第一个房间
    CreateBiTree(&root);
    root->data.x = 0;
    root->data.y = 0;
    root->data.width = COL;
    root->data.height = ROW;
    root->data.splitPoint = -1;
    root->data.splitVert = -1;
    //递归拆分房间，生成二叉树
    SplitRoom(root);
    //先序遍历，打印二叉树
    //PreOrderTraverse(root, 0);

    /* 根据二叉树建立地牢 */
    //初始化地牢
    InitDungeon();
    //修建墙体，将较大的房间拆分成小房间
    BuildWalls(root);
    //再墙上开门，使得左右、上下房间联通
    BuildDoors(root);
    //放置地牢的入口和出口
    if (rand() % 2)
    {
        PutStairs(root->lchild, UP_STAIRS);
        PutStairs(root->rchild, DOWN_STAIRS);
    }
    else
    {
        PutStairs(root->lchild, DOWN_STAIRS);
        PutStairs(root->rchild, UP_STAIRS);
    }
    /* 地牢生成完毕，销毁二叉树 */
    //销毁二叉树
    DestroyBiTree(root);
}
/* 实现房间分割 */
void SplitRoom(BiTree root)
{
    int nSplitVert;
    int nSplitPoint;
    TElemType sLeft;
    TElemType sRight;
    /* 判断房间是否还可以继续分割 */
    if (root->data.width >= LIMIT || root->data.height >= LIMIT)
    {
        //决定房间分割的方向
        if (root->data.width < LIMIT)
        {
            nSplitVert = 0;
        }
        else if (root->data.height < LIMIT)
        {
            //当房间高度不够时，修建一堵横着的墙，将房间分割成上下两部分
            nSplitVert = 1;
        }
        else
        {
            //房间足够大时，随机决定墙壁的方向
            nSplitVert = rand() % 2;
        }
        //随机选择一个位置建造墙
        if (nSplitVert) //分成左右两半
        {
            //在data.x和data.width之间随机选择一个位置建墙
            if (root->data.width == LIMIT)
            {
                //最小可分割房间，只能在固定位置建墙
                nSplitPoint = (root->data.x + MIN - 1);
            }
            else
            {
                //空间足够，在任意位置建墙
                nSplitPoint = (root->data.x + MIN - 1) + rand() % (root->data.width - LIMIT);
            }
            //左边的房间
            sLeft.x = root->data.x;
            sLeft.y = root->data.y;
            sLeft.width = nSplitPoint - root->data.x + 1;
            sLeft.height = root->data.height;
            sLeft.splitVert = -1;
            sLeft.splitPoint = -1;
            //右边的房间
            sRight.x = nSplitPoint;
            sRight.y = root->data.y;
            sRight.width = root->data.width - sLeft.width + 1;
            sRight.height = root->data.height;
            sRight.splitVert = -1;
            sRight.splitPoint = -1;
        }
        else //分成上下两半
        {
            //在data.y和data.height之间随机选择一个位置来建墙
            if (root->data.height == LIMIT)
            {
                nSplitPoint = (root->data.y + MIN - 1);
            }
            else
            {
                nSplitPoint = (root->data.y + MIN - 1) + rand() % (root->data.height - LIMIT);
            }
            //上面的房间
            sLeft.x = root->data.x;
            sLeft.y = root->data.y;
            sLeft.width = root->data.width;
            sLeft.height = nSplitPoint - root->data.y + 1;
            sLeft.splitVert = -1;
            sLeft.splitPoint = -1;
            //下面的房间
            sRight.x = root->data.x;
            sRight.y = nSplitPoint;
            sRight.width = root->data.width;
            sRight.height = root->data.height - sLeft.height + 1;
            sRight.splitVert = -1;
            sRight.splitPoint = -1;
        }
        //记录此房间的分割方式
        root->data.splitVert = nSplitVert;
        root->data.splitPoint = nSplitPoint;
        //插入左右孩子节点
        InsertChild(root, 0, sLeft);
        InsertChild(root, 1, sRight);
        //继续分割房间
        SplitRoom(root->lchild);
        SplitRoom(root->rchild);
    }
}
/* 建造墙壁 */
void BuildWalls(BiTree root)
{
    int x, y;
    //判断因该建立纵向的墙还是横向的墙
    if (!BiTreeEmpty(root))
    {
        if (root->data.splitVert)
        {
            x = root->data.splitPoint; //建墙的位置
            for (y = root->data.y; y < root->data.y + root->data.height; y++)
                gMap[y][x] = WALL;
        }
        else
        {
            y = root->data.splitPoint;
            for (x = root->data.x; x < root->data.x + root->data.width; x++)
                gMap[y][x] = WALL;
        }
        BuildWalls(root->lchild);
        BuildWalls(root->rchild);
    }
}
/* 在墙壁上开门 */
void BuildDoors(BiTree root)
{
    int x, y;
    Point points[MAX];
    int pointCount = 0;
    int selection;
    if (!BiTreeEmpty(root))
    {
        if (root->data.splitVert)
        {
            x = root->data.splitPoint;
            for (y = root->data.y; y < root->data.y + root->data.height; y++)
            {
                if ((gMap[y][x + 1] == FLOOR) && (gMap[y][x - 1] == FLOOR) && y != 0 && y != ROW - 1)
                {
                    points[pointCount].x = x;
                    points[pointCount].y = y;
                    pointCount++;
                }
            }
        }
        else
        {
            y = root->data.splitPoint;
            for (x = root->data.x; x < root->data.x + root->data.width; x++)
            {
                if (gMap[y + 1][x] == FLOOR && gMap[y - 1][x] == FLOOR && x != 0 && x != COL - 1)
                {
                    points[pointCount].x = x;
                    points[pointCount].y = y;
                    pointCount++;
                }
            }
        }
        //随机选择一个位置打通墙壁换上门
        selection = rand() % pointCount;
        gMap[points[selection].y][points[selection].x] = DOOR;
        //继续递归左右子树
        BuildDoors(root->lchild);
        BuildDoors(root->rchild);
    }
}
/* 放置楼梯 */
void PutStairs(BiTree root, int stairs)
{
    int x, y;
    BiTreeNode **pLeaves;
    int count;
    int index;
    TElemType room;
    count = GetLeaves(root->lchild, &pLeaves);
    index = rand() % count;
    room = pLeaves[index]->data;
    x = room.x + 1 + rand() % (room.width - 2);
    y = room.y + 1 + rand() % (room.height - 2);
    gMap[y][x] = stairs;
    free(pLeaves);
}
