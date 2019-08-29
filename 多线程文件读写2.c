#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t lock;//互斥锁的宏
long fte=0;//记录文件指针的位置
char ch;//存储从文件中读取的字符
int flag=0;//运行标志
int num=0;//记录文件的字符数
int main()
{
    void Fileread(FILE *fp);
    void Filewrite(FILE *fp);
    FILE *fp;
        if(!(fp=fopen("1.txt","r+")))
    {
        printf("文件不存在！");
        exit(-1);
    }
    while(!feof(fp))
    {
         fgetc(fp);
         num++;
    }
    pthread_t t1,t2,t3,t4;
    pthread_create(&t1,NULL,(void*)Fileread,(FILE*)fp);
    pthread_create(&t2,NULL,(void*)Filewrite,(FILE*)fp);
   // pthread_create(&t3,NULL,(void*)Fileread,(FILE*)fp);
   // pthread_create(&t4,NULL,(void*)Filewrite,(FILE*)fp);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&lock);//加锁销毁
    printf("复制完毕");
    fclose(fp);
    return 0;
}
void Fileread(FILE *fp)
{
    do
    {
     pthread_mutex_lock(&lock);//加锁
     while(flag==1)
     {
         pthread_mutex_unlock(&lock);//解锁
         pthread_mutex_lock(&lock);//加锁
     }
            fseek(fp,fte++,0);
            ch=fgetc(fp);
            flag=1;
            printf("读取线程1读取文件为：%c,flag为：%d\n",ch,flag);
     pthread_mutex_unlock(&lock);//解锁
    }while(fte<num);
}
void Filewrite(FILE *fp)
{
    do
    {
     pthread_mutex_lock(&lock);//加锁
     while(flag==0)
     {
         pthread_mutex_unlock(&lock);//解锁
         pthread_mutex_lock(&lock);//加锁
     }
        fseek(fp,0L,SEEK_END);
        fputc((int)ch,fp);
        printf("写线程1正在写文件\n");
        flag=0;
     pthread_mutex_unlock(&lock);//解锁
    }while(fte<num);
}
