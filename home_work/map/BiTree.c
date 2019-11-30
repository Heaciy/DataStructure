#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 20

typedef struct BiTree
{
    char data;
    struct BiTree *lchild;
    struct BiTree *rchild;
} * BiTree;

typedef struct BiTree_static
{
    char data;
    int lchild;
    int rchild;
} BiTree_static;

/* ʹ�õݹ�ķ��������� */
BiTree Create_BiTree()
{
    BiTree temp;
    char c;
    scanf("%c", &c);
    if (c == '.')
        temp = NULL;
    else
    {
        temp = (BiTree)malloc(sizeof(struct BiTree));
        temp->data = c;
        temp->lchild = Create_BiTree();
        temp->rchild = Create_BiTree();
    }
    return temp;
}
/* �ݹ鷽��������� */
void prioritiesTraverse(BiTree T)
{
    if (T != NULL)
    {
        printf("%C ", T->data);
        prioritiesTraverse(T->lchild);
        prioritiesTraverse(T->rchild);
    }
}
/* �ݹ鷽��������� */
void middleTraverse(BiTree T)
{
    if (T != NULL)
    {
        middleTraverse(T->lchild);
        printf("%c ", T->data);
        middleTraverse(T->rchild);
    }
}
/* �ݹ鷽��������� */
void lastTraverse(BiTree T)
{
    if (T != NULL)
    {
        lastTraverse(T->lchild);
        lastTraverse(T->rchild);
        printf("%c ", T->data);
    }
}
/* ����̬������ת���ɾ�̬������ */
static int j = 0;
void Create_static(BiTree T, BiTree_static *T_s)
{
    if (T != NULL)
    {
        int temp = j;
        T_s[j++].data = T->data;
        if (T->lchild != NULL)
        {
            T_s[j - 1].lchild = j;
            Create_static(T->lchild, T_s);
        }
        else
            T_s[j - 1].lchild = 0;
        if (T->rchild != NULL)
        {
            T_s[temp].rchild = j;
            Create_static(T->rchild, T_s);
        }
        else
            T_s[temp].rchild = 0;
    }
}
int main()
{
    BiTree T;
    BiTree_static a[MAXSIZE];
    printf("������������Ľڵ����ݣ�����Ϊ�ַ��ͣ���Ϊ��ʱ��.����:\n");
    T = Create_BiTree();
    Create_static(T, &a[0]);

    printf("���������");
    prioritiesTraverse(T);
    printf("\n");
    printf("���������");
    middleTraverse(T);
    printf("\n");
    printf("���������");
    lastTraverse(T);
    printf("\n\n");
    printf("˵���������ӻ��Һ���Ϊ��ʱ����0���\n\n");
    printf("��̬��������Ϊ��\n");
    printf("i\tdata\tlchild\trchild\t\n");
    for (int m = 0; m < j; m++)
    {
        printf("%d\t%c\t%d\t%d\n", m, a[m].data, a[m].lchild, a[m].rchild);
    }
}