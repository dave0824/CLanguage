#include<iostream>
#include<stdio.h>
#include<malloc.h>
//using namespace std;
enum process_status{READY , RUN , FINISH}; //进程的三种状态
//定义进程数据结构
typedef struct pcb
{
    char process_tag[20] ; //存储进程标识符
    struct pcb *next ; //连接下一个进程的指针
    int priority_num ; //优先调度算法中为优先级 ， 轮转调度算法中为轮转时间片
    int take_cpu_time ; //占用CPU时间片数
    int process_time ; //进程所需时间片数
    process_status status ; //进程当前的状态
} PCB ;
//定义进程控制块的链结构
typedef struct
{
    PCB *run ; //当前运行的进程指针
    PCB *ready ; //当前准备队列的头指针
    PCB *tail ; //准备队列的队尾指针
    PCB *finish ; //完成队列的指针
} PCBC ;
void init_pcbc(PCBC *p)
{
    p->run = NULL ;
    p->ready = NULL ;
    p->tail = NULL ;
    p->finish = NULL ;
}
//输入进程，并加入就绪队列
void input_process(PCBC *pcbc)
{
   PCB *pcb ;
   pcb = (PCB*)malloc(sizeof(PCB)) ;
   printf("请输入进程标识符：") ;
   scanf("%s" , &pcb->process_tag) ;
   printf("输入格式为： （优先级，占用CPU时间片数，进程所需时间片数） : ") ;
   scanf("%d,%d,%d" , &pcb->priority_num , &pcb->take_cpu_time , &pcb->process_time) ;
   pcb->status = READY ; //初始化就绪状态
   //当就绪队列为空时
   if(pcbc->ready == NULL && pcbc->tail == NULL)
   {
       pcbc->ready = pcbc->tail = pcb ;
       pcb->next = NULL ;
   }
   else
   {
       //将新进入的队列加入队尾
       pcb->next = pcbc->tail->next ;
       pcbc->tail->next = pcb ;
       pcbc->tail = pcb ;
   }
}
void swapx(PCB  * p1 , PCB *p2)
{
    int  i , priority_num , take_cpu_time , process_time ;
    char temp ;
    //进行标识符的交换
    for(i = 0 ; i < 20 ; i++)
    {
        temp = p1->process_tag[i];
        p1->process_tag[i] = p2->process_tag[i] ;
        p2->process_tag[i] = temp ;
    }
    //优先值的交换
    priority_num = p1->priority_num ;
    p1->priority_num = p2->priority_num ;
    p2->priority_num = priority_num ;
    //占用CPU时间片的交换
    take_cpu_time = p1->take_cpu_time ;
    p1->take_cpu_time = p2->take_cpu_time ;
    p2->take_cpu_time = take_cpu_time ;
    //进程所需时间片数的交换
    process_time = p1->process_time ;
    p1->process_time = p2->process_time ;
    p2->process_time = process_time ;
}
//将就绪队列按优先级别大小进行排序,按冒泡排序算法
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
               swapx(p , p1) ; //只是进行指针内部数据的交换，不改变指针指向
           }
       }
   }
}
/*
 *打印当前进程控制块中的情况
 */
 void print_log(PCBC *pcbc)
 {
     PCB *ready , *finish ;
     ready = pcbc->ready ;
     finish = pcbc->finish ;
     printf("--------------------------------------------------  \n") ;
     printf("Run： \n") ;
     if(pcbc->run != NULL)
     {
        printf("%s  %04d  %04d  %04d \n" , pcbc->run->process_tag ,pcbc->run->priority_num , pcbc->run->take_cpu_time , pcbc->run->process_time) ;
     }
     else
     {
         printf("Run is empty! \n") ;
     }
     printf("Ready：\n") ;
     while(ready != NULL)
     {
         printf("%s  %04d  %04d  %04d \n" , ready->process_tag ,ready->priority_num , ready->take_cpu_time , ready->process_time) ;
         ready = ready->next ;
     }
     printf("Finish：\n") ;
     while(finish != NULL)
     {
         printf("%s  %04d  %04d  %04d \n" , finish->process_tag ,finish->priority_num , finish->take_cpu_time , finish->process_time) ;
         finish = finish->next ;
     }
 }
/*
 *运行进程控制块
 */
 void run_pcbc_priority(PCBC *xpcbc)
 {
     PCBC *pcbc = xpcbc ;
     PCB *temp , *pre , *tail ;
     //进行那个CPU的循环调用
     while(pcbc->ready != NULL)
     {
         pcbc->run = pcbc->ready ; //将就绪队列队首加入运行队列
         pcbc->ready = pcbc->ready->next ; //改变队首元素
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
    PCBC *pcbc ; //创建进程控制块链 ;
    int pcb_num ; //记录处理进程数目
    pcbc = (PCBC*)malloc(sizeof(PCBC)) ;
    printf("请输入要处理的进程数目： ") ;
    scanf("%d" , &pcb_num) ;
    init_pcbc(pcbc) ; //初始化进程控制块链
    for(int i = 0 ; i < pcb_num ; i++)
    {
        input_process(pcbc) ; //输入所有进程，并进入就绪队列
    }
    //根据队列优先级进行排序
    sort_pcbc(pcbc , pcb_num) ;
    //通过优先调度算法运行
    printf("By the priority--------------------------\n") ;
    run_pcbc_priority(pcbc) ;
    return 0 ;
}
