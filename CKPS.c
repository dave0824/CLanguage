#include<iostream>
#include<stdio.h>
#include<malloc.h>
//using namespace std;
enum process_status{READY , RUN , FINISH}; //���̵�����״̬
//����������ݽṹ
typedef struct pcb
{
    char process_tag[20] ; //�洢���̱�ʶ��
    struct pcb *next ; //������һ�����̵�ָ��
    int priority_num ; //���ȵ����㷨��Ϊ���ȼ� �� ��ת�����㷨��Ϊ��תʱ��Ƭ
    int take_cpu_time ; //ռ��CPUʱ��Ƭ��
    int process_time ; //��������ʱ��Ƭ��
    process_status status ; //���̵�ǰ��״̬
} PCB ;
//������̿��ƿ�����ṹ
typedef struct
{
    PCB *run ; //��ǰ���еĽ���ָ��
    PCB *ready ; //��ǰ׼�����е�ͷָ��
    PCB *tail ; //׼�����еĶ�βָ��
    PCB *finish ; //��ɶ��е�ָ��
} PCBC ;
void init_pcbc(PCBC *p)
{
    p->run = NULL ;
    p->ready = NULL ;
    p->tail = NULL ;
    p->finish = NULL ;
}
//������̣��������������
void input_process(PCBC *pcbc)
{
   PCB *pcb ;
   pcb = (PCB*)malloc(sizeof(PCB)) ;
   printf("��������̱�ʶ����") ;
   scanf("%s" , &pcb->process_tag) ;
   printf("�����ʽΪ�� �����ȼ���ռ��CPUʱ��Ƭ������������ʱ��Ƭ���� : ") ;
   scanf("%d,%d,%d" , &pcb->priority_num , &pcb->take_cpu_time , &pcb->process_time) ;
   pcb->status = READY ; //��ʼ������״̬
   //����������Ϊ��ʱ
   if(pcbc->ready == NULL && pcbc->tail == NULL)
   {
       pcbc->ready = pcbc->tail = pcb ;
       pcb->next = NULL ;
   }
   else
   {
       //���½���Ķ��м����β
       pcb->next = pcbc->tail->next ;
       pcbc->tail->next = pcb ;
       pcbc->tail = pcb ;
   }
}
void swapx(PCB  * p1 , PCB *p2)
{
    int  i , priority_num , take_cpu_time , process_time ;
    char temp ;
    //���б�ʶ���Ľ���
    for(i = 0 ; i < 20 ; i++)
    {
        temp = p1->process_tag[i];
        p1->process_tag[i] = p2->process_tag[i] ;
        p2->process_tag[i] = temp ;
    }
    //����ֵ�Ľ���
    priority_num = p1->priority_num ;
    p1->priority_num = p2->priority_num ;
    p2->priority_num = priority_num ;
    //ռ��CPUʱ��Ƭ�Ľ���
    take_cpu_time = p1->take_cpu_time ;
    p1->take_cpu_time = p2->take_cpu_time ;
    p2->take_cpu_time = take_cpu_time ;
    //��������ʱ��Ƭ���Ľ���
    process_time = p1->process_time ;
    p1->process_time = p2->process_time ;
    p2->process_time = process_time ;
}
//���������а����ȼ����С��������,��ð�������㷨
void sort_pcbc(PCBC *pcbc , int pcb_num)
{
    PCB *p  , *p1 ;
    p = pcbc->ready ;
   for(p = pcbc->ready ; p != NULL ; p = p->next)
   {
       for(p1 = p->next ; p1 != NULL ; p1 = p1->next)
       {
           if(p->priority_num < p1->priority_num)
           {
               swapx(p , p1) ; //ֻ�ǽ���ָ���ڲ����ݵĽ��������ı�ָ��ָ��
           }
       }
   }
}
/*
 *��ӡ��ǰ���̿��ƿ��е����
 */
 void print_log(PCBC *pcbc)
 {
     PCB *ready , *finish ;
     ready = pcbc->ready ;
     finish = pcbc->finish ;
     printf("--------------------------------------------------  \n") ;
     printf("Run�� \n") ;
     if(pcbc->run != NULL)
     {
        printf("%s  %04d  %04d  %04d \n" , pcbc->run->process_tag ,pcbc->run->priority_num , pcbc->run->take_cpu_time , pcbc->run->process_time) ;
     }
     else
     {
         printf("Run is empty! \n") ;
     }
     printf("Ready��\n") ;
     while(ready != NULL)
     {
         printf("%s  %04d  %04d  %04d \n" , ready->process_tag ,ready->priority_num , ready->take_cpu_time , ready->process_time) ;
         ready = ready->next ;
     }
     printf("Finish��\n") ;
     while(finish != NULL)
     {
         printf("%s  %04d  %04d  %04d \n" , finish->process_tag ,finish->priority_num , finish->take_cpu_time , finish->process_time) ;
         finish = finish->next ;
     }
 }
/*
 *���н��̿��ƿ�
 */
 void run_pcbc_priority(PCBC *xpcbc)
 {
     PCBC *pcbc = xpcbc ;
     PCB *temp , *pre , *tail ;
     //�����Ǹ�CPU��ѭ������
     while(pcbc->ready != NULL)
     {
         pcbc->run = pcbc->ready ; //���������ж��׼������ж���
         pcbc->ready = pcbc->ready->next ; //�ı����Ԫ��
         print_log(pcbc) ;
         pcbc->run->priority_num -= 3 ;
         pcbc->run->process_time -= 1 ;
         if(pcbc->run->process_time == 0)
         {
           if(pcbc->finish == NULL)
           {
               pcbc->finish = pcbc->run ;
               pcbc->finish->next = NULL ;
               tail = pcbc->finish ;
           }
           else
           {
              tail->next = pcbc->run ;
              tail = tail->next ;
              tail->next = NULL ;
           }
         }
         else
         {
             if(pcbc->ready != NULL)
             {
                 temp = pcbc->ready ;
                 while(temp != NULL)
                 {
                     if(pcbc->run->priority_num > temp->priority_num)
                     {
                         break ;
                     }
                     pre = temp ;
                     temp = temp->next ;
                 }
                 if(temp == pcbc->ready)
                 {
                     pcbc->run->next = pcbc->ready ;
                     pcbc->ready = pcbc->run ;
                 }
                 else
                 {
                    pcbc->run->next = pre->next ;
                    pre->next = pcbc->run ;
                 }
             }
             else
             {
                 pcbc->ready = pcbc->run ;
             }
         }
     }
     pcbc->run = NULL ;
     print_log(pcbc) ;
 }
int main()
{
    PCBC *pcbc ; //�������̿��ƿ��� ;
    int pcb_num ; //��¼���������Ŀ
    pcbc = (PCBC*)malloc(sizeof(PCBC)) ;
    printf("������Ҫ����Ľ�����Ŀ�� ") ;
    scanf("%d" , &pcb_num) ;
    init_pcbc(pcbc) ; //��ʼ�����̿��ƿ���
    for(int i = 0 ; i < pcb_num ; i++)
    {
        input_process(pcbc) ; //�������н��̣��������������
    }
    //���ݶ������ȼ���������
    sort_pcbc(pcbc , pcb_num) ;
    //ͨ�����ȵ����㷨����
    printf("By the priority--------------------------\n") ;
    run_pcbc_priority(pcbc) ;
    return 0 ;
}
