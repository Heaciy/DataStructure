#include "BiTree.h"

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
    *pLeaves = leaves;
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
