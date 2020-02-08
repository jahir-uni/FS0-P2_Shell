#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	int i;
	int status;
	pid_t p;
	char mypid[20];
	sprintf(mypid, "%d", getpid());
	//printf("Soy el proceso init, el padre, mi pid es: %d o %s\n", getpid(), mypid);
	for(i=0;i<6;i++)
	{
		p=fork();
		if(p==0) //es un proceso hijo
			execlp("xterm","xterm", "-e", "./getty", mypid, NULL);
	}
	//printf("Estado: %d", status);
	while(1)
	{
		wait(&status);
		if(status==3840)
			execlp("pkill", "pkill", "-TERM", "-P", mypid, NULL);
		p=fork();
		if(p==0) //es un proceso hijo
			execlp("xterm","xterm", "-e", "./getty", mypid, NULL);
	}
	
}

