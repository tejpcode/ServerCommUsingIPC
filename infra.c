#include"header.h"
#include"declaration.h"
#include"datastructure.h"
#define fifo_name "FIFO"
void* infra(void* arg)
{
	//printf("%s:BEGIN\n",__FILE__);
	int* ptr;
	int i,shmid;
	int key,ret;
	char pipe2[4];
	char ckey[8];
	FDS *data;
	data=(FDS*)malloc(sizeof(FDS));
	data->pipefd=(int*)malloc(sizeof(int)*2);
	ptr=(int*)malloc(sizeof(int)*2);
	for(i=0;i<2;i+=2)
	{
		pipe(ptr+i);
	}
	*(data->pipefd+0)=*(ptr+0);
	*(data->pipefd+1)=*(ptr+1);
	/*printf("IN FD%s\n",data->pipe2);
	for(i=0;i<2;i++)
	{
		printf("FD:%d\n",*(ptr+i));
	}*/
	 if(access(fifo_name,F_OK)==-1)
        {
                ret=mkfifo(fifo_name,0666);
                printf("FIFO CREATED\n");
                if(ret==-1)
                {
                        perror("mkfifo");
                        exit(EXIT_FAILURE);
                }
        }
        data->FIFOFD=open(fifo_name,O_RDONLY);
        if(data->FIFOFD==-1)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }
	data->res=(Result*)malloc(sizeof(Result));
	shmid=shmget((key_t)121,sizeof(Result),0666|IPC_CREAT);
        data->res=(Result*)shmat(shmid,0,0);
	data->res->flag=1;
 	data->mkey=msgget((key_t)123,0666|IPC_CREAT);
        if(data->mkey==-1)
        {
                perror("msgget");
                exit(EXIT_FAILURE);
        }
	
	key=semget((key_t)123,4,0666|IPC_CREAT);
	sprintf(ckey,"%d",key);
	strcpy(data->key,ckey);
	//printf("IN KEY%s\n",data->key);
	sprintf(pipe2,"%d",*(data->pipefd+0));
	strcpy(data->pipe2,pipe2);
	//printf("IN KEY%s\n",data->key);
	//printf("IN FD%s\n",data->pipe2);
	if(key==-1)
	{
		perror("semget");
		exit(EXIT_FAILURE);
	}
	unin.val=1;
	for(i=0;i<4;i++)
	{
		semctl(key,i,SETVAL,unin);
	}
	//printf("%s:END\n",__FILE__);
	return (void*)data;
}
