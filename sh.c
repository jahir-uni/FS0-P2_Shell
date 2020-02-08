#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void SeparateLine();
void ImprimirVariablesAmbiente();
int SegundoPlano();
void SepararStrings();
int UsaPath();
void PartePalabra();
void parse(char *line, char **argv);
const char *  TraerVariableBuscada(char String[], char barrera[], char barrera_char);
void BuscarVariable();
char * pch;
char * pch_variable;
char **array_variables;
int count=0;

int main()
{
    char v_command[100];
    char v_command_cpy[100];
    char string1[100];
    char string2[100];
    int number_words;
    int status;
    int segPl;
    int useP;
    pid_t p;
    char cons[200];
    char string_concat[100];

    printf("%d", getpid());

    while(1)//strcmp(v_command,"exit\n"))
    {
        printf("sh > ");
        fgets(v_command, 100, stdin);

        if(strncmp(v_command, "\n", sizeof(v_command) != 0))
        {
    
            strcpy(v_command_cpy,v_command);

            SeparateLine(v_command, " \n", 1);

            if(!strcmp(v_command, "export"))
            {
                strcpy(string2,v_command);
                strcpy(v_command_cpy,TraerVariableBuscada(v_command_cpy, "\n=\0$", '$'));
                if(strcmp(v_command_cpy, "PATH")!=0)
                    strcpy(cons, v_command_cpy);
                else
                    SeparateLine(string2, " \n", 0);
            }
            
            else if(!strcmp(v_command, "echo\0") || v_command[0]=='$')
            {
                strcpy(v_command_cpy,TraerVariableBuscada(v_command_cpy, " \n=$", '$'));
                if(strcmp(v_command, "PATH")!=0)
                    printf("%s\n", cons);
                else    
                    BuscarVariable(v_command_cpy);
                
            }
            else if(!strcmp(v_command, "shutdown"))
            {
                return 1;
            }
            else if(!strcmp(v_command, "exit"))
            {
                return 0;
            }
            else //ejemplo ./ls || /ls || /home/Desktop/kill -9 123
            {

                segPl=SegundoPlano(v_command_cpy);
                useP=UsaPath(v_command_cpy);

                SepararStrings(string1, string2, v_command_cpy);

                if(useP) // Usa el path
                {
                    if(segPl) // Esta en segundo plano
                    {
                        strcpy(string_concat, strcat(cons, string1));
                        p=fork();
                        if(p==0)
                        {

                            char *argu[64];
                            parse(string2,argu);
                            execvp(string_concat, argu);
                        }
                    }
                    else
                    {
                        strcpy(string_concat, strcat(cons, string1));
                        printf("%s",string_concat);
                        p=fork();
                        if(p==0)
                        {
                            char *argu[64];
                            parse(string2,argu);
                            if(sizeof(string2) != 100)
                                execvp(string1, argu);
                            else
                                execlp(string1,"proceso", NULL);
                        }
                        printf("ASD");

                        wait(&status);
                    }
                }
                else
                {
                    if(segPl)
                    {
                        p=fork();
                        if(p==0)
                        {
                            char *argu[64];
                            parse(string2,argu);
                            execvp(string1, argu);
                        }
                    }
                    else
                    {
                        printf("%lu", sizeof(string2));
                        p=fork();
                        if(p==0)
                        {
                            char *argu[64];
                            parse(string2,argu);
                            if(sizeof(string2) != 100)
                                execvp(string1, argu);
                            else
                                execlp(string1,"proceso", NULL);
                        }
                        wait(&status);
                    }
                }
            }
        }
    }
}


void SeparateLine(char String[], char limit[], int export)
{
    pch = strtok (String,limit);

      while (pch != NULL)
       {
            if(!export && strcmp("export", pch)!=0)
            {
            count++;
   
            if(count>0)
            {
                array_variables = (char**)realloc(array_variables, (count+1)*sizeof(*array_variables));
                array_variables[count-1] = (char*)malloc(sizeof(pch));
                strcpy(array_variables[count-1], pch);
            }
            
        }
        pch = strtok (NULL, limit);
    }
}

const char * TraerVariableBuscada(char String[], char barrera[], char barrera_char)
{
    int i=0;
    static char aux[20];

    if(String[0]==barrera_char)
    {
        for(i=0;i<strlen(String);i++)
        {
            if(String[i+1]!='\n')
            {
                aux[i]=String[i+1];
            }
        }
    
        return aux;
    }
    
    else {
            pch_variable = strtok (String,barrera);
              while (pch_variable != NULL){
                if(pch_variable[i]==barrera_char)
                    return pch_variable = strtok (NULL, barrera);//" \n=$");
                i++;
              }
    }    
    return "not found";
}

void SepararStrings(char String1[], char String2[], char FullString[]){
    int i;
    int j=0;
    int flag=0;
    for(i=0;i<strlen(FullString);i++){
        if(FullString[i]==' ' && !flag)
            {
             i++;
             flag++;
            }
        
        if (!flag)
            String1[i]=FullString[i];
        else
            if(FullString[i]!='\n' && FullString[i]!='\0'){
                String2[j]=FullString[i];
                j++;
            }
    }
    if(!flag){
        String2[0] = '\0';
        //strcpy(String2, temp);
    }
}

int SegundoPlano(char String[])
{
    if(String[(unsigned)strlen(String)-2] == '&')
        return 1;
    else
        return 0;
}

int UsaPath(char String[])
{
    if(String[0]=='.' || String[0]=='/')
        return 0;
    else
        return 1;
}


void BuscarVariable(char String[]){
    int i;
    for(i=0;i<count;i++)
           if(strncmp(String, array_variables[i], strlen(String))==0)
               printf("%s\n", array_variables[i]);
}

// Esta funcion fue tomada del link a la siguiente pagina web donde se ejemplifica el uso de execvp. Creado por CentOS
//    http://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/exec.html
void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     /* replace white spaces with 0    */
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' &&
                 *line != '\t' && *line != '\n')
               line++;             /* skip the argument until ...    */
     }
     *argv = '\0';                 /* mark the end of argument list  */
}
