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
int cmp(int a, int b);
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
    else
    {
        ISEMPTY;
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
snode add_polyn(snode temp1, snode temp2)
{
    int sum;
    sort_polyn(temp1);
    sort_polyn(temp2);
    snode last, now1, now2;
    now1 = temp1->next;
    now2 = temp2->next;
    while (now1 && now2)
    {
        switch (cmp(now1->val_n, now2->val_n))
        {
        case -1:
            now1 = now1->next;
            break;
        case 0:
            sum = now1->value + now2->value;
            if (sum != 0)
            {
                now1->value = sum;
            }
            else
            {
                temp1->next = now1->next;
                free(now1);
                now1 = temp1->next;
            }
            temp2->next = now2->next;
            free(now2);
            now2 = temp2->next;
            break;
        case 1:
            temp2->next = now2->next;
            now2->next = now1;
            temp1->next = now2;
            now2 = temp2->next;
            break;
        }
    }
    if (temp2->next != NULL)
    {
        last = temp1;
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = temp2->next;
    }
    return temp1;
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