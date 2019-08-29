#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define maxsize 100
#include<stdlib.h>
#define N 10 
typedef struct
{
    char name[20];//图书名字
    char author[20];//作者姓名
    float price;//图书价格
}Book;
typedef struct
{
    Book elem[N];
    int length;
}sqlist;
//构造一个空的顺序表
void createlist(sqlist *l)
{
  // l->elem=(Book*)malloc(maxsize*sizeof(Book));
    if(!l)
   {
       printf("内存分配空间失败");
       //printf("-1");
	   exit(-1);
   }
    l->length=0;
    return ;
}
//输入图书信息
void input(sqlist*l)
{
    int i,num;
    printf("请输入图书的数量；\n");
    scanf("%d",&num);
    Book book;
    for(i=0;i<num;i++)
    {
        printf("请输入第%d本书的名字：\n",i+1);
        scanf("%s",book.name);
        
        strcpy(l->elem[i].name,book.name);
        
        printf("请输入第%d本书的作者：\n",i+1);
        scanf("%s",book.author);
       
	    strcpy(l->elem[i].author,book.author);
        printf("请输入第%d本书的价格：\n",i+1);
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
//插入图书
void insert(sqlist *l)
{
   Book book;
   int temp,i;
   printf("请输入插入的位置：");
   scanf("%d",&temp);
   if((temp>=1&&temp<=l->length+1)&&l->length<maxsize)
   {
       for(i=l->length-1;i>=(temp-1);i--)
       {
           l->elem[i+1]=l->elem[i];
       }
        printf("请输入插入书的名字：\n");
        scanf("%s",book.name );
        strcpy(l->elem[i+1].name,book.name );
        printf("请输入插入书的作者：\n");
        scanf("%s",book.author);
        strcpy(l->elem[i+1].author,book.author);
        printf("请输入插入书的价格：\n",i+1);
        scanf("%f",&l->elem[i+1].price);
        l->length++;
        printf("插入成功\n");
   }
   else
        printf("插入失败\n");
   return;
}
   //查找
void seek(sqlist*l)
{
       int i;
       printf("请输入要查找的图书序号");
       scanf("%d",&i);
       if(i<1||i>l->length)
        printf("图书不存在\n");
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
//删除
void deletebook(sqlist* l)
{
    int i,demp;
    printf("请输入要删除的图书序号：\n");
    scanf("%d",&demp);
    if(demp<1||demp>=l->length)
        printf("要删除的图书不存在！\n");
    else
    {
       for(i=1;i<=demp;i++)
       {
            l->elem[i-1]=l->elem[i];
       }
       l->length--;
        printf("删除成功！\n");
    }
}
int main()
{
   sqlist l;
   createlist(&l);
   printf("欢迎来到图书管理系统，请先录入图书!\n");
   input(&l);
   int a;
   for(;;)
   {
        printf("请选择功能：\n");
        printf("(1)图书信息插入\n");
        printf("(2)图书信息浏览\n");
        printf("(3)图书信息查询\n");
        printf("(4)图书信息删除\n");
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
            printf("输入有误，请重新输入：\n");
            continue;
        }
   }
   return 0;
}

