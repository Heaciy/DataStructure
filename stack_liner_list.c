#include<stdio.h>
#include<malloc.h>

struct Node
{
    /* data */
    int value;
    struct Node *Next;
};
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty(Stack S);
Stack CreateStack();
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(int x, Stack s);
int Top(Stack S);
void Pop(Stack S);
void PrintStack(Stack S);
//这里的S都是头指针，没有数据域(数据域为空)，只有指针域。

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

void Pop(Stack S)
{
    PtrToNode FirstCell;
    if( IsEmpty(S) )
        printf("Empty Satck");
    else
    {
        FirstCell = S->Next;
        S->Next = S->Next->Next;
        free(FirstCell);
    }
    
}

void MakeEmpty(Stack S)
{
    if(S == NULL)
        printf("Must Create Stack First1");
    else
        while (! IsEmpty(S))
        {
            Pop(S);
        }
}

Stack CreateStack()
{
    Stack S;
    S = malloc(sizeof(struct Node));
    if(S ==NULL)
    {
        printf("Memory was not allocated\n");
    }
    S->Next = NULL;
    MakeEmpty(S);
    return S;
}



void Push(int x, Stack S)
{
    PtrToNode TmpCell;
    TmpCell = malloc(sizeof(struct Node));
    if(TmpCell==NULL)
        printf("Out of Space");
    else
    {
        TmpCell->value = x;
        TmpCell->Next  = S->Next;
        S->Next = TmpCell;
    }
}

int Top(Stack S)
{
    if(!IsEmpty(S))
        return S->Next->value;
    else
    {
        printf("Empty Stack!");
        return 0;
    }
    
}

void PrintStack(Stack S)
{
    if(IsEmpty(S))
        printf("Empty Stack!");
    else
    {
        Stack Temp=S->Next;
        while(Temp!=NULL)//Temp在从上往下挪动，因为栈底的元素的Next指针
        {                //等于最初生成的头指针S的S->Next=Null相同，为Null,所以遍历会在遍历到栈底时结束
            printf("%d\n", Temp->value);
            Temp = Temp->Next;
        }
    }
}

int main()
{
    Stack S = CreateStack();
    for(int i = 0; i < 10; i++)
    {
        Push(i, S);
    }
    printf("The Top Element: %d\n",Top(S));
    PrintStack(S);
    return 0;
}