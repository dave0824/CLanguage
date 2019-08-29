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
    int grade;//���ȼ�
    int zz;//��תʱ��
    float zzxs;//��Ȩ��תϵ��
    int flag;//��ǽ���Ƿ����й�
    struct node* next;
}linklist;

void input(linklist *phead);
void output(linklist *phead);
linklist* fcfs(linklist *phead);
inline void insertSort(linklist *phead, linklist *s);

//�������ܣ���������
void input(linklist* phead)
{
    linklist* p=phead;
    FILE *fp;
    fp = fopen("dataps.txt", "rt+");
    int n;
    printf("�������������");
    scanf("%d",&n);
    printf("������%d�����̵ģ�\n",n);
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ���ȼ�\n");
    while(n--){
        linklist *s =(linklist*)malloc(sizeof(linklist));
        fscanf(fp, "%d%s%d:%2d%d%d",&s->id,s->name,&s->arrive.hour,&s->arrive.min,&s->zx,&s->grade);
        s->flag=1;
        printf("%-6d%-3s%4d:%02d%7d%16d\n",s->id,s->name,s->arrive.hour,s->arrive.min, s->zx,s->grade);
        insertSort(phead,s);
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
//ѡ��һ�����ȼ�����
linklist* select(linklist* phead,time finish)
{
    linklist* p=phead;
    linklist* pre=NULL;
    linklist ps;//���ڱȽ�
    int max=0;//����һ����С�����ȼ�
    while(p->next)
    {
        p=p->next;
        if(p->arrive.hour<finish.hour&&p->flag==1&&p->grade>max||(p->arrive.hour==finish.hour&&p->arrive.min<=finish.min&&p->flag==1&&p->grade>max))
        {
            pre=p;
            max=pre->grade;
        }
    }
        pre->flag=0;
        printf("pre.name=%s\n",pre->name);
        return pre;
}

void finishtimecount(linklist* t)
{
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
//�������ܣ�ʵ��FCFS�㷨
linklist* fcfs(linklist* phead)
{
    linklist* t = phead;
    linklist* t2 = phead;
    //if(t->next == NULL || t->next->next == NULL)
       // return;
    linklist *pre = phead;
    linklist *head =(linklist*)malloc(sizeof(linklist));//��¼������Ľṹ����
    head->next=NULL;
    linklist *prn=phead;
    linklist *pd=head;
    int i=0;
    while(t2->next)
    {
        t2=t2->next;
        i++;
        printf("**************%d\n",i);
    }
    while(i--){
        pre=prn;
        if(prn == phead){
            prn->start.hour = prn->arrive.hour;
            prn->start.min = prn->arrive.min;
            finishtimecount(prn);
            /*t->next=prn;
            prn=t;
            prn=prn->next;*/
            prn=select(phead,prn->finish);
        }
        else{
            prn->start.hour = pre->finish.hour;
            prn->start.min = pre->finish.min;
            finishtimecount(prn);
            prn=select(phead,prn->finish);
        }
        prn->next=pd->next;
        pd=prn;
        printf("**************************��������%s\n",prn->name);
        pd=pd->next;
    }
    return head;
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
    head=fcfs(head);
    output(head);
    return 0;
}
