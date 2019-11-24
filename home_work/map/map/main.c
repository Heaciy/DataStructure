#include "DungeonBuilder.h"

int main(void)
{
    char c;
    srand((unsigned)time(NULL));
    do
    {
        printf("===地图生成器===\n");
        //建造地牢
        BuildDungeon();
        //显示地牢
        PrintDungeon();
        printf("输入q结束程序：");
        scanf("%c", &c);
        printf("\n");
    } while (c != 'q');
    return 0;
}