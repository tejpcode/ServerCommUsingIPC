#include"header.h"
#include"declaration.h"
#include"datastructure.h"
struct sembuf str;
int main()
{
	Result add;
	int FD,ret,rfd,cntrl,mkey,key;
	key=semget((key_t)123,4,0666|IPC_CREAT);
	Server data;
	FD=open("FIFO",O_WRONLY);
	data.PID=getpid();
	data.operators='+';
	data.d1=10;
	data.d2=22;
	str.sem_num=0;
	str.sem_op=-1;
	str.sem_flg=SEM_UNDO;
	ret=semop(key,&str,1);
	if(ret==-1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	ret=write(FD,&data,sizeof(Server));
	if(ret==-1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	str.sem_num=0;
	str.sem_op=1;
	str.sem_flg=SEM_UNDO;
	semop(key,&str,1);
	mkey=msgget((key_t)123,0666|IPC_CREAT);
	if(mkey==-1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	ret=msgrcv((key_t)mkey,(void*)&add,sizeof(Result),getpid(),0);
	if(ret==-1)
	{
		perror("msgrcv");
		exit(EXIT_FAILURE);
	}
	printf(">>>>%s RESULT:%d	PID: %d\n",__FILE__,add.result,add.PID);
	close(FD);
	exit(0);
}
