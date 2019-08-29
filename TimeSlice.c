#include <stdio.h>
#include <stdlib.h>
//����ʱ��Ƭ�����㷨
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
}linklist;

void input(linklist *head,int);
void output(linklist *head,int);
void TimeSlice(linklist* head,int n,int tote);
void arriveSort(linklist *head, int );
void startSort(linklist *head,int n);
void show(linklist *head,int n);
int select(linklist* head,time finish,int n,int last);
int executeTime(linklist* head,int n);

//�������ܣ���������
void input(linklist* head,int n)
{
    FILE *fp;
    fp = fopen("datatime.txt", "rt+");
    int i=1;
    printf("������%d�����̵ģ�\n",n);
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ���ȼ�\n");
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
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ���ȼ�\n");
        while(i<=n){
        printf("%-6d%-3s%4d:%02d%7d%16d\n",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min,head[i].zx,head[i].grade);
        i++;
    };
    printf("*****************************************************************\n");

}

int executeTime(linklist* head,int n)
{
    int i;
    int tote=0;//��¼����ʱ
    for(i=1;i<=n;i++)
    {
        tote+=head[i].zx;
    }
    printf("\ncpu��Ҫ����ִ��ʱ��:%d\n\n",tote);
    return tote;
}

//���ݵ���ʱ������
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

//��������ʱ������
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
//ѡ��һ�����ȼ�����
int select(linklist* head,time finish,int n,int last)
{
    int i=1;
    linklist ps;//���ڱȽ�
    int cnt=last;
    int max=0;//����һ����С�����ȼ�
    while(i<=n)
    {
        if((i!=last&&head[i].arrive.hour<finish.hour&&head[i].zx>0&&head[i].grade>max)||(i!=last&&head[i].arrive.hour==finish.hour&&head[i].arrive.min<=finish.min&&head[i].zx>0&&head[i].grade>max))
        {
            cnt=i;
            max=head[cnt].grade;
        }
        i++;
    }
    printf("\n\nѡ����head[%d].%s\n",cnt,head[cnt].name);
    return cnt;
}
//���ʱ��ͳ��
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
//�������ܣ�ʵ��ʱ��Ƭ�����㷨
void TimeSlice(linklist* head,int n,int tote)
{
    int i=0;
    int time=0;//��¼ִ��ʱ��
    int jishu=1;//�������
    int cnt=0;//��¼����ֵ
    int j=0;//��¼��һ��ֵ
    int cputime;//����cpu��תʱ��
    //��¼��һ��ʱ��Ƭ
    printf("������cpu����ʱ��Ƭ���ڣ�");
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
            printf("/n****��%d��ִ��ʱ�䣺%d��ʣ����ʱ�䣺%d  *****\n",jishu++,time,tote-time);
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

    printf("/n****��%d��ִ��ʱ�䣺%d��ʣ����ʱ�䣺%d  *****\n",jishu++,i-time,tote-i);
    output(head,n);
    cnt=select(head,head[cnt].finish,n,cnt);
    }
}

//�������ܣ��������
void output(linklist* head,int n)
{
    float count1 = 0, count2 = 0;
    int  i=1;
    printf("ID�� ���� ����ʱ�� ��ʣ�ִࣩ��ʱ�� ���ȼ�          ");
    printf("��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ����\n");
    while(i<=n){
        printf("%-6d%-3s%4d:%02d%7d%16d",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min, head[i].zx,head[i].grade);
        printf("%16d:%02d%6d:%02d%9d%17.2f\n",head[i].start.hour, head[i].start.min, head[i].finish.hour,head[i].finish.min,head[i].zz, head[i].zzxs);
        count1 = count1 + head[i].zz;
        count2 = count2 + head[i].zzxs;
        i++;
    }
    printf("ϵͳƽ����תʱ��Ϊ:%.2f\n",count1/n);
    printf("ϵͳ��Ȩƽ����תʱ��Ϊ:%.2f\n", count2/n);
}
int main()
{
    int n;
    int tote;//��¼��ʱ��
    printf("�������������");
    scanf("%d",&n);
    linklist head[n+1];
    input(head,n);
    arriveSort(head,n);
    show(head,n);
    tote=executeTime(head,n);
    TimeSlice(head,n,tote);
    return 0;
}
