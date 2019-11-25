#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#define MAXSIZE 20 //银行服务窗口最大数量

typedef struct Eventnode
{
    int occurTime;
    int type;
    struct Eventnode *next;
} * Event, *EventList;

typedef struct QElemTypenode
{
    int arriveTime;
    int duration;
    struct QElemTypenode *next;
} * QElemType;

typedef struct LinkedQueuenode
{
    QElemType front;
    QElemType rear;
} * LinkedQueue;

/* 插入元素 */
int OrderInsert(EventList pList, Event sEvent);
/* 判断链表是否为空 */
int EmptyList(EventList PList);
/* 删除首节点 */
int DelFirst(EventList pList, Event pEvent);
/* 遍历链表 */
int ListTraverse(EventList pList);
/* 初始化队列 */
int InitQueue(LinkedQueue pQueue);
/* 判断链表是否为空 */
int EmptyQueue(LinkedQueue pQueue);
/* 首节点出队 */
int DelQueue(LinkedQueue pQueue, QElemType pQElem);
/* 节点入队 */
int EnQueue(LinkedQueue pQueue, QElemType sQElem);
/* 获取队列长度 */
int QueueLength(LinkedQueue pQueue);
/* 获取队列首节点 */
int GetHead(LinkedQueue pQueue, QElemType pQElem);
/* 遍历队列 */
int QueueTraverse(LinkedQueue pQueue);

//bankservice.h
/* 初始化数据（关闭时间和窗口数） */
void Initialize();
/* 处理顾客到达事件 */
void CustomerArrived();
/* 处理顾客离开事件 */
void CustomerLeaved();
/* 获取最短队列编号 */
int ShortestQueue();
/* 显示当前窗口队列 */
void PrintQueue();
/* 显示当前实践表 */
void PrintEventList();
/* 银行排队模拟 */
void BankSimulation();

int OrderInsert(EventList pList, Event sEvent)
{
    Event pAfter, pBefore;
    pAfter = pList;
    pBefore = pList->next;
    while ((pAfter != NULL) && ((sEvent->occurTime) > (pAfter->occurTime)))
    {
        pBefore = pAfter;
        pAfter = pAfter->next;
    }
    pBefore->next = (Event)malloc(sizeof(struct Eventnode));
    pBefore->next->occurTime = sEvent->occurTime;
    pBefore->next->next = pAfter;
    return 1;
}

int EmptyList(EventList PList)
{
    if (PList->next == NULL)
        return 1;
    else
        return 0;
}

int DelFirst(EventList pList, Event pEvent)
{
    Event temp;
    if (EmptyList(pList))
    {
        printf("Empty List!\n");
        return 0;
    }
    else
    {
        temp = pList->next;
        pList->next = temp->next;
        pEvent = temp;
        free(temp);
        return 1;
    }
}

int ListTraverse(EventList pList)
{
    Event temp;
    temp = pList;
    while (temp->next != NULL)
    {
        temp = temp->next;
        if (temp->type == 0)
            printf("The %d-st minute, next custom is comming.\n", temp->occurTime);
        else
            printf("The %d-st minute, the %d-st custom is leaving.\n", temp->occurTime, temp->type);
    }
    printf("\n");
    return 1;
}

int InitQueue(LinkedQueue pQueue)
{
    pQueue->front = pQueue->rear = (QElemType)malloc(sizeof(struct QElemTypenode));
    if (pQueue->front == NULL)
    {
        printf("Malloc Failed!\n");
        exit(-1);
    }
    pQueue->front->next = NULL;
    return 1;
}

int EmptyQueue(LinkedQueue pQueue)
{
    if (pQueue->front == pQueue->rear)
        return 1;
    else
        return 0;
}

int DelQueue(LinkedQueue pQueue, QElemType pQElem)
{
    QElemType temp;
    if (EmptyQueue(pQueue))
    {
        printf("The queue is empty...\n");
        return 0;
    }
    else
    {
        temp = pQueue->front->next;
        pQElem = temp;
        pQueue->front->next = temp->next;
        if (pQueue->rear == temp)
            pQueue->rear = pQueue->front;
        free(temp);
        return 1;
    }
}

int EnQueue(LinkedQueue pQueue, QElemType sQElem)
{
    QElemType temp;
    temp = (QElemType)malloc(sizeof(struct QElemTypenode));
    if (temp = NULL)
    {
        printf("Malloc Faild!\n");
        exit(-1);
    }
    else
    {
        temp = sQElem;
        temp->next = NULL;
        pQueue->rear->next = temp;
        pQueue->rear = temp;
    }
    return 1;
}

int QueueLength(LinkedQueue pQueue)
{
    QElemType temp;
    int count = 0;
    temp = pQueue->front->next;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

int GetHead(LinkedQueue pQueue, QElemType pQElem)
{
    if (EmptyQueue(pQueue))
    {
        printf("Empty Queue!\n");
        return 0;
    }
    pQElem = pQueue->front->next;
    return 1;
}

int QueueTraverse(LinkedQueue pQueue)
{
    QElemType temp;
    if (EmptyQueue(pQueue))
    {
        printf("Empty Queue!\n");
        return 0;
    }
    temp = pQueue->front->next;
    while (temp != NULL)
    {
        printf(">[Arrive Time: %d-st minute,server time: %d minute]\n", temp->arriveTime, temp->duration);
        temp = temp->next;
    }
    printf("\n");
    return 1;
}

/* BankService.cpp */
int gWindowsNum;             //银行服务窗口数
int gCustomerNum;            //客户总人数
int gTotalTime;              //总服务时间
int gCloseTime;              //银行关闭时间
EventList gEventList;        //事件列表
Event gEvent;                //事件
LinkedQueue gQueue[MAXSIZE]; //队列数组
QElemType gCustomer;         //队列节点

void Initialize()
{
    int i;
    gTotalTime = 0;
    gCustomer = 0;
    Initialize(gEventList);
    printf("Input the num of bank-window(1~20):");
    scanf("%d", &gWindowsNum);
    while (gWindowsNum < 1 || gWindowsNum > MAXSIZE)
    {
        printf("Input the num of bank-window(1~20):");
        scanf("%d", &gWindowsNum);
    }
    //服务关闭时间
    printf("\n Input the closing time: ");
    scanf("%d", &gCloseTime);
    while (gCloseTime < 1)
    {
        printf("The number you inputed must > 0,Input Again: ");
        scanf("%d", &gCloseTime);
    }
    //为每一个窗口建立一个空队列
    for (i = 0; i < gWindowsNum; i++)
    {
        Initialize(gQueue[i]);
    }
}

void CustomerArrived()
{
    QElemType sQElem;
    Event sEvent;
    int index;
    int arriveTime;
    int duration;
    printf("The time now; %d-st minute\n", gEvent->occurTime);
    arriveTime = gEvent->occurTime + rand() % 5 + 1;
    duration = rand() % 21 + 10;
    if (arriveTime < gCloseTime)
    {
        gCustomerNum++;
        sEvent->occurTime = arriveTime;
        sEvent->type = 0;
        OrderInsert(gEventList, sEvent);
        sQElem->arriveTime = gEvent->occurTime;
        sQElem->duration = duration;
        index = ShortestQueue();
        EnQueue(gQueue[index], sQElem);
        if (QueueLength(gQueue[index]) == 1)
        {
            sEvent->occurTime = gEvent->occurTime + duration;
            sEvent->type = index + 1;
            OrderInsert(gEventList, sEvent);
        }
    }
    else
        printf("\nThe service is closed!\n");
}
void CustomerLeaved()
{
    Event sEvent;
    int index = gEvent->type - 1;
    DelQueue(gQueue[index], gCustomer);
    printf("\n The custom's leaving time: %d", gEvent->occurTime);
    gTotalTime += gCustomer->duration;
    if (!EmptyQueue(gQueue[index]))
    {
        GetHead(gQueue[index], gCustomer);
        sEvent->occurTime = gEvent->occurTime + gCustomer->duration;
        sEvent->type = index + 1;
        OrderInsert(gEventList, sEvent);
    }
}
int ShortestQueue()
{
    int i = 0;
    int min = 999;
    int index = -1;
    int length = 0;
    for (i = 0; i < gWindowsNum; i++)
    {
        length = QueueLength(gQueue[i]);
        if (min > length)
        {
            min = length;
            index = i;
        }
    }
    return index;
}
void PrintQueue()
{
    int i;
    printf("\n The statement of Windows: \n");
    for (i = 0; i < gWindowsNum; i++)
    {
        printf("%d-st window: \n", i);
        QueueTraverse(gQueue[i]);
    }
    printf("\n");
}
void PrintEventList()
{
    printf("\n The statement of event-table: \n");
    ListTraverse(gEventList);
}
void BankSimulation()
{
    srand((unsigned)time(NULL));
    Initialize();
    gEvent->occurTime = 0;
    gEvent->type = 0;
    OrderInsert(gEventList, gEvent);
    while (!EmptyList(gEventList))
    {
        DelFirst(gEventList, gEvent);
        if (gEvent->type = 0)
            CustomerArrived();
        else
            CustomerLeaved();
        PrintEventList();
        PrintQueue;
        system("pause");
        printf("\n");
    }
    printf("\n");
    printf("The AVR servicing time: %f minute\n", (float)gTotalTime / gCustomerNum);
    system("pause");
}

int main()
{
    return 0;
}