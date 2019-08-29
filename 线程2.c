#include<stdio.h>
#include<windows.h>
#include<winnt.h>

DWORD WINAPI myfun1(LPVOID lpParameter );
DWORD WINAPI myfun2(LPVOID lpParameter );
int  main()
{
	HANDLE h1,h2;
	h1=::CreateThread(NULL,0,myfun1,NULL,0,NULL);
	printf("线程1开始运行！\r\n");
	h2=::CreateThread(NULL,0,myfun2,NULL,0,NULL);
	printf("线程2开始运行！\r\t");
	::CloseHandle(h1);
	::CloseHandle(h2);
	while(1){

		if(getchar()=='q')
		{
			return 0;
		}
		else
		{
			::Sleep(100);
		}
	}
	return 0;
 }
 DWORD WINAPI myfun1(LPVOID lpParameter ){


 }
/* #include <windows.h>

#include <stdio.h>
#include<time.h>

DWORD WINAPI ThreadProc1( LPVOID lpParam )
{
	int i=0;
	time_t timer;
	while(1)
	{
		timer=time(NULL);
		printf("The current time is: %s/n",asctime(localtime(&timer)));
		Sleep(1000);
	}
}

int  main()
{
	int i=0;
//让主线程进入循环，主线程若退出，子线程1，2会被系统“杀死”
//创建线程1
CreateThread(NULL, // default security attributes
0, // use default stack size
ThreadProc1, // thread function
NULL, // argument to thread function
0, // use default creation flags
NULL); // returns the thread identifier
	for(;;)
	{
	;
	}
	return 0;
}*/
