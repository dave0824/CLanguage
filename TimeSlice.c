#include <stdio.h>
#include <stdlib.h>
//进程时间片调度算法
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
    int grade;//优先级
    int zz;//周转时间
    float zzxs;//带权周转系数
}linklist;

void input(linklist *head,int);
void output(linklist *head,int);
void TimeSlice(linklist* head,int n,int tote);
void arriveSort(linklist *head, int );
void startSort(linklist *head,int n);
void show(linklist *head,int n);
int select(linklist* head,time finish,int n,int last);
int executeTime(linklist* head,int n);

//函数功能：数据输入
void input(linklist* head,int n)
{
    FILE *fp;
    fp = fopen("datatime.txt", "rt+");
    int i=1;
    printf("请输入%d个进程的：\n",n);
    printf("ID号 名字 到达时间 执行时间（分钟） 优先级\n");
    while(i<=n){
        fscanf(fp, "%d%s%d:%2d%d%d",&head[i].id,head[i].name,&head[i].arrive.hour,&head[i].arrive.min,&head[i].zx,&head[i].grade);
        printf("%-6d%-3s%4d:%02d%7d%16d\n",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min,head[i].zx,head[i].grade);
        head[i].zz=0;
        head[i].zzxs=0;
        head[i].finish.hour=0;
        head[i].finish.min=0;
        head[i].start.hour=0;
        head[i].start.min=0;
        i++;
    }
    fclose(fp);
}

void show(linklist *head,int n)
{
    int i=1;
    printf("ID号 名字 到达时间 执行时间（分钟） 优先级\n");
        while(i<=n){
        printf("%-6d%-3s%4d:%02d%7d%16d\n",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min,head[i].zx,head[i].grade);
        i++;
    };
    printf("*****************************************************************\n");

}

int executeTime(linklist* head,int n)
{
    int i;
    int tote=0;//记录总用时
    for(i=1;i<=n;i++)
    {
        tote+=head[i].zx;
    }
    printf("\ncpu需要的总执行时间:%d\n\n",tote);
    return tote;
}

//根据到达时间排序
void arriveSort(linklist *head,int n)
{

  int i,j;
  linklist temp;
  printf("*****************************************************************\n");
  for(i=1;i<=n;i++)
  {
     for(j=i+1;j<=n;j++)
     {
         if((head[i].arrive.hour>head[j].arrive.hour)||(head[i].arrive.hour==head[j].arrive.hour&&head[i].arrive.min>head[j].arrive.min))
            {
                temp=head[i];
                head[i]=head[j];
                head[j]=temp;
            }
     }
  }
}

//根据启动时间排序
void startSort(linklist *head,int n)
{

  int i,j;
  linklist temp;
  for(i=1;i<=n;i++)
  {
     for(j=i+1;j<=n;j++)
     {
         if((head[i].start.hour>head[j].start.hour)||(head[i].start.hour==head[j].start.hour&&head[i].start.min>head[j].start.min))
            {
                temp=head[i];
                head[i]=head[j];
                head[j]=temp;
            }
     }
  }
}
//选择一个优先级最大的
int select(linklist* head,time finish,int n,int last)
{
    int i=1;
    linklist ps;//用于比较
    int cnt=last;
    int max=0;//定义一个最小的优先级
    while(i<=n)
    {
        if((i!=last&&head[i].arrive.hour<finish.hour&&head[i].zx>0&&head[i].grade>max)||(i!=last&&head[i].arrive.hour==finish.hour&&head[i].arrive.min<=finish.min&&head[i].zx>0&&head[i].grade>max))
        {
            cnt=i;
            max=head[cnt].grade;
        }
        i++;
    }
    printf("\n\n选择了head[%d].%s\n",cnt,head[cnt].name);
    return cnt;
}
//完成时间统计
void finishtimecount(linklist* t,int cputime)
{
        (*t).finish.min = (*t).start.min + cputime;
        if((*t).finish.min >= 60){
            (*t).finish.hour = (*t).start.hour + (*t).finish.min/60;
            (*t).finish.min = (*t).finish.min % 60;
        }
        else
            (*t).finish.hour = (*t).start.hour;
        (*t).zz = ((*t).finish.hour - (*t).arrive.hour) * 60 + (*t).finish.min - (*t).arrive.min;
        (*t).zzxs = (float)(*t).zz / (*t).zx;
}
//函数功能：实现时间片调度算法
void TimeSlice(linklist* head,int n,int tote)
{
    int i=0;
    int time=0;//记录执行时间
    int jishu=1;//计数输出
    int cnt=0;//记录返回值
    int j=0;//记录上一个值
    int cputime;//定义cpu周转时间
    //记录第一轮时间片
    printf("请输入cpu运行时间片周期：");
    scanf("%d",&cputime);
     {
        head[1].start.hour = head[1].arrive.hour;
        head[1].start.min = head[1].arrive.min;
            if(head[1].zx>=cputime)
            {
                finishtimecount(&head[1],cputime);
                head[1].zx-=cputime;
                i+=cputime;
            }
            else
            {
                finishtimecount(&head[1],head[1].zx);
                i+=head[1].zx;
                head[1].zx=0;
            }
            j=1;
            time=i;
            printf("/n****第%d轮执行时间：%d，剩余总时间：%d  *****\n",jishu++,time,tote-time);
            output(head,n);
            cnt=select(head,head[1].finish,n,1);
     }
    while(i<tote){
            head[cnt].start.hour = head[j].finish.hour;
            head[cnt].start.min = head[j].finish.min;
            time=i;
            if(head[cnt].zx>=cputime)
            {
                finishtimecount(&head[cnt],cputime);
                head[cnt].zx-=cputime;
                i+=cputime;
            }
            else
            {
                finishtimecount(&head[cnt],head[cnt].zx);
                i+=head[cnt].zx;
                head[cnt].zx=0;
            }
            j=cnt;

    printf("/n****第%d轮执行时间：%d，剩余总时间：%d  *****\n",jishu++,i-time,tote-i);
    output(head,n);
    cnt=select(head,head[cnt].finish,n,cnt);
    }
}

//函数功能：数据输出
void output(linklist* head,int n)
{
    float count1 = 0, count2 = 0;
    int  i=1;
    printf("ID号 名字 到达时间 （剩余）执行时间 优先级          ");
    printf("开始时间 完成时间 周转时间（分钟）带权周转时间（系数）\n");
    while(i<=n){
        printf("%-6d%-3s%4d:%02d%7d%16d",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min, head[i].zx,head[i].grade);
        printf("%16d:%02d%6d:%02d%9d%17.2f\n",head[i].start.hour, head[i].start.min, head[i].finish.hour,head[i].finish.min,head[i].zz, head[i].zzxs);
        count1 = count1 + head[i].zz;
        count2 = count2 + head[i].zzxs;
        i++;
    }
    printf("系统平均周转时间为:%.2f\n",count1/n);
    printf("系统带权平均周转时间为:%.2f\n", count2/n);
}
int main()
{
    int n;
    int tote;//记录总时间
    printf("请输入进程数：");
    scanf("%d",&n);
    linklist head[n+1];
    input(head,n);
    arriveSort(head,n);
    show(head,n);
    tote=executeTime(head,n);
    TimeSlice(head,n,tote);
    return 0;
}
