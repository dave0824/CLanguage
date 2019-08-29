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
		++S->top;
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
	}
}

void traveres1(STACK1 *S)
{
	int i=0;
	for(i=0;i<S->top;i++)
	{
		printf("\nS zhan %d de zhi :%c",i+1,S->stack[i]);
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
int in(char ch)
{

	if(ch=='+'||ch=='-'||ch=='/'||ch=='('||ch==')'||ch=='*'||ch=='#')
		return 1;
	else if(ch>='0'&&ch<='9')
		return 0;
	else
	{
		printf("shu ru you wu!\n");
		exit(-1);
	}
}
int precede(char a,char b)//1:>  2:<     3:=
{
	if(a=='+'||a=='-')
			if(b=='+'||b=='-'||b==')'||b=='#')
		   		 return 1;
	    else
			return 2;
	if(a=='*'||a=='/')
		if(b=='(')
			return 2;
		else
			return 1;
	if(a=='(')
		if(b!=')')
			return 2;
		else
			return 3;
	if(a==')')
		if(b!='(')
			return 1;
    if(a=='#')
         if(b=='#')
			return 3;
        else
		    return 2;
}
int  pop1(STACK1* S,char * val)
{
	int i =0;
	if(S->top!=0)
	{
		i=S->top-1;
		* val=S->stack[i];
		 S->top--;
		return  *val;
	}
	else
	{
		printf("\nS chu zhan shi bai\n");
		exit(-1);
	}
}
char pop2(STACK2* T,char * val)
{
	int i =0;
	if(T->top!=0)
	{
		i=T->top-1;
		* val=T->stack[i];
		T->top--;
		return  *val;
	}
	else
	{
		printf("\nT chu zhan shi bai\n");
		exit(-1);
	}
}
int operate(char a,char op,char b)
{
	switch (op)
	{
		case'+':
				return (a+b);
		case'-':
				return (a-b);
				break;
		case'*':
				return (a*b);
				break;
		case'/':
				return(a/b);

				break;
		default:
				printf("\nbu neng ji suan\n");
				break;
	}
}
int getnumber(char *ch)
{
	return (*ch-48);
}
int formula()
{
	STACK1 S;
	STACK2 T;
	char ch;
	int k =0;
	char val,a,b;
	char x;
	init1(&S);
 	init2(&T);
 	push1(&S,'#');
 	ch=getchar();
 	while(ch!='#'||gettop1(S)!='#')
 	{

 		if(!in(ch))
 		{
 			k=getnumber(&ch);
 			push2(&T,k);
 		    ch=getchar();
		 }
		 else
		 {
		     //printf("\n###########%c,%c\n",gettop1(S),ch);
		 	 switch (precede(gettop1(S),ch))
		 		{
		 			case 1://>
		 			  pop1(&S,&val);
		 			  pop2(&T,&a);
					   pop2(&T,&b);
		 			  push2 (&T,operate(b,val,a));
		 			  break;
		 			case 2://<
		 	    			 push1(&S,ch);
		 			         ch=getchar();
		 				     break;
		 			case 3://=
		 			  x=gettop1(S);
		 			  pop1(&S,&x);
		 			  ch=getchar();
		 			  break;
		 			  default:
					  printf("\n~~~~~~~~~~~%c\n",precede(gettop1(S),ch));
		 			  break;
				 }
		 }
	 }
 	return gettop2(T);
}
int main()
 {
	int a;
     STACK1 S;
	 STACK2 T;
 	init1(&S);
 	init2(&T);
 	a=formula();
 	printf("\nzui zhou da an:%d",a);
 	 //traveres1(&S);
     //traveres2(&T);

 }
