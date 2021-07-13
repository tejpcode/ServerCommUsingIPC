typedef struct Server
{
	long int PID;
	char operators;
	int d1;
	int d2;
}Server;

typedef struct Result
{
	long int PID;
	int result;
	int flag;
}Result;
union semun {
        int val;                        /* value for SETVAL */
        struct semid_ds *buf;   /* buffer for IPC_STAT & IPC_SET */
        unsigned short *array;  /* array for GETALL & SETALL */
        struct seminfo *__buf;  /* buffer for IPC_INFO */
        void *__pad;
};
union semun unin;
typedef struct FDS
{
	int *pipefd;
	int FIFOFD;
	int mkey;
	char key[8];
	char pipe2[4];
	Result* res;
}FDS;
         


