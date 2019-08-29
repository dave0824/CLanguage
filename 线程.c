/*
    �������ǿ���ʹ�ú���pthread_create����һ���µ��߳�:
����ԭ�ͣ�
����int pthread_create( pthread_t   *thread,   pthread_attr_t *attr,    void   *(*func),   void   *arg);
������      thread     ָ��pthread_t���ͱ�����ָ�룬  typedef unsigned long int pthread_t, pthread_t���������߳�ID
               attr         ָ��pthread_attr_t���ͱ�����ָ�룬����ΪNULL
               func        ָ�����߳������к�����ָ��
              arg          ���ݸ�func�Ĳ���
����ֵ      0            �ɹ�����
              errcode    ����

�������ǿ���ʹ�ú���pthread_join�ȴ�ĳ���̽�����
����ԭ�ͣ�
����int pthread_join(pthread_t  thread, void **  retval);
������     thread         ���ȴ��Ľ���
              retval          ָ��ĳ�洢�̷߳���ֵ�ı���
����ֵ��  0                 �ɹ�����
             errorcode     ����
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
