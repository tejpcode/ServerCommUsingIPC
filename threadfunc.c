#include"header.h"
#include"declaration.h"
#include"datastructure.h"
void handler(int i)
{
	;
}
int flag;
void* threadfunc(void* arg)
{
	static int count=0;
	FDS* infradata;
	pthread_mutex_t mut;
	infradata=(FDS*)arg;
	int ret;
	Server data;
lab:
	ret=read((infradata->FIFOFD),&data,sizeof(Server));
	if(ret==0)
	{
		goto lab;
	}
	count++;
	printf("count:%d\n",count);
	signal(SIGINT,handler);
	signal(SIGCHLD,SIG_IGN);
	flag=1;
	ret=fork();
	switch(ret)
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			if(ret==-1)
			{
				perror("write");
				exit(EXIT_FAILURE);
			}
			if(data.operators=='+')
				execl("./addor","addor",infradata->pipe2,infradata->key,0);
			else if(data.operators=='-')
				execl("./substractor","substractor",infradata->pipe2,infradata->key,0);
			else if(data.operators=='*')
				execl("./mul","mul",infradata->pipe2,infradata->key,0);
			else if(data.operators=='/')
				execl("./divider","divider",infradata->pipe2,infradata->key,0);
			else 
				printf("Wrong Choice\n");
		default:
			ret=write(*(infradata->pipefd+1),&data,sizeof(Server));
			while(data.PID!=infradata->res->PID);
			ret=msgsnd((key_t)infradata->mkey,(void*)infradata->res,(size_t)sizeof(Result),(int)0);
			infradata->res->flag=1;
			if(ret==-1)
			{
				perror("msgsnd");
				exit(EXIT_FAILURE);
			}
	}
	pthread_exit(NULL);
}
