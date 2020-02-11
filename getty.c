/* Getty: takes inputs from user and compares them to a txt user/pass database */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define FILENAME "passwd.txt"

//Typedefs
struct loginData
{
  char user[15];
  char pass[15];
};

//Global Variables
struct loginData fullData[50];
int lineNumber;

//Function definitions

void parseFile()
{
  /* Se abre el archivo */
  FILE* openedFile = fopen(FILENAME, "rt");
  char textLine[35];
  char *pch;
  lineNumber = 0;

  if(NULL != openedFile) //Si no esta vacio
  {
    while(fgets(textLine, sizeof(textLine), openedFile))  //Se realiza un parse linea por linea
    {
      //Se separa el usuario y contraseña y se almacenan en la estructura
      pch = strtok(textLine, ":");
      strcpy(fullData[lineNumber].user, pch);
      pch = strtok (NULL, ":");
      strcpy(fullData[lineNumber].pass, pch);
      lineNumber++;
    }
  }
  else
    printf("Error al abrir el archivo...");
  fclose(openedFile);
}

int passCheck(char userInput[], char passInput[])
{
  for(int i=0;i<lineNumber;i++)
  {
    if(0 == strcmp(userInput, fullData[i].user) && 0 == strcmp(passInput, fullData[i].pass))
      return 1;
  }
  return 0;
}

int main ()
{
  char userInput[15];
  char passInput[15];
  int status;
  pid_t pid;

  while(1)
  {
    //wait(&status);

    parseFile();

    printf("**********************\n*     CHECK  PASS    *\n**********************\n\n\n");
    printf("getty $ Username: ");
    scanf("%s",userInput);
    printf("getty $ Password: ");
    scanf("%s",passInput);

    if(passCheck(userInput, passInput))
    {
      pid = fork();

      if(0 == pid)
        execlp("./sh", "sh", NULL);
      wait(&status);

      if(256 == status)
      {
        printf("Shutdown\n");
        sleep(2);
        execlp("pkill", "pkill", "-TERM", "-P", NULL);
      }
    }else
      printf("Usuario o password invalido, intenta de nuevo...\n");
  }
  return 0;
}