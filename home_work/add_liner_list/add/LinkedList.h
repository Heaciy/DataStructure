#ifndef ADD_LINKEDLIST_H
#define ADD_LINKEDLIST_H

#define ISEMPTY printf("Empty List\n");

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node
{
    double value;
    int val_n;
    struct node *next;
};
typedef struct node *snode;

/*检查输入*/
bool GetInt();

/*从链表的末尾插入数据*/
void insert_at_last();

/*处理输入数据并组织生成相应的链表*/
void input_data();

/*打印列表*/
void print_polyn();

/*对列表进行排序(并最简化(合并公因式))*/
void sort_polyn();

/*检查指数并合并公因式*/
void equal_to();

/*释放分配的空间*/
void free_list();

/*处理链表相加*/
snode add_polyn();

/*创建链表(创建头指针)*/
snode create_polyn();

/*根据另外两条链表创建第三条链表*/
snode create_the_third_polyn();

#endif //ADD_LINKEDLIST_H
