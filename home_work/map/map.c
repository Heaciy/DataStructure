#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

/* 定义地图相关元素 */
/* 地图的尺寸 */
#define COL 15
#define ROW 15
// const int COL = 15;
// const int ROW = 15;
#define MAX COL > ROW ? COL : ROW //地图最大边数

/* 最小房间和最小可分割房间的边数 */
#define MIN 5
#define LIMIT (2 * MIN - 1)
// const int MIN = 5;
// const int LIMIT = (2 * MIN - 1);

/* 其他元素 */
#define FLOOR 0
#define WALL 1
#define DOOR 2
#define UP_STAIRS 3   //入口
#define DOWN_STAIRS 4 //出口

const char TILES[] = " #+IO";

/* 定义点 */
typedef struct Point
{
    int x, y;
} Point;

/* 定义地牢房间 */
typedef struct TElemType
{
    int x;
    int y;
    int width;
    int height;
    int splitPoint;
    int splitVert;
} TElemType;

/* 定义二叉树 */
struct BiTreeNode
{
    TElemType data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
};

typedef struct BiTreeNode *BiTree, BiTreeNode;

/* bitree.h */
int CreateBiTree(BiTree *T);                    //创建二叉树
int DestroyBiTree(BiTree T);                    //销毁二叉树
int BiTreeEmpty(BiTree T);                      //判断二叉树是否为空(如果是则是一个叶子节点)
int BiTreeHeight(BiTree T);                     //返回树的深度
int CountLeaf(BiTree T);                        //返回叶子结点的数目
int GetLeaves(BiTree T, BiTreeNode ***pLeaves);  //获得所有叶子节点，返回叶子节点数
int InsertChild(BiTree T, int lr, TElemType e); //先序遍历二叉树，打印树的结构
int PreOrderTraverse(BiTree T, int depth);
/* DungeonBuilder.h */
void BuildDungeon();                     //建造地下城(地牢)，使用二分空间法，递归生成二叉树
void SplitRoom(BiTree room);             //使用二分空间分割法，递归生成二叉树
void InitDungeon();                      //初始化地牢
void BuildWalls(BiTree root);            //根据二叉树建立墙壁
void BuildDoors(BiTree root);            //根据二叉树，随机在墙上开门
void PutStairs(BiTree root, int stairs); //放置地下城的台阶(出入口)
void PrintDungeon();                     //显示地下城

