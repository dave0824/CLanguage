#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
int a=200;
int b=100;
pthread_mutex_t lock;//互斥锁的宏
void ThreadA(void)
{
    printf("线程A.....\n");
    pthread_mutex_lock(&lock);
    a-=50;
    //sleep(5);
    b+=50;
    pthread_mutex_unlock(&lock);
}
void ThreadB(void)
{
    printf("线程B.....\n");
    //sleep(1);
    pthread_mutex_lock(&lock);//加锁
    printf("a=%d\n",a);
    printf("b=%d\n",b);
    printf("%d\n",a+b);
    pthread_mutex_unlock(&lock);//解锁
}
int main(void)
{
    pthread_t tida,tidb;
    pthread_mutex_init(&lock,NULL);//建立一个互斥锁
    pthread_create(&tida,NULL,(void *)ThreadA,NULL);
    pthread_create(&tidb,NULL,(void *)ThreadB,NULL);//创建一个线程，1.句柄，2.线程属性，3.线程函数，4.函数的参数
    pthread_join(tida,NULL);//等待一个线程结束
    pthread_join(tidb,NULL);
    pthread_mutex_destroy(&lock);
    return 1;
}
