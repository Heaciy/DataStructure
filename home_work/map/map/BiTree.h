#ifndef MAP_BITREE_H
#define MAP_BITREE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

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

int CreateBiTree(BiTree *T);                    //����������
int DestroyBiTree(BiTree T);                    //���ٶ�����
int BiTreeEmpty(BiTree T);                      //�ж϶������Ƿ�Ϊ��(���������һ��Ҷ�ӽڵ�)
int BiTreeHeight(BiTree T);                     //�����������
int CountLeaf(BiTree T);                        //����Ҷ�ӽ�����Ŀ
int GetLeaves(BiTree T, BiTreeNode ***pLeaves);  //�������Ҷ�ӽڵ㣬����Ҷ�ӽڵ���
int InsertChild(BiTree T, int lr, TElemType e); //�����������������ӡ���Ľṹ
int PreOrderTraverse(BiTree T, int depth);

typedef struct BiTreeNode *BiTree, BiTreeNode;

#endif //MAP_BITREE_H
