#include "DungeonBuilder.h"

const char TILES[] = " #+IO";

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
    //PreOrderTraverse(root, 0);

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
    index = rand() % count;
    room = pLeaves[index]->data;
    x = room.x + 1 + rand() % (room.width - 2);
    y = room.y + 1 + rand() % (room.height - 2);
    gMap[y][x] = stairs;
    free(pLeaves);
}
