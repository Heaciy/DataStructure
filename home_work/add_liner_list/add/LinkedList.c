#include "LinkedList.h"

bool GetInt(int *value) {
    char str[256] = {0};
    fflush(stdin);
    fgets(str, 256,stdin);
    unsigned int index = 1;
    int nTemp = 0;
    if (str[0] == '-')
        nTemp = 1;
    for (index = nTemp; index < strlen(str); index++)
        if (str[index] < '0' || str[index] > '9')
            return false;
    *value = atoi(str);
    return true;
}

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
    printf("\nenter the num of items in the %dst polyn: ", nOrder);
    scanf("%d", &x); //用头指针的数据域存放多项式的项数
    head->val_n = x;
    for (int i = 1; i <= x; i++)
    {
        printf("value of %dst item: ", i);
        scanf("%lf", &val);
        printf("val_n of %dst item: ", i);
        scanf("%d", &val_n);
        insert_at_last(head, val, val_n);
    }
}

void print_polyn(snode head)
{
    //sort_polyn(head);
    snode temp = head->next;
    if (temp == NULL)
    {
        ISEMPTY;
    }
    else
    {
        printf("%.2f X^%d", temp->value, temp->val_n);
        for (temp = temp->next; temp != NULL; temp = temp->next)
        {
            if ((temp->value) > 0)
                printf("+%.2f X^%d", temp->value, temp->val_n);
            else
                printf("%.2f X^%d", temp->value, temp->val_n);
        }
        printf("\n");
    }
}

void equal_to(snode pre)
{
    snode temp = pre->next;
    if ((temp != NULL) && (temp->next != NULL) && (temp->val_n == temp->next->val_n))
    {
        temp->value += temp->next->value;
        snode nex = temp->next;
        if (temp->value == 0)
        {
            snode now = temp;
            temp = nex->next;
            pre->next = temp;
            free(now);
            free(nex);
        }
        else
        {
            temp->next = nex->next;
            free(nex);
        }
        equal_to(pre);
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
        // 排序后进行最简化处理
        temp = head;
        while (temp != NULL)
        {
            equal_to(temp);
            temp = temp->next;
        }
    }
    else
    {
        ISEMPTY;
    }
}

snode create_the_third_polyn(snode head1, snode head2)
{
    snode Third_polyn = create_polyn();
    snode temp1;
    int i;
    for (i = 0, temp1 = head1->next; i < head1->val_n; i++, temp1 = temp1->next) //拷贝链1
    {
        insert_at_last(Third_polyn, temp1->value, temp1->val_n);
    }
    for (i = 0, temp1 = head2->next; i < head2->val_n; i++, temp1 = temp1->next) //拷贝链2
    {
        insert_at_last(Third_polyn, temp1->value, temp1->val_n);
    }
    return Third_polyn;
}

snode add_polyn(snode head1, snode head2)
{
    snode result = create_the_third_polyn(head1, head2);//将两条链拷贝到新链上
    sort_polyn(result);//对新链进行排序即可(因为在排序的函数中已经包含了最简化过程)
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
        //printf("*");
        del = temp;
    }
    //printf("List Freed\n");
}