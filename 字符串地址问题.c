#include<stdio.h>
int main(void)
{
    char name[10]={"hello csdn"};
    if(name==&name[0])
    {
        printf("name��&name[0]ȡ�õĵ�ַ��ͬ����ַΪ:%p",name);
    }
    else
    {
        printf("ȡ�õĵ�ַ��ͬ");
    }
    printf("name+1�ĵ�ַ:%p\n",name+1);
    printf("&name+1�ĵ�ַ:%p\n",&name+1);
    return 0;
}
