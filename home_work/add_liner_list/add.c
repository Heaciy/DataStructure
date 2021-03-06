#include <stdio.h>
#include <malloc.h>
#define ISEMPTY printf("Empty List\n");
const int MAX_NUM = 2; //多项式的个数；

struct node
{
    double value;
    int val_n;
    struct node *next;
};

typedef struct node *snode;
void insert_at_last();
void input_data();
void print_polyn();
void sort_polyn();
void equal_to();
void free_list();
snode add_polyn();
snode create_polyn();

snode create_polyn()
{
    snode header;
    header = (snode)malloc(sizeof(struct node));
    header->next = NULL;
    return header;
}

/* void create_polyn(snode *head)
{
    *head = (snode)malloc(sizeof(struct node));
    (*head)->next = NULL;
} */


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
            //printf("pdb\n");
        }
        else
        {
            temp->next = nex->next;
            //pre->next->next = nex ->next;
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
        printf("After sort:\n");
        print_polyn(head);
        // 排序后进行最简化处理
        printf("After equal_to():\n");
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

snode add_polyn(snode head1, snode head2)
{
    snode head = head1;
    snode temp = head;
    while (temp->next != NULL) //也可以设置尾指针
    {
        temp = temp->next;
    }
    temp->next = head2->next;
    sort_polyn(head);
    return head;
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
    printf("List Freed\n");
}

int main()
{
    snode head[MAX_NUM];
    for (int i = 0; i < MAX_NUM; i++)
    {
        head[i] = create_polyn();
        input_data(head[i], i + 1);
        print_polyn(head[i]);
        // sort_polyn(head[i]);
    }
    printf("\n");

    snode result = add_polyn(head[0], head[1]);
    print_polyn(result);
    free_list(result);
    return 0;
}