/* BiTree.cpp */
int CreateBiTree(BiTree *T)
{
    *T = (BiTree)malloc(sizeof(struct BiTreeNode));
    if (*T == NULL)
    {
        printf("内存分配失败\n");
        exit(-1);
    }
    (*T)->lchild = NULL;
    (*T)->rchild = NULL;
    return 1;
}
int DestroyBiTree(BiTree T)
{
    if (T->lchild != NULL)
        DestroyBiTree(T->lchild);
    if (T->rchild != NULL)
        DestroyBiTree(T->rchild);
    free(T);
    T = NULL;
    return 1;
}
int BiTreeEmpty(BiTree T) //判断二叉树是否为空，如果为空则是"叶子节点"
{
    if (T->lchild == NULL && T->rchild == NULL)
        return 1;
    else
        return 0;
}
int BiTreeHeight(BiTree T)
{
    int h1, h2;
    if (T == NULL)
        return 0;
    h1 = BiTreeHeight(T->rchild);
    h2 = BiTreeHeight(T->rchild);
    if (h1 > h2)
        return h1 + 1;
    else
        return h2 + 1;
}
int CountLeaf(BiTree T)
{
    if (T == NULL)
        return 0;
    else if (BiTreeEmpty(T))
        return 1;
    else
        return CountLeaf(T->lchild) + CountLeaf(T->rchild);
    return 0;
}
int InsertChild(BiTree T, int lr, TElemType e)
{
    BiTreeNode *temp;
    if (T == NULL)
    {
        printf("父节点不能为空！\n");
        return 0;
    }
    temp = (BiTreeNode *)malloc(sizeof(struct BiTreeNode));
    if (temp == NULL)
    {
        printf("内存分配失败!\n");
        return 0;
    }
    else
    {
        temp->data = e;
        temp->lchild = NULL;
        temp->rchild = NULL;
    }
    //lr如果为0插入左子树，如果为1插入右子树
    if (lr == 0)
    {
        if (T->lchild != NULL)
            DestroyBiTree(T->lchild);
        T->lchild = temp;
    }
    else
    {
        if (T->rchild != NULL)
            DestroyBiTree(T->rchild);
        T->rchild = temp;
    }
    return 1;
}
int GetLeaves(BiTree T, BiTreeNode ***pLeaves)
{
    BiTreeNode **leaves; //定义叶子节点数组
    int count;           //叶子节点总数
    int index = 0;
    BiTreeNode **stack1; //保存节点
    int *stack2;         //保存状态，与stack1共用一个栈顶指针
    int height;          //树的高度
    int top;             //栈顶指针
    int tag;             //访问状态标记
    BiTreeNode *pCur;    //临时节点，用于记录当前节点的指针
    if (T == NULL)
    {
        printf("节点为空！\n");
        return 0;
    }
    count = CountLeaf(T); //叶子节点数组，长度与叶子节点数量相同
    printf("count: %d\n",count);
    leaves = (BiTreeNode **)malloc(sizeof(BiTreeNode *) * count);
    height = BiTreeHeight(T); //栈的最大深度与树的深度一致
    stack1 = (BiTreeNode **)malloc(sizeof(BiTreeNode *) * (height + 1));
    stack2 = (int *)malloc(sizeof(int) * (height + 1));
    /* 后序遍历二叉树 */
    pCur = T;  //记录根节点
    index = 0; //节点数组下表初始为0
    top = 0;   //栈顶指针初始为0
    tag = 1;   //循环标识，初始为1，遍历结束后为0
    do
    {
        while (pCur != NULL)
        {
            stack1[++top] = pCur; //当前节点入栈
            stack2[top] = 0;      //标识设置为0，标识“左子树准备进栈”
            pCur = pCur->lchild;
        }             //左子树为NULL停止入栈
        if (top == 0) //若为0说明已经访问到根节点
            tag = 0;  //停止遍历
        else if (stack2[top] == 0)
        {
            pCur = stack1[top]->rchild; //当前节点移到右子树
            stack2[top] = 1;            //状态设置为1，标识“右子树准备进栈”
        }
        else //左右子树均已访问
        {
            pCur = stack1[top]; //弹栈
            top--;
            if (BiTreeEmpty(pCur))
                leaves[index++] = pCur;
            pCur = NULL;
        }

    } while (tag != 0);
    free(stack1);
    free(stack2);
    pLeaves = &leaves;
    return count;
}

int PreOrderTraverse(BiTree T, int depth)
{
    int i;
    if (T == NULL)
        return -1;
    /* 访问节点，打印当前房间的结构 */
    for (i = 0; i < depth; i++)
        printf(" ");
    printf("Room[x=%d,y=%d,width=%d,height=%d,splitVert=%d,splitPint=%d]\n", T->data.x, T->data.y, T->data.width, T->data.height, T->data.splitVert, T->data.splitPoint);
    /* 继续访问子节点 */
    if (T->lchild != NULL)
        PreOrderTraverse(T->lchild, depth + 1);
    if (T->rchild != NULL)
        PreOrderTraverse(T->rchild, depth + 1);
    return 1;
}

/* 处理地图 */
// int gMap[ROW][COL];
int gMap[15][15];
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
    PreOrderTraverse(root, 0);
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
    printf("count: %d\n",count);
    index = rand() % count;
    printf("index: %d\n",index);
    room = pLeaves[index]->data;
    x = room.x + 1 + rand() % (room.width - 2);
    y = room.y + 1 + rand() % (room.height - 2);
    gMap[y][x] = stairs;
    free(pLeaves);
}

int main(void)
{
    char c;
    srand((unsigned)time(NULL));
    do
    {
        printf("===地图生成器===\n");
        //建造地牢
        BuildDungeon();
        //显示地牢
        PrintDungeon();
        printf("输入q结束程序：");
        scanf("%c", &c);
        printf("\n");
    } while (c != 'q');
    return 0;
}
//总结树结构的特点