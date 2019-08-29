/*  HELLO.C -- Hello, world */

#include <stdio.h>

double Price()
{
    double a; //Record baggage of weight
    int flag;//Record type of ticket
    double price;//Record transport baggage price
    char ch;//Record whether disabled
    char ch2;//Record whether chinese
    printf("please select type of passenger ticket:\n");
    printf("(1)head grade space\n");
    printf("(2)job object  space\n");
    printf("(3)economy space\n");
    scanf("%d",&flag);
    printf("please input baggage weight(kg)\n");
    scanf("%lf",&a);
    if(a<=20)
    {
        return 0;
    }
    switch (flag)
    {
        case 1:  price=(a-20)*6;
                 break;
        case 2:  price=(a-20)*8;
                 break;
        case 3:  price=(a-20)*10;
                 break;
        default:
                printf("Don't money\n");
                break;
    }
    printf("Are you disabled?(y|n)\n");
    getchar();
    scanf("%c",&ch);
    if(ch=='Y'||ch=='y')
    {
        price=price*0.5;
    }
    printf("Are you chinese?(y|n)\n");
    getchar();
    scanf("%c",&ch2);
    if(ch2=='N'||ch2=='n')
    {
        price=price*1.5;
    }
    return price;


}
int main(void)
{
    printf("Transport baggage price :%f\n",Price());
}
