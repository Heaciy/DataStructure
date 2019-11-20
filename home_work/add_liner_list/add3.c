#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#define ISEMPTY printf("Empty List\n");
const int MAX_NUM = 2; //多项式的个数；

struct node
{
    double value;
    int val_n;
    struct node *next;
};

typedef struct node *snode;
/* 检查输入数据 */
bool GetInt();
/* 比较两个数据的大小 */
int cmp(int a, int b);
/* 从列表最后插入 */
void insert_at_last();
/* 输入数据并生成相应链表 */
void input_data();
/* 打印列表 */
void print_polyn();
/* 链表排序 */
void sort_polyn();
/* 释放内存 */
void free_list();
/* 两个链表相加 */
snode add_polyn();
/* 创建链表的头节点 */
snode create_polyn();

snode create_polyn()
{
    snode header;
    header = (snode)malloc(sizeof(struct node));
    header->next = NULL;
    return header;
}

void insert_at_last(snode head, int val, int val_n)
{
    snode temp = head;
    while (temp->next != NULL) //也可以设置尾指针
    {
        temp = temp->next;
    }
    temp->next = (snode)malloc(sizeof(struct node));
    temp->next->value = val;
    temp->next->val_n = val_n;
    temp->next->next = NULL;
}

void input_data(snode head, int nOrder)
{
    double val;
    int val_n, x;
    printf("\nThe items' num of %dst polyn: ", nOrder);
    scanf("%d", &x);
    for (int i = 1; i <= x; i++)
    {
        printf("Input %dst item's value: ", i);
        scanf("%lf", &val);
        printf("Input %dst item's val_n: ", i);
        scanf("%d", &val_n);
        insert_at_last(head, val, val_n);
    }
}

void print_polyn(snode head)
{
    snode temp = head->next;
    if (temp == NULL)
    {
        ISEMPTY;
    }
    else
    {
        if (temp->val_n != 0) //打印第一项
        {
            if (temp->val_n == 1)
                printf("%.2f X", temp->value);
            else
                printf("%.2f X^%d", temp->value, temp->val_n);
        }
        else
            printf("%.2f ", temp->value);
        for (temp = temp->next; temp != NULL; temp = temp->next)
        {
            if ((temp->value) > 0)
            {
                if (temp->val_n != 0)
                {
                    if (temp->val_n == 1)
                        printf("+%.2f X", temp->value);
                    else
                        printf("+%.2f X^%d", temp->value, temp->val_n);
                }
                else
                    printf("+%.2f ", temp->value);
            }
            else
            {
                if (temp->val_n != 0)
                {
                    if (temp->val_n == 1)
                        printf("%.2f X", temp->value);
                    else
                        printf("%.2f X^%d", temp->value, temp->val_n);
                }
                else
                    printf("%.2f ", temp->value);
            }
        }
        printf("\n");
    }
}

void sort_polyn(snode head)
{
    snode temp, nex;
    double swap_val;
    int swap_n;
    if (head->next != NULL)
    {
        for (temp = head->next; temp != NULL; temp = temp->next)
        {
            for (nex = temp->next; nex != NULL; nex = nex->next)
            {
                if ((temp->val_n) > (nex->val_n))
                {
                    swap_val = temp->value;
                    swap_n = temp->val_n;
                    temp->value = nex->value;
                    temp->val_n = nex->val_n;
                    nex->value = swap_val;
                    nex->val_n = swap_n;
                }
            }
        }
    }
}

int cmp(int a, int b)
{
    if (a < b)
        return -1;
    else if (a == b)
        return 0;
    else
        return 1;
}

snode add_polyn(snode head1, snode head2)
{
    int sum;
    snode result = create_polyn();
    sort_polyn(head1);
    sort_polyn(head2);
    snode now1, now2;
    now1 = head1->next;
    now2 = head2->next;
    while (now1 && now2)
    {
        switch (cmp(now1->val_n, now2->val_n))
        {
        case -1:
            insert_at_last(result, now1->value, now1->val_n);
            now1 = now1->next;
            break;
        case 0:
            sum = now1->value + now2->value;
            if (sum != 0)
            {
                insert_at_last(result, sum, now1->val_n);
                now1 = now1->next;
            }
            else
            {
                now1 = now1->next;
            }
            now2 = now2->next;
            break;
        case 1:
            insert_at_last(result, now2->value, now2->val_n);
            now2 = now2->next;

            break;
        }
    }
    if (now1 != NULL)
    {
        while (now1 != NULL)
        {
            insert_at_last(result, now1->value, now1->val_n);
            now1 = now1->next;
        }
    }
    if (now2 != NULL)
    {
        while (now2 != NULL)
        {
            insert_at_last(result, now2->value, now2->val_n);
            now2 = now2->next;
        }
    }
    return result;
}

void free_list(snode head)
{
    snode del = head;
    snode temp;
    while (del != NULL)
    {
        temp = del->next;
        free(del);
        del = temp;
    }
}

int main()
{
    snode head[MAX_NUM];
    for (int i = 0; i < MAX_NUM; i++)
    {
        head[i] = create_polyn();
        input_data(head[i], i + 1);
        printf("The %dst polyn: ", i + 1);
        print_polyn(head[i]);
    }
    printf("\n");

    snode result = add_polyn(head[0], head[1]);
    printf("The sum :");
    print_polyn(result);
    free_list(result);
    free(head[0]);
    free(head[1]);
    return 0;
}