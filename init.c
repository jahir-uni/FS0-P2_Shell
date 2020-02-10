#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	int status;
	pid_t pfork;
	char mypid[20];

	sprintf(mypid, "%d", getpid());

	for(int i=0;i < 6;i++)
	{
		pfork = fork();
		if(0 == pfork) //Proceso Hijo
			execlp("xterm","xterm", "-e", "./getty", mypid, NULL);
	}
	while(1)
	{
		wait(&status);
		if(status==3840)
			execlp("pkill", "pkill", "-TERM", "-P", mypid, NULL);
		pfork = fork();
		if(0 == pfork) //si es un proceso hijo
			execlp("xterm","xterm", "-e", "./getty", mypid, NULL);
	}
	
}

