#include"header.h"
#include"declaration.h"
#include"datastructure.h"
struct sembuf str;
//int counter;
int main(int argc,char* argv[])
{
	int ret;
	Server data;
	Result* res;
	res=(Result*)malloc(sizeof(Result));
	ret=read(atoi(argv[1]),&data,sizeof(Server));
	if(ret==-1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	str.sem_num=2;
	str.sem_op=-1;
	str.sem_flg=SEM_UNDO;
	semop(atoi(argv[2]),&str,1);
	ret=shmget((key_t)121,sizeof(Result),0666|IPC_CREAT);
	res=(Result*)shmat(ret,0,0);
	while(res->flag!=1);
	res->result=data.d1-data.d2;
	res->PID=data.PID;
	res->flag=0;
	str.sem_num=2;
	str.sem_op=0;
	str.sem_flg=SEM_UNDO;
	semop(atoi(argv[2]),&str,1);
	exit(0);
}

