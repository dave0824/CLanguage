#include<stdio.h>

int main(void){
    long b = 1008605122;
    int a = 30;
    char ch[] = "asssas";
    float f = 3.141592684;
    printf("%03d\n",a);
    printf("%x\n",a);
    printf("%#x\n",a);
    printf("%#X\n",a);
    printf("%ld\n",b);

    printf("%10s\n",ch);
    printf("%5.3s\n",ch);

    printf("%5.4f\n",f);
    printf("%3.2e",b);
}
