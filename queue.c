#include <stdio.h>
#include <malloc.h>

/* 使用数组实现队列 */
struct QueueRecord
{
    int Capacity;
    int Front;  //头
    int Rear;   //尾
    int Size;   //队列大小
    int *Array; //队列存储的数据类型
};
typedef struct QueueRecord *Queue;

int IsEmpty(Queue Q);
int ISFull(Queue Q);
Queue CreateQueue(int MaxElement);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(int x, Queue Q);
int Front(Queue Q);
void Dequeue(Queue Q);
int FrontAndDequeue(Queue Q);

/* 判断队列是否为空 */
int IsEmpty(Queue Q)
{
    return Q->Size == 0;
}

/* 构造空队列 */
void MakeEmpty(Queue Q)
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

/* 入队 */
static int Succ(int value, Queue Q)
{
    if (IsFull(Q))
        value = 0;
    return value;
}
void EnQueue(int X, Queue Q)
{
    if(IsFull(Q))
        printf("Full Queue!");
    else
    {
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear] = X;
    }
}

