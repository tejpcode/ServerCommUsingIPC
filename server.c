#include"header.h"
#include"declaration.h"
#include"datastructure.h"
#define fifo_name "FIFO"
int flag;
int main()
{
	int ret;
	FDS *data;
	data=(FDS*)malloc(sizeof(FDS));
	init();
	printf("Server waiting for client\n");
	data=(FDS*)(*fptr[1])(NULL);
	pthread_t id;
        pthread_attr_t atr;	
	ret=pthread_attr_init(&atr);
	if(ret != 0 )
	{
		perror("pthread_attr_init");
		exit(EXIT_FAILURE);
	}
	ret=pthread_attr_setdetachstate(&atr,PTHREAD_CREATE_DETACHED);
	if(ret != 0 )
	{
		perror("pthread_attr_setdetachstate");
		exit(EXIT_FAILURE);
	}
	flag=0;
	while(1)
	{
			ret=pthread_create(&id,&atr,&threadfunc,(void*)data);
			if(ret != 0 )
			{
				perror("pthread_create");
				exit(EXIT_FAILURE);
			}
			while(flag==0);
			flag=0;
		
	}
}
