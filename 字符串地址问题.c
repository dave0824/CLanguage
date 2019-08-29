#include<stdio.h>
int main(void)
{
    char name[10]={"hello csdn"};
    if(name==&name[0])
    {
        printf("name与&name[0]取得的地址相同，地址为:%p",name);
    }
    else
    {
        printf("取得的地址不同");
    }
    printf("name+1的地址:%p\n",name+1);
    printf("&name+1的地址:%p\n",&name+1);
    return 0;
}
