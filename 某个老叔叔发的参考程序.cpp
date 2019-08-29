#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define maxsize 100
#include<stdlib.h>
#define N 10 
typedef struct
{
    char name[20];//ͼ������
    char author[20];//��������
    float price;//ͼ��۸�
}Book;
typedef struct
{
    Book elem[N];
    int length;
}sqlist;
//����һ���յ�˳���
void createlist(sqlist *l)
{
  // l->elem=(Book*)malloc(maxsize*sizeof(Book));
    if(!l)
   {
       printf("�ڴ����ռ�ʧ��");
       //printf("-1");
	   exit(-1);
   }
    l->length=0;
    return ;
}
//����ͼ����Ϣ
void input(sqlist*l)
{
    int i,num;
    printf("������ͼ���������\n");
    scanf("%d",&num);
    Book book;
    for(i=0;i<num;i++)
    {
        printf("�������%d��������֣�\n",i+1);
        scanf("%s",book.name);
        
        strcpy(l->elem[i].name,book.name);
        
        printf("�������%d��������ߣ�\n",i+1);
        scanf("%s",book.author);
       
	    strcpy(l->elem[i].author,book.author);
        printf("�������%d����ļ۸�\n",i+1);
        scanf("%f",&l->elem[i].price);
        l->length++;
    }
    return;
}
void output(sqlist* l)
{
    int i;
    for(i=0;i<l->length;i++)
    {
        printf("%d  ",i+1);
        printf("%s  ",l->elem[i].name);
        printf("%s  ",l->elem[i].author);
        printf("%f  ",l->elem[i].price);
        printf("\n");
    }
}
//����ͼ��
void insert(sqlist *l)
{
   Book book;
   int temp,i;
   printf("����������λ�ã�");
   scanf("%d",&temp);
   if((temp>=1&&temp<=l->length+1)&&l->length<maxsize)
   {
       for(i=l->length-1;i>=(temp-1);i--)
       {
           l->elem[i+1]=l->elem[i];
       }
        printf("���������������֣�\n");
        scanf("%s",book.name );
        strcpy(l->elem[i+1].name,book.name );
        printf("���������������ߣ�\n");
        scanf("%s",book.author);
        strcpy(l->elem[i+1].author,book.author);
        printf("�����������ļ۸�\n",i+1);
        scanf("%f",&l->elem[i+1].price);
        l->length++;
        printf("����ɹ�\n");
   }
   else
        printf("����ʧ��\n");
   return;
}
   //����
void seek(sqlist*l)
{
       int i;
       printf("������Ҫ���ҵ�ͼ�����");
       scanf("%d",&i);
       if(i<1||i>l->length)
        printf("ͼ�鲻����\n");
       else
       {
        printf("%d  ",i);
        printf("%s  ",l->elem[i-1].name);
        printf("%s  ",l->elem[i-1].author);
        printf("%f  ",l->elem[i-1].price);
        printf("\n");
       }
       return;
}
//ɾ��
void deletebook(sqlist* l)
{
    int i,demp;
    printf("������Ҫɾ����ͼ����ţ�\n");
    scanf("%d",&demp);
    if(demp<1||demp>=l->length)
        printf("Ҫɾ����ͼ�鲻���ڣ�\n");
    else
    {
       for(i=1;i<=demp;i++)
       {
            l->elem[i-1]=l->elem[i];
       }
       l->length--;
        printf("ɾ���ɹ���\n");
    }
}
int main()
{
   sqlist l;
   createlist(&l);
   printf("��ӭ����ͼ�����ϵͳ������¼��ͼ��!\n");
   input(&l);
   int a;
   for(;;)
   {
        printf("��ѡ���ܣ�\n");
        printf("(1)ͼ����Ϣ����\n");
        printf("(2)ͼ����Ϣ���\n");
        printf("(3)ͼ����Ϣ��ѯ\n");
        printf("(4)ͼ����Ϣɾ��\n");
        scanf("%d",&a);
        if(a==1)
            insert(&l);
        else if(a==2)
            output(&l);
        else if(a==3)
            seek(&l);
        else if(a==4)
            deletebook(&l);
        else
        {
            printf("�����������������룺\n");
            continue;
        }
   }
   return 0;
}

