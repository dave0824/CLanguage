#include<stdio.h>
#include<math.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
struct booklist
{
    char name[20];//图书名
    char author[20];//作者姓名
    char publisher[20];//出版社
    char date[20];//出版日期
    float price;//图书价格
    struct booklist *next;//定义指针域
};
//建立头结点
struct booklist * create_node()
{
    struct booklist * head;
    head=(struct booklist *)malloc(sizeof(struct booklist));
    if(head==NULL)
    {
        printf("分配空间失败\n");
        exit(0);
    }
    head->next=NULL;
    return head;
};
//插入
void insert (struct booklist*head)
{
    struct booklist *p,*s;
    char flag='Y';
    p=head;
    while(p->next!=NULL)
    {
        p=p->next;
    }
        s=(struct booklist*)malloc(sizeof(struct booklist));
        printf("请输入图书名：\n");
        scanf("%s",s->name);
        printf("请输入作者姓名:\n");
        scanf("%s",s->author);
        printf("请输入出版社:\n");
        scanf("%s",s->publisher);
        printf("请输入出版日期：\n");
        scanf("%s",s->date);
        printf("请输入图书价格：\n");
        scanf("%f",&s->price);
        p->next=s;
        p=s;
        s->next=NULL;
        printf("添加成功!\n");
    return ;
}
//遍历
void output(struct booklist * head)
{
    struct booklist *p;
    p=head->next;
    while(p!=NULL)
    {
        printf("%s  ",p->name);
        printf("%s  ",p->author);
        printf("%s  ",p->publisher);
        printf("%s  ",p->date);
        printf("%f  ",p->price);
        printf("\n");
        p=p->next;
    }
    return;
}
//删除
void deletebook(struct booklist *head)
{
    struct booklist *p,*k;
    int cnt=0;
    char temp[20];
    p=k=head;
    printf("请输入要删除的图书名:\n");
    scanf("%s",&temp);
    while(p!=NULL)
    {
        if(strcmp(p->name,temp)==0)
        {
            cnt++;
            break;
        }
            p=p->next;
    }
    if(cnt==0)
    {
            printf("您输入的书名不存在：\n");
    }
    else
    {
        for(;k->next!=p;)
        {
            k=k->next;
        }
        k->next=p->next;
        free(p);
        printf("删除成功！\n");
    }
        return;
}
//查找
void seekbook(struct booklist *head)
{
    struct booklist *p;
    char temp[20];
    p=head;
    printf("请输入要查找的图书名：\n");
    scanf("%s",&temp);
    while(p!=NULL)
    {
        if(strcmp(temp,p->name)==0)
        {
            printf("%s  ",p->name);
            printf("%s  ",p->author);
            printf("%s  ",p->publisher);
            printf("%s  ",p->date);
            printf("%f  ",&p->price);
            printf("\n");
            return;
        }
        p=p->next;
    }
    printf("您输入的书名不存在\n");
        return;
}
int main()
{
    struct booklist *head;
    head=create_node();
    int a;
    printf("欢迎使用图书管理系统\n");
    for(;;)
    {
        printf("请选择菜单\n");
        printf("(1)图书信息录入\n");
        printf("(2)图书信息浏览\n");
        printf("(3)图书信息查询\n");
        printf("(4)图书信息删除\n");
        scanf("%d",&a);
        if(a==1)
            insert(head);
        else if(a==2)
            output(head);
        else if(a==3)
            seekbook(head);
        else if(a==4)
            deletebook(head);
        else
        {
            printf("输入有误，请重新输入：\n");
            continue;
        }
    }
    //return;
}

