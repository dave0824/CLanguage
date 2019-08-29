#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct
{
    char ch;
    int quanzhi;
    char* hc;
}L;
typedef struct
{
    int weight;
    int parent,lchild,rchild;
}htnode,*huffmantree;
typedef struct    //��Ÿ���Ϊ0�Ľڵ��Ȩֵ���±�
{
    int quanzhi;
    int xiabiao;
}record;
void output(huffmantree,int);
void select(huffmantree ht,int n,int *s1,int *s2);
huffmantree createhuffmantree(huffmantree ht,int n,L* A);
void creathuffmancode(huffmantree ht,L *A,int n);
void outputcode(L* A,int n);
int input(L* A,char text[200][2000],int m);//Ȩֵ����
void translation(char text[200][2000],L* A,char* version,int n,int cnt);//��������
void decode(huffmantree ht,L* A,char* version,int n);
void readdata(char text[200][2000],int* cnt);//��ȡ�ļ�
void savadata(char* array);//�洢����
void readmiwen(char* array);//��ȡ����
void savamima(L* A,int n);//�����������
int readmima(L* A);//��ȡ����ԭ��
int main(void)
{
    int n,cnt=0,i;
    L A[2000];
    huffmantree ht;
    char text[200][2000];
    char version[10000];
    version[0]='\n';
    for(;;)
    {
        printf("��ѡ���ܣ�\n");
        printf("1:huffuman������\n");
        printf("2:huffuman������\n");
        printf("3:�˳�ϵͳ\n");
        scanf("%d",&i);
        getchar();
        if(i==1)
        {
            readdata(text,&cnt);
            n=input(A,text,cnt);
            ht=createhuffmantree(ht,n,A);
            output(ht,n);
            creathuffmancode(ht,A,n);
            outputcode(A,n);
            translation(text,A,version,n,cnt);
            printf("�������Ӧ�������Ѵ�����ɲ����棡\n");
        }
        else if(i==2)
        {
            readmiwen(version);
            n=readmima(A);
            ht=createhuffmantree(ht,n,A);
            decode(ht,A,version,n);
        }
        else if(i==3)
        {
            break;
        }
        else
        {
            printf("�����������������룡\n");
        }
    }
    return 0;
}
void select(huffmantree ht,int n,int *s1,int *s2)
{
    int i,j,k,cnt=0;
    record temp[n];
    record temp2;
    for(k=0;k<=n;k++)
    {
        if(ht[k].parent==0)
        {
           temp[cnt].quanzhi=ht[k].weight;
           temp[cnt].xiabiao=k;
           cnt++;
        }
    }
    for(i=0;i<cnt;i++)
        for(j=i;j<cnt;j++)
        {
            if(temp[i].quanzhi>temp[j].quanzhi)
            {
               temp2=temp[i];
               temp[i]=temp[j];
               temp[j]=temp2;
            }
        }
        *s1=temp[0].xiabiao;
        *s2=temp[1].xiabiao;
}

huffmantree createhuffmantree(huffmantree ht,int n,L* A)
{
    int i,m,s1,s2;
    m=2*n-1;
    ht=(huffmantree)malloc(sizeof(htnode)*(m+1));
    for(i=1;i<=n;i++)
    {
        ht[i].parent=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
    }
    for(i=1;i<=n;i++)
    {
        ht[i].weight=A[i].quanzhi;
    }
    for(i=n+1;i<=m;i++)
    {
        select(ht,i-1,&s1,&s2);
        ht[s1].parent=i;
        ht[s2].parent=i;
        ht[i].lchild=s1,ht[i].rchild=s2;
        ht[i].weight=ht[s1].weight+ht[s2].weight;
        ht[i].parent=0;
    }
    return ht;
}

void output(huffmantree ht,int m)
{
	int i;
	m=2*m-1;
	printf("���\tweight\tparent\tlchild\trchild\t\n");
	for(i=1;i<=m;i++)
	{
	    printf("%d\t",i);
		printf("%d\t",ht[i].weight);
		printf("%d\t",ht[i].parent);
		printf("%d\t",ht[i].lchild);
		printf("%d\t",ht[i].rchild);
		printf("\n");
	}
	printf("*****************************************************\n");
}
void creathuffmancode(huffmantree ht,L *A,int n)
{
    int i,start,c,f,j,k;
    char *cd;
    cd=(char*)malloc(sizeof(char)*n);
    cd[n-1]='\0';
    for(i=1;i<=n;i++)
    {
        start=n-1;//startָ����󣬱��������λ��
        c=i;
        f=ht[i].parent;//fָ����c��˫��
        while(f!=0)
        {
            --start;
            if(ht[f].lchild==c)
                cd[start]='0';
            else
                cd[start]='1';
            c=f;
            f=ht[f].parent;
        }
        A[i].hc=(char*)malloc(sizeof(char)*(n-start));
        strcpy(A[i].hc,&cd[start]);
    }
    free(cd);
    savamima(A,n);
}
void creathuffmancode2(huffmantree ht,L *A,int n)
{
    int i,start,c,f,j,k;
    char *cd;
    cd=(char*)malloc(sizeof(char)*n);
    cd[n-1]='\0';
    for(i=1;i<=n;i++)
    {
        start=n-1;//startָ����󣬱��������λ��
        c=i;
        f=ht[i].parent;//fָ����c��˫��
        while(f!=0)
        {
            --start;
            if(ht[f].lchild==c)
                cd[start]='0';
            else
                cd[start]='1';
            c=f;
            f=ht[f].parent;
        }
    }
    free(cd);
}
void outputcode(L* A,int n)
{
    int i,j;
    for(i=1;i<=n;i++)
    {
        printf("%c=%s\n",A[i].ch,A[i].hc);
    }
}
int input(L* A,char text[200][2000],int m)//Ȩֵ����
{
    int i,j,k,cnt=2;
    A[1].ch=text[0][0];
    for(k=0;k<m;k++)
    for(i=0;i<strlen(text[k]);i++)
    {
        for(j=1;j<=i+1;j++)
        {
            if(text[k][i]==A[j].ch)
            {
                A[j].quanzhi++;
                break;
            }
        }
        if(j>i+1)
        {
            A[cnt].ch=text[k][i];
            A[cnt].quanzhi=1;
            cnt++;
        }

    }
    return cnt-1;
}
void translation(char text[200][2000],L* A,char* version,int n,int cnt)
{
    int i,j,k;
    for(k=0;k<cnt;k++)
    for(i=0;i<strlen(text[k]);i++)
    {
        for(j=1;j<=n;j++)
        if(text[k][i]==A[j].ch)
        {
          strcat(version,A[j].hc);
          break;
        }
    }
    printf("����:%s\n",&version[1]);//���Ĵ洢��version[1]��ʼ��version[0]û�У���
    savadata(&version[1]);
}
void decode(huffmantree ht,L* A,char* version,int n)
{
  char *ch=version;
  char mingwen[2000];
  int i,j=0;
  int m=2*n-1;
  while(*ch!='\0')
  {
      for(i=m;ht[i].lchild!=0&&ht[i].rchild!=0;)
      {
          if(*ch=='0')
            i=ht[i].lchild;
          else if(*ch=='1')
            i=ht[i].rchild;
          ch++;
      }
      mingwen[j++]=A[i].ch;
  }
   mingwen[j]='\0';
   printf("����:\n\n%s",mingwen);
}
void readdata(char text[200][2000],int* cnt)//��ȡ�ļ�
{
    FILE *fp;
    char filename[20];
    printf("������ԭ�����ڵ��ļ���\n");
    gets(filename);
    int k=0,i;
    if(!(fp=fopen(filename,"r")))
    {
        printf("�ļ������ڣ�");
        exit(-1);
    }
    while(!feof(fp))
    {
        fgets(text[k++],2000,fp);
        (*cnt)++;
    }
    fclose(fp);
}
void savadata(char* array)//�洢����
{
    FILE *fp;
    char filename[20];
    printf("������洢���ĵ��ļ���\n");
    gets(filename);
    int k=0,i;
    if(!(fp=fopen(filename,"w")))
    {
        printf("�洢ʧ�ܣ�");
        exit(-1);
    }
    fputs(array,fp);
    fclose(fp);
}
void readmiwen(char* array)//��ȡ����
{
    FILE *fp;
    char filename[20];
    printf("�������������ڵ��ļ���\n");
    gets(filename);
    if(!(fp=fopen(filename,"r")))
    {
        printf("�ļ������ڣ�");
        exit(-1);
    }
    fgets(array,10000,fp);
    fclose(fp);
}
void savamima(L* A,int n)//�����������
{
    FILE *fp;
    int i;
    char filename[20];
    printf("������洢��Ӧ������ļ���\n");
    gets(filename);
    if(!(fp=fopen(filename,"w")))
    {
        printf("�洢ʧ�ܣ�");
        exit(-1);
    }
    for(i=1;i<=n;i++)
    {
        fprintf(fp,"%c,%d,%s\n",A[i].ch,A[i].quanzhi,A[i].hc);
    }
    fclose(fp);
}
int readmima(L A[2000])//��ȡ����ԭ��
{
    char ch;
    char out[1000];
    FILE *fp;
    int i=1;
    char filename[20];
    printf("���������Ķ�Ӧ���������ڵ��ļ���\n");
    gets(filename);
    if(!(fp=fopen(filename,"r")))
    {
        printf("�ļ������ڣ�");
        exit(-1);
    }
    while(!feof(fp))
    {
        A[i].hc=(char*)malloc(sizeof(char)*20);
        //fscanf(fp,"%c,%d,%s\n",&A[i].ch,&A[i].quanzhi,A[i].hc);
        A[i].ch=fgetc(fp);
        while(!feof(fp))
        {
            if((ch=fgetc(fp)=='\n')||(ch=fgetc(fp)==','))
                putchar(1);
            fgetc(fp);
            //fscanf(fp,"%c,%d,%s\n",&A[i].ch,&A[i].quanzhi,A[i].hc);
            printf("%c,%d,%s\n",A[i].ch,A[i].quanzhi,A[i].hc);
            i++;
        }

    }
    fclose(fp);
    return i;
}
