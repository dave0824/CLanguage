#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t lock;//�������ĺ�
long fte=0;//��¼�ļ�ָ���λ��
char ch;//�洢���ļ��ж�ȡ���ַ�
int flag=0;//���б�־
int num=0;//��¼�ļ����ַ���
int main()
{
    void Fileread(FILE *fp);
    void Filewrite(FILE *fp);
    FILE *fp;
        if(!(fp=fopen("1.txt","r+")))
    {
        printf("�ļ������ڣ�");
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
    pthread_mutex_destroy(&lock);//��������
    printf("�������");
    fclose(fp);
    return 0;
}
void Fileread(FILE *fp)
{
    do
    {
     pthread_mutex_lock(&lock);//����
     while(flag==1)
     {
         pthread_mutex_unlock(&lock);//����
         pthread_mutex_lock(&lock);//����
     }
            fseek(fp,fte++,0);
            ch=fgetc(fp);
            flag=1;
            printf("��ȡ�߳�1��ȡ�ļ�Ϊ��%c,flagΪ��%d\n",ch,flag);
     pthread_mutex_unlock(&lock);//����
    }while(fte<num);
}
void Filewrite(FILE *fp)
{
    do
    {
     pthread_mutex_lock(&lock);//����
     while(flag==0)
     {
         pthread_mutex_unlock(&lock);//����
         pthread_mutex_lock(&lock);//����
     }
        fseek(fp,0L,SEEK_END);
        fputc((int)ch,fp);
        printf("д�߳�1����д�ļ�\n");
        flag=0;
     pthread_mutex_unlock(&lock);//����
    }while(fte<num);
}
