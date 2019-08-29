#include <windows.h>
#include <stdio.h>

static int number=20;

DWORD WINAPI ThreadOne(LPVOID lpParameter)
{
	while(1)
	{
		if(number>0)
		{
			printf("窗口1售出第%d张票...\n",number);
			Sleep(100);
			number--;
		}
	}
	return 0;
}
DWORD WINAPI ThreadTwo(LPVOID lpParameter)
{
	while(1)
	{
		if(number>0)
		{
			printf("窗口2售出第%d张票...\n",number);
			Sleep(100);
			number--;
		}
	}
	return 0;
}


int main()
{
	HANDLE HOne,HTwo;
	printf("***********************vpoet******************\n");
	HOne=CreateThread(NULL,0,ThreadOne,NULL,0,NULL);
	printf("窗口1售票开始:\n");
	HTwo=CreateThread(NULL,0,ThreadTwo,NULL,0,NULL);
	printf("窗口2售票开始:\n");
	CloseHandle(HOne);
	CloseHandle(HTwo);
	while(TRUE)
	{
		if(number==0)
		{
			printf("MainThread Over!\n");
			return 0;
		}
		else
		{
			continue;
		}
	}

	return 0;
}
