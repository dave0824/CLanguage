#include<stdio.h>
int main(void)
{
    int a[5]={0,1,2,3,4};
    int *s=a;
    *s++;
    printf("%d",*s);
}
