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

/* 定义二叉树 */
struct BiTreeNode
{
    TElemType data;
    struct BiTreeNode *lchild;
    struct BiTreeNode *rchild;
};
typedef struct BiTreeNode *BiTree, BiTreeNode;

int CreateBiTree(BiTree *T);                    //创建二叉树
int DestroyBiTree(BiTree T);                    //销毁二叉树
int BiTreeEmpty(BiTree T);                      //判断二叉树是否为空(如果是则是一个叶子节点)
int BiTreeHeight(BiTree T);                     //返回树的深度
int CountLeaf(BiTree T);                        //返回叶子结点的数目
int GetLeaves(BiTree T, BiTreeNode ***pLeaves);  //获得所有叶子节点，返回叶子节点数
int InsertChild(BiTree T, int lr, TElemType e); //先序遍历二叉树，打印树的结构
int PreOrderTraverse(BiTree T, int depth);

typedef struct BiTreeNode *BiTree, BiTreeNode;

#endif //MAP_BITREE_H
