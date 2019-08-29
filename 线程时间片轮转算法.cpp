#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 20
typedef struct data{
	int hour;
	int minute;
}time;

typedef struct node{
	int id; //进程编号
	char name[20];//进程名
	time arrive;//到达队列的时间
	time start;//开始执行时间
	time finish;//执行结束时间
	//time temp;//临时的结束时间
	int remain;//剩余操作时间
	int optime;//执行时间
	int ztime;//周转时间
	float weight;//带权周转系数
}List;

List list [N];
List temp [N];
int input();
void output(int num);
void sorttime(int num);

int input(){
	FILE *fp=fopen("datafcfs.txt","rt+");
	int num;//进程数目
	printf("请输入进程数目\n");
	scanf("%d",&num);
	printf("进程ID	进程名	到达时间	执行时间(分)    剩余执行时间\n");
	int n=1;//第一个位置不放任何数据
	while(n<=num){
		fscanf(fp, "%d%s%d:%2d%d",&list[n].id,list[n].name,&list[n].arrive.hour,&list[n].arrive.minute,&list[n].optime);
        //printf("\n%d\n",list[n].id);
        list[n].remain=list[n].optime;
		printf("%-6d%-5s%2d:%2d%7d%6d\n",list[n].id,list[n].name,list[n].arrive.hour,list[n].arrive.minute, list[n].optime,list[n].optime);
        n++;
	}
	fclose(fp);
	sorttime(num);
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
	printf("模拟进程时间片调度过程输出结果：\n");
    printf("ID号 名字 到达时间 执行时间（分钟） 剩余执行时间");
    printf("   开始时间 完成时间 周转时间（分钟）带权周转时间（系数）\n");
	while(i<=num){
		printf("%-6d%-3s%4d:%02d%7d%6d",list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime,list[i].remain);
        printf("%16d:%02d%6d:%02d%9d%7.2f\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
		,list[i].finish.minute,list[i].ztime, list[i].weight);
		i++;
	}
}
void outputtemp(int num){
	int i=0;
	printf("模拟进程时间片调度过程输出结果：\n");
    printf("ID号 名字 到达时间 执行时间（分钟） 剩余执行时间");
    //printf("开始时间 完成时间 周转时间（分钟）带权周转时间（系数）\n");
	while(i<=num){
		printf("\n%-6d%-3s%4d:%02d%7d%d6d\n",list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime,list[i].remain);
       // printf("%16d:%02d%6d:%02d%9d%7.2f\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
		//,list[i].finish.minute,list[i].ztime, list[i].weight);
		i++;
	}
}
int count(){
	int n=0;
	printf("\n请输入时间片的大小:\n");
	scanf("%d",&n);
	return n;
}

void timely(int t,int num){

	int i,j;
	i=2;
	int k=1;
	//j=num;
	list[1].start.hour=list[1].arrive.hour;
				list[1].start.minute=list[1].arrive.minute;
				list[1].finish.hour=list[1].start.hour;
				list[1].finish.minute=list[1].start.minute+t;
				list[1].remain=list[1].optime-t;
				if(list[1].finish.minute>=60){
				list[1].finish.hour=(list[1].finish.minute/60)+list[1].finish.hour;
				list[1].finish.minute=list[1].finish.minute-((list[1].finish.minute/60)*60);
				}
        printf("\n********正在执行的线程**********\n");
		printf("ID号 名字 到达时间 执行时间 剩余执行时间");
   		printf("   开始时间 完成时间\n");
  	 	printf("%-6d%-3s%4d:%2d%7d%6d",list[1].id,list[1].name,list[1].arrive.hour,list[1].arrive.minute,list[1].optime,
		list[1].remain);
        printf("%16d:%02d%6d:%2d\n",list[1].start.hour, list[1].start.minute,list[1].finish.hour
		,list[1].finish.minute);
	int flag=num;
	//list[0]=list[1];
	while(flag)
    {

			//if(i>num){
			//i=(i%num);
				printf("\n~~~~~~~~~~~~~%d\n",i);
		//}
		if(list[i].remain>0)
        {//是否执行完
			if(i==1)
            {
				list[1].start.hour=list[1].finish.hour;
				list[1].start.minute=list[1].finish.minute;
				list[1].finish.hour=list[1].start.hour;
				list[1].finish.minute=list[1].start.minute+t;
				list[1].remain=list[1].optime-t;
				if(list[1].finish.minute>=60)
                {
				list[1].finish.hour=(list[1].finish.minute/60)+list[1].finish.hour;
				list[1].finish.minute=list[1].finish.minute-((list[1].finish.minute/60)*60);
				}
			}
			else
            {
                    if(list[i].arrive.hour<list[i-1].finish.hour
						||((list[i].arrive.hour==list[i-1].finish.hour)&&(list[i].arrive.minute<=list[i-1].finish.minute)))
                    {
						list[i].start.hour=list[i-1].finish.hour;
						list[i].start.minute=list[i-1].finish.minute;
						list[i].finish.hour=list[i].start.hour;
						list[i].finish.minute=list[i].start.minute+t;
						list[i].remain=list[i].optime-t;
						if(list[i].finish.minute>=60)
						{
						list[i].finish.hour=(list[i].finish.minute/60)+list[i].finish.hour;
						list[i].finish.minute=list[i].finish.minute-(list[i].finish.minute/60)*60;
						}
                        else
                        {
							printf("\n分大于60\n");
						}
					}
					else
                    {
						i=1;
						printf("\n后面一个时间大于前一个的时间\n");
                        printf("\n********正在执行的线程**********\n");
                        printf("ID号 名字 到达时间 执行时间 剩余执行时间");
                        printf("   开始时间 完成时间\n");
                                printf("%-6d%-3s%4d:%2d%7d%6d",list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime,
                                list[i].remain);
                                printf("%16d:%02d%6d:%2d\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
                                ,list[i].finish.minute);
						continue;
					}
            }
        }
        else
        {
				printf("\n333\n");
				flag--;
				temp[k++]=list[i];
				for(j=i+1;j<=num;j++){
					list[i]=list[j];
				}
        }
		printf("\n********正在执行的线程**********\n");
		printf("ID号 名字 到达时间 执行时间 剩余执行时间");
   		printf("   开始时间 完成时间\n");
  	 	printf("%-6d%-3s%4d:%2d%7d%6d",list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime,
		list[i].remain);
        printf("%16d:%02d%6d:%2d\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
		,list[i].finish.minute);
		i++;

	}
}
int main(){
	int k,t;
	k=0; t=0;
	t = input();//t是线程的数目

	k=count();//k是时间片的大小
	timely(k,t);
	//output(t);


}
