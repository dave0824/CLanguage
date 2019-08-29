#include<stdio.h>
int main()
{
    int a[10]={0,5,4,8,9,7,2,6,1,3};
    int i,j;
    int temp;
    for(i=0;i<10;i++)
        for(j=i+1;j<10;j++)
        {
            if(a[i]>a[j])
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    for(i=0;i<10;i++)
    printf("%d,",a[i]);
    return 0;
}
