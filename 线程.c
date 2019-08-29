/*
    　　我们可以使用函数pthread_create创建一个新的线程:
函数原型：
　　int pthread_create( pthread_t   *thread,   pthread_attr_t *attr,    void   *(*func),   void   *arg);
参数：      thread     指向pthread_t类型变量的指针，  typedef unsigned long int pthread_t, pthread_t用于声明线程ID
               attr         指向pthread_attr_t类型变量的指针，或者为NULL
               func        指向新线程所运行函数的指针
              arg          传递给func的参数
返回值      0            成功返回
              errcode    错误

　　我们可以使用函数pthread_join等待某进程结束：
函数原型：
　　int pthread_join(pthread_t  thread, void **  retval);
参数：     thread         所等待的进程
              retval          指向某存储线程返回值的变量
返回值：  0                 成功返回
             errorcode     错误
*/
#include<stdio.h>
#include<pthread.h>
#define NUM 6
int main()
{
    void print_msg();

    pthread_t t1,t2;
    pthread_create(&t1,NULL,print_msg,NULL);
    pthread_create(&t2,NULL,print_msg,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}
void print_msg()
{
    //char *cp=(char*)m;
    int i;
    int m =5;
    for(i=0;i<NUM;i++)
    {
        printf("%d",m);
        //fflush(stdout);
        //sleep(1);
    }
}
