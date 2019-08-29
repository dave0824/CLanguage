#include<stdio.h>
#include<math.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
struct booklist
{
    char name[20];//ͼ����
    char author[20];//��������
    char publisher[20];//������
    char date[20];//��������
    float price;//ͼ��۸�
    struct booklist *next;//����ָ����
};
//����ͷ���
struct booklist * create_node()
{
    struct booklist * head;
    head=(struct booklist *)malloc(sizeof(struct booklist));
    if(head==NULL)
    {
        printf("����ռ�ʧ��\n");
        exit(0);
    }
    head->next=NULL;
    return head;
};
//����
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
        printf("������ͼ������\n");
        scanf("%s",s->name);
        printf("��������������:\n");
        scanf("%s",s->author);
        printf("�����������:\n");
        scanf("%s",s->publisher);
        printf("������������ڣ�\n");
        scanf("%s",s->date);
        printf("������ͼ��۸�\n");
        scanf("%f",&s->price);
        p->next=s;
        p=s;
        s->next=NULL;
        printf("��ӳɹ�!\n");
    return ;
}
//����
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
//ɾ��
void deletebook(struct booklist *head)
{
    struct booklist *p,*k;
    int cnt=0;
    char temp[20];
    p=k=head;
    printf("������Ҫɾ����ͼ����:\n");
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
            printf("����������������ڣ�\n");
    }
    else
    {
        for(;k->next!=p;)
        {
            k=k->next;
        }
        k->next=p->next;
        free(p);
        printf("ɾ���ɹ���\n");
    }
        return;
}
//����
void seekbook(struct booklist *head)
{
    struct booklist *p;
    char temp[20];
    p=head;
    printf("������Ҫ���ҵ�ͼ������\n");
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
    printf("�����������������\n");
        return;
}
int main()
{
    struct booklist *head;
    head=create_node();
    int a;
    printf("��ӭʹ��ͼ�����ϵͳ\n");
    for(;;)
    {
        printf("��ѡ��˵�\n");
        printf("(1)ͼ����Ϣ¼��\n");
        printf("(2)ͼ����Ϣ���\n");
        printf("(3)ͼ����Ϣ��ѯ\n");
        printf("(4)ͼ����Ϣɾ��\n");
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
            printf("�����������������룺\n");
            continue;
        }
    }
    //return;
}

