#include<stdio.h>
#include<string.h>
int main(void)
{
    char c,s[20],*p;
    int a=1234,*i;
    float f=3.141592653589;
    double x=0.12345678987654321;
    p="Howdoyoudo";
    strcpy(s,"Hello,Comrade");
    *i=12;
    c='\x41';
    //printf("a=%d\n",a);/*������ʮ��������a=1234*/
    //printf("a=%6d\n",a);/*������6λʮ������a=1234*/
    //printf("a=%06d\n",a);/*������6λʮ������a=001234*/
    //printf("a=%2d\n",a);/*a����2λ,��ʵ��ֵ���a=1234*/
    //printf("*i=%4d\n",*i);/*���4λʮ��������*i=12*/
    //printf("*i=%-4d\n",*i);/*��������4λʮ��������*i=12*/
    //printf("i=%p\n",i);/*�����ַi=06E4*/
    //printf("f=%f\n",f);/*���������f=3.141593*/
    //printf("f=%6.4f\n",f);/*���6λ����С�����4λ�ĸ�����f=3.1416*/
    //printf("x=%lf\n",x);/*�����������x=0.123457*/
    //printf("x=%18.16lf\n",x);/*���18λ����С�����16λ�ĳ�����
    //��x=0.1234567898765432*/
    //printf("c=%c\n",c);/*����ַ�c=A*/
    //printf("c=%x\n",c);/*����ַ���ASCII��ֵc=41*/
    //printf("s[]=%s\n",s);/*��������ַ���s[]=Hello,Comrade*/
    //printf("s[]=%6.9s\n",s);/*������9���ַ����ַ���s[]=Hello,Co*/
    //printf("s=%p\n",s);/*��������ַ������ַ���ַs=0060FEE3*/
    //printf("*p=%s\n",p);/*���ָ���ַ���p=Howdoyoudo*/
    //printf("p=%p\n",p);/*���ָ���ֵp=0194*/
    getch();
    return 0;.
}