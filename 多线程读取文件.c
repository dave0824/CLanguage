#include<stdio.h>
#include<pthread.h>
pthread_mutex_t lock;//�������ĺ�
long fte=0;//��¼�ļ�ָ���λ��
char ch;
int flag=0;
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
    pthread_t t1,t2,t3,t4;
    pthread_create(&t1,NULL,(void*)Fileread,(FILE*)fp);
    pthread_create(&t2,NULL,(void*)Filewrite,(FILE*)fp);
    pthread_create(&t1,NULL,(void*)Fileread,(FILE*)fp);
    pthread_create(&t2,NULL,(void*)Filewrite,(FILE*)fp);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&lock);//��������
    printf("�������");
    fclose(fp);
    return;
}
void Fileread(FILE *fp)
{
    int i;
    for(i=0;i<1000;i++)
    {
     pthread_mutex_lock(&lock);//����
    if(flag==0)
        {
            fseek(fp,fte++,0);
            ch=fgetc(fp);
            flag=1;
            printf("��ȡ�ļ�Ϊ��%c,flagΪ��%d,i=%d\n",ch,flag,i);
            Sleep(1);
        }
        printf("i==%d",i);
     //printf("%d\n",fte);
     pthread_mutex_unlock(&lock);//����
    }
}
void Filewrite(FILE *fp)
{
    int i;
    for(i=0;i<1000;i++)
    {
     pthread_mutex_lock(&lock);//����
     if(flag==1)
     {
        fseek(fp,0L,SEEK_END);
        fputc((int)ch,fp);
        printf("222\n");
        flag=0;
        Sleep(1);
     }
     pthread_mutex_unlock(&lock);//����
    }
}
