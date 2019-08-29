#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
	int optime;//ִ��ʱ��
	int ztime;//��תʱ��
	float weight;//��Ȩ��תϵ��
	struct node* next;//��һ�ڵ�
}List;

List * CreateList(){
	List* head=(List*)malloc(sizeof(List));
	if(head){
            head->next=NULL;
		return head;
	}
	else{
		printf("��������ʧ�ܣ�\n");
		exit(-1);
	}
}

void input(List* head){
	FILE *fp;
	List* list=head;
	fp=fopen("data.txt","rt+");
	int num;//������Ŀ
	printf("�����������Ŀ\n");
	scanf("%d",&num);
	printf("����ID	������	����ʱ��	ִ��ʱ��(��)\n");
	while(num>0){
		List* s=(List*)malloc(sizeof(List));
		//fscanf(fp,"%d%s%d:%d%2d",&l->id,&l->name,&l->arrive.hour,&l->arrive.minute,&l->optime);
		//printf("%-6d%-3s%-4d:%3d%7d",l->id,l->name,l->arrive.hour,l->arrive.minute,l->optime);
	    fscanf(fp, "%d%s%d:%2d%d",&s->id,s->name,&s->arrive.hour,&s->arrive.minute,&s->optime);
        printf("%-6d%-3s%4d:%02d%7d\n",s->id,s->name,s->arrive.hour,s->arrive.minute, s->optime);
        	if(list->next==NULL){
        		list->next=s;
        		s->next=NULL;
			}
			else{
                    list=list->next;
                    list->next=s;
                    s->next=NULL;

				//s->next=list->next;
				//list->next=s;
			}

		num--;
	}

	fclose(fp);

}
void output(List* head){
	List *p=head->next;
	printf("ģ�����FCFS���ȹ�����������\n");
    printf("ID�� ���� ����ʱ�� ִ��ʱ�䣨���ӣ�");
    printf("��ʼʱ�� ���ʱ�� ��תʱ�䣨���ӣ���Ȩ��תʱ�䣨ϵ����\n");
	while(p){

		printf("%-6d%-3s%4d:%02d%7d\n",p->id,p->name,p->arrive.hour,p->arrive.minute, p->optime);
        //printf("%16d:%02d%6d:%02d%9d%17.2f\n",p->start.hour, p->start.minute, p->finish.hour,p->finish.minute,p->ztime, p->weight);
		p=p->next;
	}
	return ;
}
void sort(List* head)
{
	List *L=NULL;
	List *p=NULL;
	L=head->next;
	p=L->next;
	List *temp=(List*)malloc(sizeof(List));
	temp->next=NULL;
	while(L){
		while(p){
			if((L->arrive.hour>p->arrive.hour)||((L->arrive.hour==p->arrive.hour)
				&&(L->arrive.minute>p->arrive.minute)))
            {
			temp->arrive=L->arrive;
			temp->id=L->id;
			strcpy(temp->name,L->name);
			temp->optime=L->optime;
			L->arrive=p->arrive;
			L->id=p->id;
		    strcpy(L->name,p->name);
			L->optime=p->optime;
			p->arrive=temp->arrive;
			p->id=temp->id;
			strcpy(p->name,temp->name);
			p->optime=temp->optime;
			}
			p=p->next;
		}
		p=L->next;
		L=L->next;
	}
}
int main(){
	List *head=NULL;
	head=CreateList();
	input(head);
	sort(head);
	output(head);
}
