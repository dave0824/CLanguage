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
typedef struct    //存放父亲为0的节点的权值和下标
{
    int quanzhi;
    int xiabiao;
}record;
void output(huffmantree,int);
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
           //printf("%d   ",ht[k].weight);
        }
    }
    //printf("\n");
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
       // printf("s1=%d  s2=%d  ht[s1].weight=%d  ht[s2].weight=%d\n",*s1,*s2,ht[*s1].weight,ht[*s2].weight);
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
	printf("结点\tweight\tparent\tlchild\trchild\t\n");
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
        start=n-1;//start指向最后，编码结束符位置
        c=i;
        f=ht[i].parent;//f指向结点c的双亲
        //printf("ht[%d].parent=%d\n",i,ht[i].parent);
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
        //for(j=start;j<n;j++)
           // printf("%c",cd[j]);
       // printf("\n");
        A[i].hc=(char*)malloc(sizeof(char)*(n-start));
        strcpy(A[i].hc,&cd[start]);
        //for(j=0;j<n-start;j++)
            //printf("A[%d].hc=%s",i,A[i].hc);
       // printf("\n");
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
int input(L* A,char* text)//权值计算
{
    int i,j,cnt=2;
    printf("请输入原文\n");
    gets(text);
    A[1].ch=text[0];
    A[1].quanzhi=1;
    for(i=1;i<strlen(text);i++)
    {
        for(j=1;j<=i;j++)
        {
            if(text[i]==A[j].ch)
            {
                A[j].quanzhi++;
                break;
            }
        }
        if(j>i)
        {
            A[cnt].ch=text[i];
            A[cnt].quanzhi=1;
            cnt++;
        }

    }
    return cnt-1;
}
void translation(char* text,L* A,char* version)
{
    int i,j;
    for(i=0;i<strlen(text);i++)
    {
        if(text[i]==A[1].ch)
            strcat(version,A[1].hc);
        else if(text[i]==A[2].ch)
            strcat(version,A[2].hc);
        else if(text[i]==A[3].ch)
            strcat(version,A[3].hc);
        else if(text[i]==A[4].ch)
            strcat(version,A[4].hc);
        else if(text[i]==A[5].ch)
            strcat(version,A[5].hc);
        else if(text[i]==A[6].ch)
            strcat(version,A[6].hc);
        else if(text[i]==A[7].ch)
            strcat(version,A[7].hc);
        else if(text[i]==A[8].ch)
            strcat(version,A[8].hc);
        else if(text[i]==A[9].ch)
            strcat(version,A[9].hc);
        else if(text[i]==A[10].ch)
            strcat(version,A[10].hc);
        else if(text[i]==A[11].ch)
            strcat(version,A[11].hc);
        else if(text[i]==A[12].ch)
            strcat(version,A[12].hc);
        else if(text[i]==A[13].ch)
            strcat(version,A[13].hc);
    }
    printf("密文:%s\n",&version[1]);//密文存储从version[1]开始，version[0]没有！！
}
void decode(huffmantree ht,L* A,char* version,int n)
{
  char *ch=version+1;
  char mingwen[20];
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
   printf("明文:%s",mingwen);
}
int main(void)
{
    int n;
    L A[20];
    char text[20];
    char version[100];
    huffmantree ht;
    n=input(A,text);
    ht=createhuffmantree(ht,n,A);
    output(ht,n);
    creathuffmancode(ht,A,n);
    outputcode(A,n);
    translation(text,A,version);
    decode(ht,A,version,n);
}
