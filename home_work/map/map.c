#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

/* �����ͼ���Ԫ�� */
/* ��ͼ�ĳߴ� */
#define COL 15
#define ROW 15
// const int COL = 15;
// const int ROW = 15;
#define MAX COL > ROW ? COL : ROW //��ͼ������

/* ��С�������С�ɷָ��ı��� */
#define MIN 5
#define LIMIT (2 * MIN - 1)
// const int MIN = 5;
// const int LIMIT = (2 * MIN - 1);

/* ����Ԫ�� */
#define FLOOR 0
#define WALL 1
#define DOOR 2
#define UP_STAIRS 3   //���
#define DOWN_STAIRS 4 //����

const char TILES[] = " #+IO";

/* ����� */
typedef struct Point
{
    int x, y;
} Point;

/* ������η��� */
typedef struct TElemType
{
    int x;
    int y;
    int width;
    int height;
    int splitPoint;
    int splitVert;
} TElemType;

/* ��������� */
struct BiTreeNode
{
    TElemType data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
};

typedef struct BiTreeNode *BiTree, BiTreeNode;

/* bitree.h */
int CreateBiTree(BiTree *T);                    //����������
int DestroyBiTree(BiTree T);                    //���ٶ�����
int BiTreeEmpty(BiTree T);                      //�ж϶������Ƿ�Ϊ��(���������һ��Ҷ�ӽڵ�)
int BiTreeHeight(BiTree T);                     //�����������
int CountLeaf(BiTree T);                        //����Ҷ�ӽ�����Ŀ
int GetLeaves(BiTree T, BiTreeNode ***pLeaves);  //�������Ҷ�ӽڵ㣬����Ҷ�ӽڵ���
int InsertChild(BiTree T, int lr, TElemType e); //�����������������ӡ���Ľṹ
int PreOrderTraverse(BiTree T, int depth);
/* DungeonBuilder.h */
void BuildDungeon();                     //������³�(����)��ʹ�ö��ֿռ䷨���ݹ����ɶ�����
void SplitRoom(BiTree room);             //ʹ�ö��ֿռ�ָ���ݹ����ɶ�����
void InitDungeon();                      //��ʼ������
void BuildWalls(BiTree root);            //���ݶ���������ǽ��
void BuildDoors(BiTree root);            //���ݶ������������ǽ�Ͽ���
void PutStairs(BiTree root, int stairs); //���õ��³ǵ�̨��(�����)
void PrintDungeon();                     //��ʾ���³�

/* BiTree.cpp */
int CreateBiTree(BiTree *T)
{
    *T = (BiTree)malloc(sizeof(struct BiTreeNode));
    if (*T == NULL)
    {
        printf("�ڴ����ʧ��\n");
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
int BiTreeEmpty(BiTree T) //�ж϶������Ƿ�Ϊ�գ����Ϊ������"Ҷ�ӽڵ�"
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
        printf("���ڵ㲻��Ϊ�գ�\n");
        return 0;
    }
    temp = (BiTreeNode *)malloc(sizeof(struct BiTreeNode));
    if (temp == NULL)
    {
        printf("�ڴ����ʧ��!\n");
        return 0;
    }
    else
    {
        temp->data = e;
        temp->lchild = NULL;
        temp->rchild = NULL;
    }
    //lr���Ϊ0���������������Ϊ1����������
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
    BiTreeNode **leaves; //����Ҷ�ӽڵ�����
    int count;           //Ҷ�ӽڵ�����
    int index = 0;
    BiTreeNode **stack1; //����ڵ�
    int *stack2;         //����״̬����stack1����һ��ջ��ָ��
    int height;          //���ĸ߶�
    int top;             //ջ��ָ��
    int tag;             //����״̬���
    BiTreeNode *pCur;    //��ʱ�ڵ㣬���ڼ�¼��ǰ�ڵ��ָ��
    if (T == NULL)
    {
        printf("�ڵ�Ϊ�գ�\n");
        return 0;
    }
    count = CountLeaf(T); //Ҷ�ӽڵ����飬������Ҷ�ӽڵ�������ͬ
    printf("count: %d\n",count);
    leaves = (BiTreeNode **)malloc(sizeof(BiTreeNode *) * count);
    height = BiTreeHeight(T); //ջ�����������������һ��
    stack1 = (BiTreeNode **)malloc(sizeof(BiTreeNode *) * (height + 1));
    stack2 = (int *)malloc(sizeof(int) * (height + 1));
    /* ������������� */
    pCur = T;  //��¼���ڵ�
    index = 0; //�ڵ������±��ʼΪ0
    top = 0;   //ջ��ָ���ʼΪ0
    tag = 1;   //ѭ����ʶ����ʼΪ1������������Ϊ0
    do
    {
        while (pCur != NULL)
        {
            stack1[++top] = pCur; //��ǰ�ڵ���ջ
            stack2[top] = 0;      //��ʶ����Ϊ0����ʶ��������׼����ջ��
            pCur = pCur->lchild;
        }             //������ΪNULLֹͣ��ջ
        if (top == 0) //��Ϊ0˵���Ѿ����ʵ����ڵ�
            tag = 0;  //ֹͣ����
        else if (stack2[top] == 0)
        {
            pCur = stack1[top]->rchild; //��ǰ�ڵ��Ƶ�������
            stack2[top] = 1;            //״̬����Ϊ1����ʶ��������׼����ջ��
        }
        else //�����������ѷ���
        {
            pCur = stack1[top]; //��ջ
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
    /* ���ʽڵ㣬��ӡ��ǰ����Ľṹ */
    for (i = 0; i < depth; i++)
        printf(" ");
    printf("Room[x=%d,y=%d,width=%d,height=%d,splitVert=%d,splitPint=%d]\n", T->data.x, T->data.y, T->data.width, T->data.height, T->data.splitVert, T->data.splitPoint);
    /* ���������ӽڵ� */
    if (T->lchild != NULL)
        PreOrderTraverse(T->lchild, depth + 1);
    if (T->rchild != NULL)
        PreOrderTraverse(T->rchild, depth + 1);
    return 1;
}

/* �����ͼ */
// int gMap[ROW][COL];
int gMap[15][15];
void InitDungeon()
{
    int x, y;
    /* ��ʼ���������� */
    for (y = 0; y < ROW; y++)
        for (x = 0; x < COL; x++)
        {
            gMap[y][x] = FLOOR;
        }
    /* ������ǽ��������Χ���� */
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
    BiTree root; //���������ڵ�
    /* ���ɶ����� */
    //������һ������
    CreateBiTree(&root);
    root->data.x = 0;
    root->data.y = 0;
    root->data.width = COL;
    root->data.height = ROW;
    root->data.splitPoint = -1;
    root->data.splitVert = -1;
    //�ݹ��ַ��䣬���ɶ�����
    SplitRoom(root);
    //�����������ӡ������
    PreOrderTraverse(root, 0);
    /* ���ݶ������������� */
    //��ʼ������
    InitDungeon();
    //�޽�ǽ�壬���ϴ�ķ����ֳ�С����
    BuildWalls(root);
    //��ǽ�Ͽ��ţ�ʹ�����ҡ����·�����ͨ
    BuildDoors(root);
    //���õ��ε���ںͳ���
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
    /* ����������ϣ����ٶ����� */
    //���ٶ�����
    DestroyBiTree(root);
}
/* ʵ�ַ���ָ� */
void SplitRoom(BiTree root)
{
    int nSplitVert;
    int nSplitPoint;
    TElemType sLeft;
    TElemType sRight;
    /* �жϷ����Ƿ񻹿��Լ����ָ� */
    if (root->data.width >= LIMIT || root->data.height >= LIMIT)
    {
        //��������ָ�ķ���
        if (root->data.width < LIMIT)
        {
            nSplitVert = 0;
        }
        else if (root->data.height < LIMIT)
        {
            //������߶Ȳ���ʱ���޽�һ�º��ŵ�ǽ��������ָ������������
            nSplitVert = 1;
        }
        else
        {
            //�����㹻��ʱ���������ǽ�ڵķ���
            nSplitVert = rand() % 2;
        }
        //���ѡ��һ��λ�ý���ǽ
        if (nSplitVert) //�ֳ���������
        {
            //��data.x��data.width֮�����ѡ��һ��λ�ý�ǽ
            if (root->data.width == LIMIT)
            {
                //��С�ɷָ�䣬ֻ���ڹ̶�λ�ý�ǽ
                nSplitPoint = (root->data.x + MIN - 1);
            }
            else
            {
                //�ռ��㹻��������λ�ý�ǽ
                nSplitPoint = (root->data.x + MIN - 1) + rand() % (root->data.width - LIMIT);
            }
            //��ߵķ���
            sLeft.x = root->data.x;
            sLeft.y = root->data.y;
            sLeft.width = nSplitPoint - root->data.x + 1;
            sLeft.height = root->data.height;
            sLeft.splitVert = -1;
            sLeft.splitPoint = -1;
            //�ұߵķ���
            sRight.x = nSplitPoint;
            sRight.y = root->data.y;
            sRight.width = root->data.width - sLeft.width + 1;
            sRight.height = root->data.height;
            sRight.splitVert = -1;
            sRight.splitPoint = -1;
        }
        else //�ֳ���������
        {
            //��data.y��data.height֮�����ѡ��һ��λ������ǽ
            if (root->data.height == LIMIT)
            {
                nSplitPoint = (root->data.y + MIN - 1);
            }
            else
            {
                nSplitPoint = (root->data.y + MIN - 1) + rand() % (root->data.height - LIMIT);
            }
            //����ķ���
            sLeft.x = root->data.x;
            sLeft.y = root->data.y;
            sLeft.width = root->data.width;
            sLeft.height = nSplitPoint - root->data.y + 1;
            sLeft.splitVert = -1;
            sLeft.splitPoint = -1;
            //����ķ���
            sRight.x = root->data.x;
            sRight.y = nSplitPoint;
            sRight.width = root->data.width;
            sRight.height = root->data.height - sLeft.height + 1;
            sRight.splitVert = -1;
            sRight.splitPoint = -1;
        }
        //��¼�˷���ķָʽ
        root->data.splitVert = nSplitVert;
        root->data.splitPoint = nSplitPoint;
        //�������Һ��ӽڵ�
        InsertChild(root, 0, sLeft);
        InsertChild(root, 1, sRight);
        //�����ָ��
        SplitRoom(root->lchild);
        SplitRoom(root->rchild);
    }
}
/* ����ǽ�� */
void BuildWalls(BiTree root)
{
    int x, y;
    //�ж���ý��������ǽ���Ǻ����ǽ
    if (!BiTreeEmpty(root))
    {
        if (root->data.splitVert)
        {
            x = root->data.splitPoint; //��ǽ��λ��
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
/* ��ǽ���Ͽ��� */
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
        //���ѡ��һ��λ�ô�ͨǽ�ڻ�����
        selection = rand() % pointCount;
        gMap[points[selection].y][points[selection].x] = DOOR;
        //�����ݹ���������
        BuildDoors(root->lchild);
        BuildDoors(root->rchild);
    }
}
/* ����¥�� */
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
        printf("===��ͼ������===\n");
        //�������
        BuildDungeon();
        //��ʾ����
        PrintDungeon();
        printf("����q��������");
        scanf("%c", &c);
        printf("\n");
    } while (c != 'q');
    return 0;
}
//�ܽ����ṹ���ص