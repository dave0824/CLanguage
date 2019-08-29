/*
这是线程的优先级调度算法
主要要注意的是
1---在时间上，如果只有一个准备好的线程，直接执行。
2---否则，注重优先级的调度，如果优先级一样的话，先来先执行
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 20
typedef struct data{
	int hour;
	int minute;
}time;
typedef struct node{
	int priority;//优先级
	int id; //进程编号
	char name[20];//进程名
	time arrive;//到达队列的时间
	time start;//开始执行时间
	time finish;//执行结束时间
	int optime;//执行时间
	int ztime;//周转时间
	float weight;//带权周转系数
}List;


List list[N];
void output(int num);
int input();
void sorttime(int num);
void Prority(int num);

int input(){
	FILE *fp=fopen("dataprority.txt","rt+");
	int num;//进程数目
	printf("请输入进程数目\n");
	scanf("%d",&num);
	printf("优先级 进程ID	进程名	到达时间	执行时间(分)\n");
	int n=1;//第一个位置不放任何数据
	while(n<=num){
		fscanf(fp, "%d%d%s%d:%2d%d",&list[n].priority,&list[n].id,list[n].name,&list[n].arrive.hour,&list[n].arrive.minute,&list[n].optime);
        //printf("\n%d\n",list[n].id);
		printf("%-3d%-6d%-3s%4d:%4d%7d\n",list[n].priority,list[n].id,list[n].name,list[n].arrive.hour,list[n].arrive.minute, list[n].optime);
        n++;
	}
	fclose(fp);
	sorttime(num);
	return num;
}
void output(int num){

	int i=1;
	printf("模拟进程FCFS调度过程输出结果：\n");
    printf("优先级  ID号 名字 到达时间 执行时间（分钟）");
    printf("开始时间 完成时间 周转时间（分钟）带权周转时间（系数）\n");
	while(i<=num){
		printf("%-4d%-6d%-3s%4d:%02d%7d",list[i].priority,list[i].id,list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[i].optime);
        printf("%16d:%02d%6d:%02d%9d%7.2f\n",list[i].start.hour, list[i].start.minute,list[i].finish.hour
		,list[i].finish.minute,list[i].ztime, list[i].weight);
		i++;
	}
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
void sortprority(int k,int num){
	int i,j;
	for(i=k+1;i<=num;i++){
		if(list[i].arrive.hour<list[k].finish.hour
		||((list[i].arrive.hour==list[k].finish.hour)&&(list[i].arrive.minute<list[k].finish.minute))){
		//printf("\n****%s   %d : %d  %d : %d  \n",list[i].name,list[i].arrive.hour,list[i].arrive.minute,list[k].finish.hour,list[k].finish.minute);
			for(j=i+1;j<=num;j++){
				if(list[j].arrive.hour<list[k].finish.hour
					||((list[j].arrive.hour==list[k].finish.hour)&&(list[j].arrive.minute<list[k].finish.minute))){
				//printf("\n****%s    %s   j=%d\n",list[i].name,list[i+1].name,j);
					if(list[i].priority<list[j].priority){

						list[0]=list[i];
						list[i]=list[j];
						list[j]=list[0];
					}
				}

	    		}
			}
		}
}
void Prority(int num){
	int i=2;
	int t=0;
	list[1].start.hour=list[1].arrive.hour;
	list[1].start.minute=list[1].arrive.minute;
	list[1].finish.hour=list[1].start.hour;
	list[1].finish.minute=list[1].start.minute+list[1].optime;
	if(list[1].finish.minute>=60){
		t=list[1].finish.minute/60;
		list[1].finish.hour=list[1].finish.hour+t;
		list[1].finish.minute=list[1].finish.minute-(t)*60;
	}
	list[1].ztime=(list[1].finish.hour-list[1].arrive.hour) *60+(list[1].finish.minute-list[1].arrive.minute);
	list[1].weight=(float) list[1].ztime/list[1].optime;
	while(i<=num){
		sortprority(i-1,num);
		list[i].start.hour=list[i-1].finish.hour;
		list[i].start.minute=list[i-1].finish.minute;
		list[i].finish.hour=list[i].start.hour;
		list[i].finish.minute=list[i].start.minute+list[i].optime;
		if(list[i].finish.minute>=60){
			t=list[i].finish.minute/60;
			list[i].finish.hour=list[i].finish.hour+t;
			list[i].finish.minute=list[i].finish.minute-(t)*60;
		}

		list[i].ztime=(list[i].finish.hour-list[i].arrive.hour) *60+(list[i].finish.minute-list[i].arrive.minute);
		list[i].weight=(float) list[i].ztime/list[i].optime;
		i++;
	}
}
int main(){
	List list;
	int num=0;
	num=input();
	Prority(num);
	output(num);


}
