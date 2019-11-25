#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#define MAXSIZE 20 //���з��񴰿��������

typedef struct Eventnode
{
    int occurTime;
    int type;
    struct Eventnode *next;
}Event, *EventList;

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
} LinkedQueue;

/* ��ʼ���¼��б� */
int InitList(EventList pList);
/* ����Ԫ�� */
int OrderInsert(EventList pList, Event sEvent);
/* �ж������Ƿ�Ϊ�� */
int EmptyList(EventList PList);
/* ɾ���׽ڵ� */
int DelFirst(EventList pList, Event *pEvent);
/* �������� */
int ListTraverse(EventList pList);
/* ��ʼ������ */
int InitQueue(LinkedQueue *pQueue);
/* �ж������Ƿ�Ϊ�� */
int EmptyQueue(LinkedQueue *pQueue);
/* �׽ڵ���� */
int DelQueue(LinkedQueue *pQueue, QElemType pQElem);
/* �ڵ���� */
int EnQueue(LinkedQueue *pQueue, QElemType sQElem);
/* ��ȡ���г��� */
int QueueLength(LinkedQueue *pQueue);
/* ��ȡ�����׽ڵ� */
int GetHead(LinkedQueue *pQueue, QElemType pQElem);
/* �������� */
int QueueTraverse(LinkedQueue *pQueue);

//bankservice.h
/* ��ʼ�����ݣ��ر�ʱ��ʹ������� */
void Initialize();
/* ����˿͵����¼� */
void CustomerArrived();
/* ����˿��뿪�¼� */
void CustomerLeaved();
/* ��ȡ��̶��б�� */
int ShortestQueue();
/* ��ʾ��ǰ���ڶ��� */
void PrintQueue();
/* ��ʾ��ǰʵ���� */
void PrintEventList();
/* �����Ŷ�ģ�� */
void BankSimulation();

int InitList(EventList pList)
{
    pList = (Event*)malloc(sizeof(struct Eventnode));
    if (pList == NULL)
    {
        printf("�ڴ����ʧ�ܣ�");
        exit(-1);
    }
    else
        return 1;
}

int OrderInsert(EventList pList, Event sEvent)
{
    Event *pAfter, *pBefore;
    pAfter = pList;
    pBefore = pList->next;
    while ((pAfter != NULL) && ((sEvent.occurTime) > (pAfter->occurTime)))
    {
        pBefore = pAfter;
        pAfter = pAfter->next;
    }
    pBefore->next = (Event*)malloc(sizeof(struct Eventnode));
    pBefore->next->occurTime = sEvent.occurTime;
    pBefore->next->type = sEvent.type;
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

int DelFirst(EventList pList, Event *pEvent)
{
    Event *temp;
    if (EmptyList(pList))
    {
        printf("����Ϊ��!\n");
        return 0;
    }
    else
    {
        temp = pList->next;
        pList->next = temp->next;
        *pEvent = *temp;
        free(temp);
        return 1;
    }
}

int ListTraverse(EventList pList)
{
    Event *temp;
    temp = pList;
    while (temp->next != NULL)
    {
        temp = temp->next;
        if (temp->type == 0)
            printf("�� %d ����, ��һ���ͻ���������.\n", temp->occurTime);
        else
            printf("�� %d ����, %d�Ŵ��ڵĹ˿ͼ����뿪.\n", temp->occurTime, temp->type);
    }
    printf("\n");
    return 1;
}

int InitQueue(LinkedQueue *pQueue)
{
    pQueue->front = pQueue->rear = (QElemType)malloc(sizeof(struct QElemTypenode));
    if (pQueue->front == NULL)
    {
        printf("�ڴ����ʧ��!\n");
        exit(-1);
    }
    pQueue->front->next = NULL;
    return 1;
}

int EmptyQueue(LinkedQueue *pQueue)
{
    if (pQueue->front == pQueue->rear)
        return 1;
    else
        return 0;
}

int DelQueue(LinkedQueue *pQueue, QElemType pQElem)
{
    QElemType temp;
    if (EmptyQueue(pQueue))
    {
        printf("����Ϊ�գ����ܼ���������\n");
        return 0;
    }
    else
    {
        temp = pQueue->front->next;
        *pQElem = *temp;
        pQueue->front->next = temp->next;
        if (pQueue->rear == temp)
            pQueue->rear = pQueue->front;
        free(temp);
        return 1;
    }
}

int EnQueue(LinkedQueue *pQueue, QElemType sQElem)
{
    QElemType temp;
    temp = (QElemType)malloc(sizeof(struct QElemTypenode));
    if (temp = NULL)
    {
        printf("�ڴ����ʧ��!\n");
        exit(-1);
    }
    else
    {
        *temp = *sQElem;
        temp->next = NULL;
        pQueue->rear->next = temp;
        pQueue->rear = temp;
    }
    return 1;
}

int QueueLength(LinkedQueue *pQueue)
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

int GetHead(LinkedQueue *pQueue, QElemType pQElem)
{
    if (EmptyQueue(pQueue))
    {
        printf("����Ϊ��!\n");
        return 0;
    }
    *pQElem = *(pQueue->front->next);
    return 1;
}

int QueueTraverse(LinkedQueue *pQueue)
{
    QElemType temp;
    if (EmptyQueue(pQueue))
    {
        printf("����Ϊ��!\n");
        return 0;
    }
    temp = pQueue->front->next;
    while (temp != NULL)
    {
        printf(">[����ʱ��: ��%d����,����ʱ��: %d ����]\n", temp->arriveTime, temp->duration);
        temp = temp->next;
    }
    printf("\n");
    return 1;
}

/* BankService.cpp */
int gWindowsNum;             //���з��񴰿���
int gCustomerNum;            //�ͻ�������
int gTotalTime;              //�ܷ���ʱ��
int gCloseTime;              //���йر�ʱ��
EventList gEventList;        //�¼��б�
Event gEvent;                //�¼�
LinkedQueue gQueue[MAXSIZE]; //��������
QElemType gCustomer;         //���нڵ�

void Initialize()
{
    int i;
    gTotalTime = 0;
    gCustomer = 0;
    InitList(gEventList);
    printf("���������з��񴰿ڸ���(1~20):");
    scanf("%d", &gWindowsNum);
    while (gWindowsNum < 1 || gWindowsNum > MAXSIZE)
    {
        printf("������1��%d֮�������:", MAXSIZE);
        scanf("%d", &gWindowsNum);
    }
    //����ر�ʱ��
    printf("\n���������ر�ʱ��(��λ������): ");
    scanf("%d", &gCloseTime);
    while (gCloseTime < 1)
    {
        printf("����������������: ");
        scanf("%d", &gCloseTime);
    }
    //Ϊÿһ�����ڽ���һ���ն���
    for (i = 0; i < gWindowsNum; i++)
    {
        InitQueue(&gQueue[i]);
    }
}
void CustomerArrived()
{
    QElemType sQElem;
    Event sEvent;
    int index;
    int arriveTime;
    int duration;
    printf("��ǰʱ��: ��%d����\n", gEvent.occurTime);
    arriveTime = gEvent.occurTime + rand() % 5 + 1;
    duration = rand() % 21 + 10;
    if (arriveTime < gCloseTime)
    {
        gCustomerNum++;
        sEvent.occurTime = arriveTime;
        sEvent.type = 0;
        OrderInsert(gEventList, sEvent);
        sQElem->arriveTime = gEvent.occurTime;
        sQElem->duration = duration;
        index = ShortestQueue();
        EnQueue(&gQueue[index], sQElem);
        if (QueueLength(&gQueue[index]) == 1)
        {
            sEvent.occurTime = gEvent.occurTime + duration;
            sEvent.type = index + 1;
            OrderInsert(gEventList, sEvent);
        }
    }
    else
        printf("\n�Ŷӷ����ѹرգ����ٽ����¿ͻ���\n");
}
void CustomerLeaved()
{
    Event sEvent;
    int index = gEvent.type - 1;
    DelQueue(&gQueue[index], gCustomer);
    printf("\n�ͷ��뿪ʱ��: %d", gEvent.occurTime);
    gTotalTime += gCustomer->duration;
    if (!EmptyQueue(&gQueue[index]))
    {
        GetHead(&gQueue[index], gCustomer);
        sEvent.occurTime = gEvent.occurTime + gCustomer->duration;
        sEvent.type = index + 1;
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
        length = QueueLength(&gQueue[i]);
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
    printf("\n�����Ŷ�״̬: \n");
    for (i = 0; i < gWindowsNum; i++)
    {
        printf("%d�Ŵ���: \n", i);
        QueueTraverse(&gQueue[i]);
    }
    printf("\n");
}
void PrintEventList()
{
    printf("\n�¼���״̬: \n");
    ListTraverse(gEventList);
}
void BankSimulation()
{
    srand((unsigned)time(NULL));
    Initialize();
    gEvent.occurTime = 0;
    gEvent.type = 0;
    OrderInsert(gEventList, gEvent);
    while (!EmptyList(gEventList))
    {
        DelFirst(gEventList, &gEvent);
        if (gEvent.type = 0)
            CustomerArrived();
        else
            CustomerLeaved();
        PrintEventList();
        PrintQueue;
        system("pause");
        printf("\n");
    }
    printf("\n");
    printf("�ͻ�ƽ������ʱ��: %f����\n", (float)gTotalTime / gCustomerNum);
    system("pause");
}

int main()
{
    BankSimulation();
}