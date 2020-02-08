#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct UserNames 
{
	char UserName[15];
} Names;

typedef struct UserPasswords 
{
    	char UserPass[15];
} Passwords;

void ReadFile();
int CheckUser();

Names *P_Names;
Passwords *P_Passwords;
int NumberOfElements=0;

int main(int argc, char **argv)
{
   	char V_UserName[15];
   	char V_UserPassword[15];
   	char archivo[]="passwd.txt";
	int status;
	pid_t p;
	char ppid[20];
	strcpy(ppid, argv[1]);
	printf("%s\n",ppid);

   	while(1)
  	{
    		wait(&status);
    		printf("gt > User: ");
     		scanf("%s", V_UserName);
     		printf("gt > Password: ");
     		scanf("%s", V_UserPassword);
     		ReadFile(archivo);

     		if(CheckUser(V_UserName, V_UserPassword))			
        	{
			//printf("Ejecutando getty\n");
			p=fork();
			if(p==0)
				execlp("./sh", "sh", NULL);
			wait(&status);
			printf("STATUS SH: %d\n", status);

			if(status==256) //shutdown
			{	
				printf("Shutdown %s\n", ppid);
				sleep(2);
				execlp("pkill", "pkill", "-TERM", "-P", argv[1], NULL);
			}	
        	}
     		else 
        		printf("Invalid user/password. Try again.\n");
    	}
}

int CheckUser (char User[], char Pass []) 
{
   	int i;
   	for(i=0;i<NumberOfElements;i++)
	{
      		if (strcmp(User,P_Names[i].UserName) == 0 && strcmp(Pass,P_Passwords[i].UserPass) == 0)
         	return 1;
   	}
   	return 0;
}

void ReadFile (char AnyFile[]) 
{
    	// LEER ARCHIVO Y GUARDAR EN ESTRUCTURAS
    	FILE * names;
    	names = fopen(AnyFile, "rt");
 
    	if (names!=NULL)
	{
        	/* Nombres */
        	P_Names=(Names*)malloc(sizeof(Names));
        	/* Contraseñas */
        	P_Passwords=(Passwords*)malloc(sizeof(Passwords));
        	char F_String [37]; 
        	int Aux1=0, Aux2=1;
        	int i=0, j=0, k=0;
        
        	while(!feof(names))
            	{
                	fgets(F_String, 37, names);
                	i=0, j=0;

                	while((F_String[i]!='\n')&&(F_String[i]!='\0'))
			{

                   		while(F_String[i]!=':')
                       		{
                           		P_Names[Aux1].UserName[i]=F_String[i];
                           		i++;
                       		}
                   		P_Names[Aux1].UserName[i]='\0';
                   		i++; 

                   		while((F_String[i]!='\n')&&(F_String[i]!='\0'))
		               	{
		                   	P_Passwords[Aux1].UserPass[j]=F_String[i];
		                   	i++, j++;
		               	}
		           	P_Passwords[Aux1].UserPass[i]='\0';
		           	Aux1++, Aux2++;
		           	P_Passwords=(Passwords*)realloc(P_Passwords, (sizeof(Passwords)*Aux2));
		           	P_Names=(Names*)realloc(P_Names, (sizeof(Names)*Aux2));
		           	NumberOfElements++;
           		}   
		}
	}
    	// EN CASO DE QUE NO PUEDA ABRIRSE EL ARCHIVO
    	else 
		printf("No se puede abrir el archivo.");
    	fclose(names);
}

