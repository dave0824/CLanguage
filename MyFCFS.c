#include <stdio.h>
#include <stdlib.h>
//进程调度算法
typedef struct  data
{
    int hour;
    int min;
}time;
typedef struct node
{
    int id;//编号
    char name[20];//进程名
    time arrive;//到达就绪队列时间
    int zx;//执行时间
    time start;//开始时间
    time finish;//完成时间
    int zz;//周转时间
    float zzxs;//带权周转系数
    struct node* next;
}linklist;

void input(linklist *phead);
void output(linklist *phead);
void fcfs(linklist *phead);
inline void insertSort(linklist *phead, linklist *s);

//函数功能：数据输入
void input(linklist* phead)
{
    FILE *fp;
    fp = fopen("data.txt", "rt+");
    int n;
    printf("请输入进程数：");
    scanf("%d",&n);
    printf("请输入%d个进程的：\n",n);
    printf("ID号 名字 到达时间 执行时间（分钟）\n");
    while(n--){
        linklist *s =(linklist*)malloc(sizeof(linklist));
        fscanf(fp, "%d%s%d:%2d%d",&s->id,s->name,&s->arrive.hour,&s->arrive.min,&s->zx);
        printf("%-6d%-3s%4d:%02d%7d\n",s->id,s->name,s->arrive.hour,s->arrive.min, s->zx);
        insertSort(phead, s);
    };
    fclose(fp);
}

//函数功能：链表插入排序
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
//函数功能：实现FCFS算法
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

//函数功能：数据输出
void output(linklist* phead)
{
    linklist* p = phead;
    float count1 = 0, count2 = 0;
    int n = 0;
    printf("模拟进程FCFS调度过程输出结果：\n");
    printf("ID号 名字 到达时间 执行时间（分钟）");
    printf("开始时间 完成时间 周转时间（分钟）带权周转时间（系数）\n");
    while(p->next){
        p = p->next;
        printf("%-6d%-3s%4d:%02d%7d",p->id,p->name,p->arrive.hour,p->arrive.min, p->zx);
        printf("%16d:%02d%6d:%02d%9d%17.2f\n",p->start.hour, p->start.min, p->finish.hour,p->finish.min,p->zz, p->zzxs);
        count1 = count1 + p->zz;
        count2 = count2 + p->zzxs;
        n++;
    }
    printf("\n");
    printf("系统平均周转时间为：                                   %.2f\n",count1/n);
    printf("系统带权平均周转时间为：                                                 %.2f\n", count2/n);
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
