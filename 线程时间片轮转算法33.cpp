#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 20
typedef struct data{
	int hour;
	int minute;
}time;

typedef struct node{
	int id; //���̱��
	char name[20];//������
	time arrive;//������е�ʱ��
	time start;//��ʼִ��ʱ��
	time finish;//ִ�н���ʱ��
	//time temp;//��ʱ�Ľ���ʱ��
	int remain;//ʣ�����ʱ��
	int optime;//ִ��ʱ��
	int ztime;//��תʱ��
	float weight;//��Ȩ��תϵ��
}List;

List list [N];
List temp [N];
int input();
void output(int num);
void sorttime(int num);
void outputtemp(int num);

int input(){
	FILE *fp=fopen("datafcfs.txt","rt+");
	int num;//������Ŀ
	printf("�����������Ŀ\n");
	scanf("%d",&num);
	printf("����ID	������	����ʱ��	ִ��ʱ��(��)    ʣ��ִ��ʱ��\n");
	int n=1;//��һ��λ�ò����κ�����
	while(n<=num){
		fscanf(fp, "%d%s%d:%2d%d",&list[n].id,list[n].name,&list[n].arrive.hour,&list[n].arrive.minute,&list[n].optime);
        //printf("\n%d\n",list[n].id);
        list[n].remain=list[n].optime;
		printf("%-6d%-5s%2d:%2d%7d%6d\n",list[n].id,list[n].name,list[n].arrive.hour,list[n].arrive.minute, list[n].optime,list[n].optime);
        n++;
	}
	fclose(fp);
	sorttime(num);
	//outputtemp(num);
	return num;
}

void sorttime(int num){
	int i,j;
	for(i=1;i<=num;i++){
		for(j=num;j>i;j--){
			if(list[i].arrive.hour>list[j].arrive.hour||
			(list[i].arrive.hour==list[j].arrive.hour)&&(list[i].arrive.minute>list[j].arrive.minute)){
				list[0]=list[i];
				list[i]=list[j];
				list[j]=list[0];
			}
		}
	}
}

void output(int num){

	int i=1;
	printf("ģ�����ʱ��Ƭ���ȹ�����������\n");
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ʣ��ִ��ʱ��");
    printf("   ��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ����\n");
	while(i<=num){
		printf("%-6d%-3s%4d:%02d%7d%6d",list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime,list[i].remain);
        printf("%16d:%02d%6d:%02d%9d%7.2f\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
		,list[i].finish.minute,list[i].ztime, list[i].weight);
		i++;
	}
}
void outputtemp(int num){
	int i=1;
	printf("ģ�����ʱ��Ƭ���ȹ�����������\n");
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ� ʣ��ִ��ʱ��");
    //printf("��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ����\n");
	while(i<=num){
		printf("\n%-6d%-3s%4d:%02d%7d%d6d\n",list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime,list[i].remain);
       // printf("%16d:%02d%6d:%02d%9d%7.2f\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
		//,list[i].finish.minute,list[i].ztime, list[i].weight);
		i++;
	}
}
int count(){
	int n=0;
	printf("\n������ʱ��Ƭ�Ĵ�С:\n");
	scanf("%d",&n);
	return n;
}

void timely(int t,int num){
	int flag=num;
	int i,j;
	i=2;
	int k=1;
	int temp1=-1;
	list[1].start.hour=list[1].arrive.hour;
	list[1].start.minute=list[1].arrive.minute;
	list[1].finish.hour=list[1].start.hour;
	if(list[1].remain<t)
        {
		list[1].finish.minute=list[1].start.minute+(list[1].remain);
		list[1].remain=0;
		}
    else
        {
			list[1].finish.minute=list[1].start.minute+t;
			list[1].remain=list[1].optime-t;
        }
	if(list[1].finish.minute>=60)
	{
		list[1].finish.hour=(list[1].finish.minute/60)+list[1].finish.hour;
		list[1].finish.minute=list[1].finish.minute-((list[1].finish.minute/60)*60);\
    }
		printf("\n********����ִ�е��߳�**********\n");
		printf("ID�� ���� ����ʱ�� ִ��ʱ�� ʣ��ִ��ʱ��");
   		printf("   ��ʼʱ�� ���ʱ��\n");
  	 	printf("%-6d%-3s%4d:%2d%7d%6d",list[1].id,list[1].name,list[1].arrive.hour,list[1].arrive.minute,list[1].optime,
		list[1].remain);
        printf("%16d:%02d%6d:%2d\n",list[1].start.hour, list[1].start.minute,list[1].finish.hour
		,list[1].finish.minute);
	while(flag)
        {
		//if(i>num){
		//	i=(i%num);
				printf("\n~~~~~~~~~~~~~%d\n",i);
	//}
		if(list[i].remain>0)
		{//�Ƿ�ִ����
			if(i==1)
            {
				list[1].start.hour=list[temp1].finish.hour;
				list[1].start.minute=list[temp1].finish.minute;
				list[1].finish.hour=list[1].start.hour;
				if(list[1].remain<t)
				{
					list[1].finish.minute=list[1].start.minute+(list[1].remain);
					list[1].remain=0;
				}
                else
                {
					list[1].finish.minute=list[1].start.minute+t;
					list[1].remain=list[1].remain-t;
				}

				if(list[1].finish.minute>=60)
                {
				list[1].finish.hour=(list[1].finish.minute/60)+list[1].finish.hour;
				list[1].finish.minute=list[1].finish.minute-((list[1].finish.minute/60)*60);
				}
                else
                {
					list[1].finish.hour=list[1].start.hour;
				}
				temp1=0;
			}
			else
			{
                    if(list[i].arrive.hour<list[i-1].finish.hour
						||((list[i].arrive.hour==list[i-1].finish.hour)&&(list[i].arrive.minute<=list[i-1].finish.minute)))
                    {
						list[i].start.hour=list[i-1].finish.hour;
						list[i].start.minute=list[i-1].finish.minute;
						list[i].finish.hour=list[i].start.hour;
						if(list[i].remain<t)
                        {
							list[i].finish.minute=list[i].start.minute+(list[i].remain);
							list[i].remain=0;
						}
						else
                        {

						list[i].finish.minute=list[i].start.minute+t;
						list[i].remain=list[i].remain-t;
						}

						//list[i].finish.minute=list[i].start.minute+t;
						//list[i].remain=list[i].optime-t;
						if(list[i].finish.minute>=60)
                        {
						list[i].finish.hour=(list[i].finish.minute/60)+list[i].finish.hour;
						list[i].finish.minute=list[i].finish.minute-(list[i].finish.minute/60)*60;
						}
						else
                        {
							list[i].finish.hour=list[i].start.hour;
						}
					}
					else
                    {
						temp1=i-1;
						i=1;
						printf("\n����һ��ʱ�����ǰһ����ʱ��%d\n",temp1);
						continue;
					}

			}
		}
        else
        {
				printf("\n333\n");
				flag--;
				temp[k++]=list[i];
				for(j=1;j<=flag;j++)
				{
					list[j]=list[j+1];
				}
        }
		printf("\n#############%d\n",temp1);
		printf("\n********����ִ�е��߳�**********\n");
		printf("ID�� ���� ����ʱ�� ִ��ʱ�� ʣ��ִ��ʱ��");
   		printf("   ��ʼʱ�� ���ʱ��\n");
  	 	printf("%-6d%-3s%4d:%2d%7d%6d",list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime,
		list[i].remain);
        printf("%16d:%02d%6d:%2d\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
		,list[i].finish.minute);
		i=(i+1)%num;
		i++;
	}

}
int main(){
	int k,t;
	k=0; t=0;
	t = input();//t���̵߳���Ŀ
	k=count();//k��ʱ��Ƭ�Ĵ�С
	timely(k,t);
}
