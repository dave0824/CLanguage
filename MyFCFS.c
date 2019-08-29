#include <stdio.h>
#include <stdlib.h>
//���̵����㷨
typedef struct  data
{
    int hour;
    int min;
}time;
typedef struct node
{
    int id;//���
    char name[20];//������
    time arrive;//�����������ʱ��
    int zx;//ִ��ʱ��
    time start;//��ʼʱ��
    time finish;//���ʱ��
    int zz;//��תʱ��
    float zzxs;//��Ȩ��תϵ��
    struct node* next;
}linklist;

void input(linklist *phead);
void output(linklist *phead);
void fcfs(linklist *phead);
inline void insertSort(linklist *phead, linklist *s);

//�������ܣ���������
void input(linklist* phead)
{
    FILE *fp;
    fp = fopen("data.txt", "rt+");
    int n;
    printf("�������������");
    scanf("%d",&n);
    printf("������%d�����̵ģ�\n",n);
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ�\n");
    while(n--){
        linklist *s =(linklist*)malloc(sizeof(linklist));
        fscanf(fp, "%d%s%d:%2d%d",&s->id,s->name,&s->arrive.hour,&s->arrive.min,&s->zx);
        printf("%-6d%-3s%4d:%02d%7d\n",s->id,s->name,s->arrive.hour,s->arrive.min, s->zx);
        insertSort(phead, s);
    };
    fclose(fp);
}

//�������ܣ������������
void insertSort(linklist *phead,linklist *s)
{
    linklist *p = phead;
    linklist *pre = p;
    if(!p->next){
        s->next = p->next;
        p->next = s;
        return;
    }
    while(p->next){
        pre = p;
        p = p->next;
        if(p->arrive.hour > s->arrive.hour||(p->arrive.hour == s->arrive.hour && p->arrive.min > s->arrive.min)){
            s->next = p;
            pre->next = s;
            return;
        }
    }
    s->next = NULL;
    p->next = s;
}
//�������ܣ�ʵ��FCFS�㷨
void fcfs(linklist* phead)
{
    linklist* t = phead;
    if(t->next == NULL || t->next->next == NULL)
        return;
    linklist *pre = phead;
    while(t->next){
        pre = t;
        t = t->next;
        if(pre == phead){
            t->start.hour = t->arrive.hour;
            t->start.min = t->arrive.min;
        }
        else{
            t->start.hour = pre->finish.hour;
            t->start.min = pre->finish.min;
        }
        t->finish.min = t->start.min + t->zx;
        if(t->finish.min >= 60){
            t->finish.hour = t->start.hour + t->finish.min/60;
            t->finish.min = t->finish.min % 60;
        }
        else
            t->finish.hour = t->start.hour;
        t->zz = (t->finish.hour - t->arrive.hour) * 60 + t->finish.min - t->arrive.min;
        t->zzxs = (float)t->zz / t->zx;

    }
}

//�������ܣ��������
void output(linklist* phead)
{
    linklist* p = phead;
    float count1 = 0, count2 = 0;
    int n = 0;
    printf("ģ�����FCFS���ȹ�����������\n");
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ�");
    printf("��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ����\n");
    while(p->next){
        p = p->next;
        printf("%-6d%-3s%4d:%02d%7d",p->id,p->name,p->arrive.hour,p->arrive.min, p->zx);
        printf("%16d:%02d%6d:%02d%9d%17.2f\n",p->start.hour, p->start.min, p->finish.hour,p->finish.min,p->zz, p->zzxs);
        count1 = count1 + p->zz;
        count2 = count2 + p->zzxs;
        n++;
    }
    printf("\n");
    printf("ϵͳƽ����תʱ��Ϊ��                                   %.2f\n",count1/n);
    printf("ϵͳ��Ȩƽ����תʱ��Ϊ��                                                 %.2f\n", count2/n);
}
int main()
{
    linklist *head =(linklist*)malloc(sizeof(linklist));
    head->next = NULL;
    input(head);
    fcfs(head);
    output(head);
    return 0;
}
