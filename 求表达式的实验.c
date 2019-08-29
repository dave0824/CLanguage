#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define M 20
typedef struct //ÔËËã·ûÕ»
{
    char stack[M];
    int top;
}STACK1;
typedef struct //²Ù×÷ÊýÕ»
{
    int stack[M];
    int top;
}STACK2;
void init1(STACK1 *S)
{
	S->top=0;
}
void init2(STACK2 *T)
{
	T->top=0;
}
int push1(STACK1 *S,char ch)
{
	if(S->top==M)
	{
		printf("\nthe STACK is full\n");
		exit(-1);
	}
	else
	{
		S->stack[S->top]=ch;
		S->top++;
		printf("  \n S%d",S->top);
	}
}
int push2(STACK2 *T,int  ch)
{
	if(T->top==M)
	{
		printf("\nthe STACK is full\n");
		exit(-1);
	}
	else
	{
		T->stack[T->top]=ch;
		T->top++;
		printf("\nT   %d",T->top);
	}
}

void traveres1(STACK1 *S)
{
	int i=0;
	for(i=0;i<S->top;i++)
	{
		printf("\nS zhan %d de  di zhi :%c",i,S->stack[i]);
	}
	return ;
}
void traveres2(STACK2 *T)
{
	int i=0;
	for(i=0;i<T->top;i++)
	{
		printf("\nT zhan de di %d zhi :%d",i,T->stack[i]);
	}
	return ;
}

int gettop1(STACK1  S)
{
	if(S.top==0)
    {

        printf("\nfail qu zhan ding \n");
    }
    else
        return S.stack[S.top-1];
}
int gettop2(STACK2 T)
{
	if(T.top==0)
    {

        printf("\nfail qu zhan ding \n");
    }
    else
        return T.stack[T.top-1];
}
int precede(char a,char b)
{
	char t;
	if(a=='+'||a=='-')
			if(b=='+'||b=='-'||b=='('||b=='#')
		   {
		   		//t='>';
		   		 return 1;
			   }
	else
		{
			//t='<';
			return 2;

		}

	if(a=='*'||a=='/')
		if(b=='(')
		{
			//t='<';
			return 2;
		}

		else
		{
			//t='>';
			return 1;
		 }
	if(a=='(')
		if(b=')')
		{
			//t='=';
			return 3;
		}

		else
		{
			//t='<';
			return 2;
		}
	if(a==')')
		if(b!='(')
		{
			//t='>';
			return 1;
		}

    if(a=='#')
         if(b=='#')
         {
         	//t='=';
			return 3;
		 }

        else
		{
			//t='<';
		    return 2;
		 }
}

int main()
 {
	int a=100;
	int b;
     STACK1 S;
	 STACK2 T;
 	init1(&S);
 	init2(&T);
 	b=precede('#','+');
 	printf("\n ^^^^^%d",b);
 	//push1(&S,'#');
 	//push2(&T,4);

 	    //push2(&T,a);
 	    //push2(&T,8);                           // a=formula();
 	 //traveres1(&S);
    // traveres2(&T);
     //printf("\n Szhan ding yuansu%c", gettop1(S));
     //printf("\n Tzhan ding yuansu%d", gettop2(T));

 }
