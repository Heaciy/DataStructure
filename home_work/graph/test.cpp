#include <iostream>
using namespace std;

#define MAXVEX 100       /* ��󶥵���,Ӧ���û����� */
typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType;    /* ���ϵ�Ȩֵ����Ӧ���û����� */

typedef struct EdgeNode /* �߱����  */
{
    int adjvex;            /* �ڽӵ���,�洢�ö����Ӧ���±� */
    EdgeType weight;       /* ���ڴ洢Ȩֵ,���ڷ���ͼ���Բ���Ҫ */
    struct EdgeNode *next; /* ����,ָ����һ���ڽӵ� */
} EdgeNode;

typedef struct VextexNode /* �������� */
{
    VertexType data;     /* ������,�洢������Ϣ */
    EdgeNode *firstedge; /* �߱�ͷָ�� */
} VextexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numNodes, numEdges; /* ͼ�е�ǰ�������ͱ��� */
} GraphAdjList;

void dfs(GraphAdjList G, int v);
int visited[MAXVEX]; //���dfs�����飬����û�б����ʹ�

void dfs(GraphAdjList G, int v)
{
    cout << G.adjList[v].data;
    visited[v] = 1;
    EdgeNode *p = G.adjList[v].firstedge;
    while (p)
    {
        if (visited[p->adjvex] == 0)
            dfs(G, p->adjvex);
        else
            p = p->next;
    }
}

void CreateALGraph(GraphAdjList *Gp)
{
    int i, j, k;
    EdgeNode *pe;
    cout << "���붥�����ͱ���(�ո�ָ���:" << endl;
    cin >> Gp->numNodes >> Gp->numEdges;

    for (i = 0; i < Gp->numNodes; i++)
    {
        cout << "���붥����Ϣ��" << endl;
        cin >> Gp->adjList[i].data;
        Gp->adjList[i].firstedge = NULL; /* ���߱���Ϊ�ձ� */
    }

    for (k = 0; k < Gp->numEdges; k++) /* �����߱� */
    {
        cout << "�����(vi,vj)�Ķ������i,j���ո�ָ���:" << endl;
        cin >> i >> j;
        pe = (EdgeNode *)malloc(sizeof(EdgeNode));
        pe->adjvex = j; /* �ڽ����Ϊj */
        /* ��pe��ָ��ָ��ǰ������ָ��Ľ�� */
        pe->next = Gp->adjList[i].firstedge;
        Gp->adjList[i].firstedge = pe; /* ����ǰ�����ָ��ָ��pe */
    }
}

int main(void)
{
    GraphAdjList GL;
    CreateALGraph(&GL);
    int v;
    cout<< "��������ţ�"<<endl;
    cin>>v;
    dfs(GL, v);
    return 0;
}