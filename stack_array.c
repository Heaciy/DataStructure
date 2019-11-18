#include<stdio.h>
#include<malloc.h>
#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord 
{
    int Capacity;
    int TopOfStack;
    int *Array;//假设存储的数据类型为int
};

typedef struct StackRecord *Stack;

int IsEmpty(Stack S);
int IsFULL(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(int x,Stack S);
int Top(Stack S);
void Pop(Stack S);
int TopAndPop(Stack S);
void PrintStack(Stack S);

Stack CreateStack(int MaxElements)//创建栈
{
    Stack S;
    if(MaxElements<MinStackSize)
        printf("Stack size too small!\n");
    
    S = (Stack)malloc(sizeof(struct StackRecord));
    if(S==NULL)
        printf("Out of Space!\n");
    
    S->Array = (int*)malloc(sizeof(int)*MaxElements);
    if(S->Array==NULL)
        printf("Out of space!\n");
    S->Capacity = MaxElements;
    MakeEmpty(S);
    return S;
}

void MakeEmpty(Stack S)//使栈空
{
    S->TopOfStack = EmptyTOS;
}

int IsEmpty(Stack S)//判断栈是否为空并返回0/1
{
    return S->TopOfStack==EmptyTOS;
}

int IsFULL(Stack S)
{
    return S->TopOfStack==S->Capacity;
}

void DisposeStack(Stack S)//释放栈
{
    if(S!=NULL)
    {
        free(S->Array);
        free(S);
    }
}
void Push(int X,Stack S)
{
    if(IsFULL(S))
        printf("Full Stack!\n");
    else
        S->Array[++S->TopOfStack] = X;
}

int Top(Stack S)
{
    if(!IsEmpty(S))
        return S->Array[S->TopOfStack];
    else
    {
        printf("Empty stack!\n");
        return 0;
    }
}

void Pop(Stack S)
{
    if(IsEmpty(S))
        printf("Empty Stack!\n");
    S->TopOfStack--;
}

int TopAndPop(Stack S)
{
    if(!IsEmpty(S))
        return S->Array[S->TopOfStack--];
    else
        printf("Empty Stack!\n");
}

void PrintStack(Stack S)
{
    if(!IsEmpty(S))
    {
        for(int i=0;i<=(S->TopOfStack);i++)
        {
            printf("the %d-st: %d\n",i,S->Array[i]);
        }
    }
    else
        printf("Empty Stack!\n");
}

int main()
{
    Stack S = CreateStack(10);
    for(int i = 0; i<5; i++)
    {
        Push(i,S);
        printf("Push %d\n",i);
    }
    PrintStack(S);
    DisposeStack(S);
    return 0;
}