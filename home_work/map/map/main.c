#include "DungeonBuilder.h"

int main(void)
{
    char c;
    srand((unsigned)time(NULL));
    do
    {
        printf("===��ͼ������===\n");
        //�������
        BuildDungeon();
        //��ʾ����
        PrintDungeon();
        printf("����q��������");
        scanf("%c", &c);
        printf("\n");
    } while (c != 'q');
    return 0;
}