#include<windows.h>								//����ͷ�ļ�
#include<stdio.h>

int main()
{
	HANDLE hpip;								//���������ܵ����
	OVERLAPPED ovi={0};							//����ṹ�����
	char buf[200];								//�������ݻ�����
	DWORD readbuf;									//��ȡʵ�ʶ�ȡ�ֽ���
	hpip=CreateNamedPipe("\\\\.\\pipe\\pipename", PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES,1024,1024,0,
		NULL);					 	//���������ܵ� 
	printf("�����ܵ��ɹ������ڵȴ��ͻ������ӣ�\r\n");
	if(::ConnectNamedPipe(hpip,&ovi))				//�ȴ��ͻ��˵���������
	{
		printf("�ͻ������ӳɹ���\r\n");
		printf("���ڶ�ȡ���ݣ�\r\n");					//��ʾ��Ϣ
		if(ReadFile(hpip,buf,200,&readbuf,NULL))		//��ȡ�ܵ�����
		{
			printf("���ݶ�ȡ�ɹ�\r\n");						//��ʾ��Ϣ
			printf("��ȡ�������ǣ�%s\r\n",buf);
		}
		else
		{
			printf("���ݶ�ȡʧ��\r\n");
		}
	}
	return 0;
}