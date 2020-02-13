
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SPLIT_CHARS " /'\n'" //chars to split string by

#define MAX_CMD_NUM 6	//max command number

#define CMD_EXIT 0 	//index command to close shell window
#define CMD_SHUTDOWN 1	//index command to shutdown all windows from main parent
#define CMD_BIN 2	//index Path for system programs
#define CMD_LS 3	//index command to show...
#define CMD_PS 4	//index command to show...
#define CMD_EXEC 5	//index command to execute a file


int main(void) {

char shellCMDList[][20] = {"exit","shutdown","bin","ls","ps","."};
char *terminalData[4];
char strPath[50]= "/bin/";
char strExec[50]= "./";

char cmd[50];

char userInput[50];
int cmdIndex = 0;
int state=0;

while(1){
	printf("\nsh > ");
	//Get user input command string
	fgets(userInput, sizeof(userInput),stdin);

	//Split string and get keywords
	terminalData[0] = strtok (userInput," /'\n'");
	for (int i = 0; i < 4; i++) {
		if(terminalData[i] != NULL){
			terminalData[i+1] = strtok (NULL," /'\n'");
		}
	}

	//Validate command
	for (cmdIndex = 0; cmdIndex < MAX_CMD_NUM; cmdIndex++) {
		//Compare array to current list of commands
		if(strcmp(terminalData[0],shellCMDList[cmdIndex]) == 0){

			//Execute commands
			switch (cmdIndex) {

				case CMD_EXIT:
					printf("Comando <exit>: %s\n",terminalData[0]);//<-diagnostic
					return 0;//3840;
					break;

				case CMD_SHUTDOWN:
					printf("Comando <shutdown>: %s\n",terminalData[0]);//<-diagnostic
					return 256;
					break;

				case CMD_BIN:
					if(terminalData[1]==NULL)//if Null, its an error
						break;

					strcpy(strPath,"/bin/");
					strcat(strPath,terminalData[1]);
					printf("Comando <bin>: %s",strPath);//<-diagnostic
					//execvp(strPath,terminalData[1]);					
					//execvp(strPath,terminalData);

					break;

				case CMD_EXEC:
					if(terminalData[2]==NULL){
						printf("Comando <execute1>: %s",terminalData[1]);//<-diagnostic
						//execvp(terminalData[0],"");
					}else{
						printf("Comando <execute2>: %s %s",terminalData[1],terminalData[2]);//<-diagnostic						
						//execvp(terminalData[0],terminalData[1]);
					}

					break;
				default: //all other commands

					if(terminalData[1]==NULL){
						printf("Comando <CMD>: %s",terminalData[0]);//<-diagnostic						
						execlp(terminalData[0],terminalData[0],(char *)NULL);
					}else{
						//printf("Comando <CMD>: %s %s",terminalData[0],terminalData[1]);//<-diagnostic
						//execvp(terminalData[0],terminalData[1]);
						printf("Comando <CMD>: %s %s",terminalData[0],terminalData[1]);//<-diagnostic
						strcpy(strPath,terminalData[0]);
						strcat(strPath," ");
						strcat(strPath,terminalData[1]);
						printf("Comando a enviar: %s", strPath);//<-diagnostic
						execlp(strPath,strPath,(char *)NULL);
					}

					break;
			}
			state=1;
			break;
		}else{
			state=0;
		}
	}//end for


}
	return 0;
}
