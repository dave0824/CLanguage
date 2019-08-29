#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
FILE *fp=NULL;
int i,j=0;
int mutex=1;
int num=0;
int cnt=0;//记录指针位置
char ch1 [1000];
char ch2 [100]={"Thanks to his Alma mater, the place where I grew up."};
int P(){
	if(mutex==1){

		mutex=mutex-1;
		return 1;
	}
	else{
		return 0;
	}
}
void V(){
	mutex=mutex+1;
}
void fileread(int count){
    			do{
				if(P()==1){
				fread(ch1,sizeof(char),1,fp);
				cnt++;
				Sleep(100);
				printf("%d--正在读文件----->%s\n",count,ch1);

				}
				V();
                }while(cnt<num);
}
void filewrite(int count){
    		while(j<strlen(ch2)){
			if(P()==1){
                fseek(fp,0L,SEEK_END);
				fwrite(&ch2[j++],sizeof(char),1,fp);
			Sleep(100);
			printf("%d**正在写文件----->\n",count);
			}
			V();
		}
}
DWORD WINAPI MyThreadRead1(LPVOID IpParameter){

    fileread(1);
	return 0;
}
DWORD WINAPI MyThreadRead2(LPVOID IpParameter){

    fileread(2);
	return 0;
}
DWORD WINAPI MyThreadRead3(LPVOID IpParameter){

     fileread(3);
	return 0;
}
DWORD WINAPI MyThreadWrite1(LPVOID IpParameter){

    filewrite(1);
	return 0;
}

DWORD WINAPI MyThreadWrite2(LPVOID IpParameter){

   	filewrite(2);
	return 0;
}
int main()
{
	HANDLE r1,r2,r3;
	HANDLE w1,w2;
	fp=fopen("char.txt","r+");
    while(!feof(fp))
    {
         fgetc(fp);
         num++;
    }
    fseek(fp,0,SEEK_SET);
	r1=CreateThread(NULL,0,MyThreadRead1,NULL,0,NULL);
	r2=CreateThread(NULL,0,MyThreadRead2,NULL,0,NULL);
	r3=CreateThread(NULL,0,MyThreadRead3,NULL,0,NULL);
	w1=CreateThread(NULL,0,MyThreadWrite1,NULL,0,NULL);
	w2=CreateThread(NULL,0,MyThreadWrite2,NULL,0,NULL);
	CloseHandle(r1);
	CloseHandle(r2);
	CloseHandle(r3);
	CloseHandle(w1);
	CloseHandle(w2);
	while(cnt<num);
	//fclose(fp);
	return 0;
}
