
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPLIT_CHARS " /"

#define MAX_CMD_NUM 6

#define CMD_EXIT 0
#define CMD_SHUTDOWN 1
#define CMD_BIN 2
#define CMD_LS 3
#define CMD_PS 4
#define CMD_EXEC 5


char shellCMDList[][20] = {"exit","shutdown","bin","ls","ps","."};
char *terminalData[4];
char strPath[50]= "/bin/";
char strExec[50]= "./";

char userInput[50];
int cmdIndex = 0;
int state=0;

char str[] = "./prog parm";//"./programa parametro";

int main(void) {
while(1){
	printf("\nsh > ");
	scanf("%s",userInput);

	//Split string and get keywords
	terminalData[0] = strtok (str,SPLIT_CHARS);
	//terminalData[0] = strtok (userInput," /");
	for (int i = 0; i < 4; i++) {
		if(terminalData[i] != NULL){
			terminalData[i+1] = strtok (NULL," /");
		}
	}

	//Validate command
	for (cmdIndex = 0; cmdIndex < MAX_CMD_NUM; cmdIndex++) {
		//Compare array to current list of commands
		if(strcmp(terminalData[0],shellCMDList[cmdIndex]) == 0){


			switch (cmdIndex) {

				case CMD_EXIT:
					printf("Comando <exit>: %s",terminalData[0]);//<-diagnostic
					//return 0;//3840;
					break;

				case CMD_SHUTDOWN:
					printf("Comando <shutdown>: %s",terminalData[0]);//<-diagnostic
					//return 256;
					break;

				case CMD_BIN:
					if(terminalData[1]==NULL)//if Null, its an error
						break;

					strcat(strPath,terminalData[1]);
					printf("Comando <bin>: %s",strPath);//<-diagnostic
					//execvp(strPath[],terminalData[1]);

					break;

				case CMD_EXEC:
					if(terminalData[2]==NULL){
						printf("Comando <execute1>: %s",terminalData[1]);//<-diagnostic
						//execvp(terminalData[0],"");
					}else{
						printf("Comando <execute2>: %s ",terminalData[1]);//<-diagnostic
						printf("*=%s _",terminalData[2]);
						//execvp(terminalData[0],terminalData[1]);
					}

					break;
				default:

					if(terminalData[1]==NULL){
						printf("Comando <CMD>: %s",terminalData[0]);//<-diagnostic
						//execvp(terminalData[0],terminalData[1]);
					}else{
						printf("Comando <CMD>: %s%s",terminalData[0],terminalData[1]);//<-diagnostic
						//execvp(terminalData[0],terminalData[1]);
					}

					break;
			}
			state=1;
			break;
		}else{
			state=0;
		}
	}//end for

	printf("\nResult state: %d",state);//<-diagnostic
	/*int result = strcmp(terminalData[0],shellCMDList[5]); //just testing
	printf("Resultado comp: %d\n",result);*/



}
	return 0;
}

