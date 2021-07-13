#include"header.h"
#include"declaration.h"
int init()
{
	//printf("%s: BEGIN\n",__func__);
	fptr[0]=exitfunc;
	fptr[1]=infra;
	//printf("%s: END\n",__func__);
}
