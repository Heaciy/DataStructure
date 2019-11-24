#include "BiTree.h"

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
    *pLeaves = leaves;
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
