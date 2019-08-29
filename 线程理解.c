#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
int a=200;
int b=100;
pthread_mutex_t lock;//�������ĺ�
void ThreadA(void)
{
    printf("�߳�A.....\n");
    pthread_mutex_lock(&lock);
    a-=50;
    //sleep(5);
    b+=50;
    pthread_mutex_unlock(&lock);
}
void ThreadB(void)
{
    printf("�߳�B.....\n");
    //sleep(1);
    pthread_mutex_lock(&lock);//����
    printf("a=%d\n",a);
    printf("b=%d\n",b);
    printf("%d\n",a+b);
    pthread_mutex_unlock(&lock);//����
}
int main(void)
{
    pthread_t tida,tidb;
    pthread_mutex_init(&lock,NULL);//����һ��������
    pthread_create(&tida,NULL,(void *)ThreadA,NULL);
    pthread_create(&tidb,NULL,(void *)ThreadB,NULL);//����һ���̣߳�1.�����2.�߳����ԣ�3.�̺߳�����4.�����Ĳ���
    pthread_join(tida,NULL);//�ȴ�һ���߳̽���
    pthread_join(tidb,NULL);
    pthread_mutex_destroy(&lock);
    return 1;
}
