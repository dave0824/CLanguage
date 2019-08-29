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
}linklist;

void input(linklist *head,int);
void output(linklist *head,int);
void fcfs(linklist *head,int n);
void insertSort(linklist *head, int );
void startSort(linklist *head,int n);
void show(linklist *head,int n);

//�������ܣ���������
void input(linklist* head,int n)
{
    FILE *fp;
    fp = fopen("dataps.txt", "rt+");
    int i=1;
    printf("������%d�����̵ģ�\n",n);
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ���ȼ�\n");
    while(i<=n){
        fscanf(fp, "%d%s%d:%2d%d%d",&head[i].id,head[i].name,&head[i].arrive.hour,&head[i].arrive.min,&head[i].zx,&head[i].grade);
        head[i].flag=1;
        printf("%-6d%-3s%4d:%02d%7d%16d\n",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min,head[i].zx,head[i].grade);
        i++;
    }
    fclose(fp);
}

void show(linklist *head,int n)
{
    int i=1;
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ���ȼ�  flag\n");
        while(i<=n){
        printf("%-6d%-3s%4d:%02d%7d%16d%16d\n",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min,head[i].zx,head[i].grade,head[i].flag);
        i++;
    };

}

//�������ܣ������������
void insertSort(linklist *head,int n)
{

  int i,j;
  linklist temp;
  printf("**********************************\n");
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
int select(linklist* head,time finish,int n)
{
    int i=2;
    linklist ps;//���ڱȽ�
    int cnt=1;
    int max=0;//����һ����С�����ȼ�
    while(i<=n)
    {
        if((head[i].arrive.hour<finish.hour&&head[i].flag==1&&head[i].grade>max)||(head[i].arrive.hour==finish.hour&&head[i].arrive.min<=finish.min&&head[i].flag==1&&head[i].grade>max))
        {
            cnt=i;
            printf("i======%d\n",i);
            max=head[cnt].grade;
        }
        i++;
    }
        head[cnt].flag=0;
        printf("max==%d\n",max);
        printf("head[%d].name=%s\n",cnt,head[cnt].name);
        return cnt;
}

void finishtimecount(linklist* t)
{
        (*t).finish.min = (*t).start.min + (*t).zx;
        if((*t).finish.min >= 60){
            (*t).finish.hour = (*t).start.hour + (*t).finish.min/60;
            (*t).finish.min = (*t).finish.min % 60;
        }
        else
            (*t).finish.hour = (*t).start.hour;
        (*t).zz = ((*t).finish.hour - (*t).arrive.hour) * 60 + (*t).finish.min - (*t).arrive.min;
        (*t).zzxs = (float)(*t).zz / (*t).zx;
        printf("s.time: %d:%d\n",(*t).finish.hour,(*t).finish.min);
}
//�������ܣ�ʵ��FCFS�㷨
void fcfs(linklist* head,int n)
{
    int i=1;
    int cnt=0;//��¼����ֵ
    int j=0;//��¼��һ��ֵ
    while(i<=n){
        if(i==1){
            head[i].start.hour = head[i].arrive.hour;
            head[i].start.min = head[i].arrive.min;
            finishtimecount(&head[i]);
            printf("head[%d].time==%d:%d\n",i,head[i].finish.hour,head[i].finish.min);
            j=i;
            head[i].flag=0;
            cnt=select(head,head[i].finish,n);
        }
        else{
            head[cnt].start.hour = head[j].finish.hour;
            head[cnt].start.min = head[j].finish.min;
            finishtimecount(&head[cnt]);
            j=cnt;
            cnt=select(head,head[cnt].finish,n);
        }
        printf("**************************��������%s\n",head[cnt].name);
        i++;
    }
}

//�������ܣ��������
void output(linklist* head,int n)
{
    float count1 = 0, count2 = 0;
    int  i=1;
    printf("ģ�����FCFS���ȹ�����������\n");
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ���ȼ�          ");
    printf("��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ����\n");
    while(i<=n){
        printf("%-6d%-3s%4d:%02d%7d%16d",head[i].id,head[i].name,head[i].arrive.hour,head[i].arrive.min, head[i].zx,head[i].grade);
        printf("%16d:%02d%6d:%02d%9d%17.2f\n",head[i].start.hour, head[i].start.min, head[i].finish.hour,head[i].finish.min,head[i].zz, head[i].zzxs);
        count1 = count1 + head[i].zz;
        count2 = count2 + head[i].zzxs;
        i++;
    }
    printf("\n");
    printf("ϵͳƽ����תʱ��Ϊ:%.2f\n",count1/n);
    printf("ϵͳ��Ȩƽ����תʱ��Ϊ:%.2f\n", count2/n);
}
int main()
{
    int n;
    printf("�������������");
    scanf("%d",&n);
    linklist head[n+1];
    input(head,n);
    insertSort(head,n);
    show(head,n);
    fcfs(head,n);
    startSort(head,n);
    output(head,n);
    return 0;
}
