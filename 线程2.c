#include<stdio.h>
#include<windows.h>
#include<winnt.h>

DWORD WINAPI myfun1(LPVOID lpParameter );
DWORD WINAPI myfun2(LPVOID lpParameter );
int  main()
{
	HANDLE h1,h2;
	h1=::CreateThread(NULL,0,myfun1,NULL,0,NULL);
	printf("�߳�1��ʼ���У�\r\n");
	h2=::CreateThread(NULL,0,myfun2,NULL,0,NULL);
	printf("�߳�2��ʼ���У�\r\t");
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
//�����߳̽���ѭ�������߳����˳������߳�1��2�ᱻϵͳ��ɱ����
//�����߳�1
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
