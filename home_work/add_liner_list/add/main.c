#include "LinkedList.h"
const int MAX_NUM = 2; //多项式的个数；

int main()
{
    snode head[MAX_NUM];//存放两条链表的头指针的数组
    for (int i = 0; i < MAX_NUM; i++)
    {
        head[i] = create_polyn();//生成链表头节点
        input_data(head[i], i + 1);
        print_polyn(head[i]);
        // sort_polyn(head[i]);//如果有需要可以对用户输入的链表进行排序
    }
    printf("\n");
    snode result = add_polyn(head[0], head[1]);
    printf("The result:\n");
    /*打印结果*/
    print_polyn(result);
    /*释放分配的空间*/
    free_list(result);
    free_list(head[0]);
    free_list(head[1]);
    return 0;
}