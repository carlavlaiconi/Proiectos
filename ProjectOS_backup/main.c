#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<wait.h>
#include<sys/types.h>
#include "executeCommands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


int main()
{
    int main_pid=getpid();
    char *input = readline(">_ ");
    add_history(input);;
    int k;


    while(strcmp(input, "exit")!=0)
    {

        if(strcmp(input, "exit")==0)
        {
            exit(0);
        }

        // separating each word from the input and storing it in the args array
        char *token;
        int lngth;
        char *args[100];
        int countarg=0;
        int ok=0;
        char* command="";
        token=strtok(input, " \n");
        while(token)
        {
            lngth=strlen(token);
            args[countarg]=malloc(sizeof(char)*lngth);
            strcpy(args[countarg++],token);
            token=strtok(NULL, " \n");
        }
        args[countarg]=NULL;

        // grouping the commands from the args based on the pipes, and storing them in the commands array  "ls -l" "|" "ping"

        char* commands[10];
        for(int i=0; i<9; i++)
            commands[i]=NULL;
        int length;
        int num_commands = 0;
        int i;
        for (i = 0; i < countarg; i++)
        {
            if (strcmp(args[i], "|") == 0)
            {
                num_commands++;
            }
            else
            {
                if (commands[num_commands] == NULL)
                {

                    commands[num_commands] = malloc(strlen(args[i]) + 1);
                    strcpy(commands[num_commands], args[i]);

                }
                else
                {
                    char aux[300];
                    strcpy(aux, commands[num_commands]);
                    strcat(aux, " ");
                    strcat(aux, args[i]);
                    aux[strlen(aux)]='\0';
                    free(commands[num_commands]);
                    commands[num_commands]=malloc(strlen(aux)+1);
                    strcpy(commands[num_commands], aux);

                }
            }

        }
        num_commands++;
        if (strcmp(commands[0], "exit")==0)
            exit(0);
        else
        {
            executeCommands(num_commands, commands);
        }
        if(getpid()!=main_pid)
            exit(0);

        free(input);
        input = readline(">_ ");
        add_history(input);
        if (strcmp(commands[0], "exit")==0)
            exit(0);

    }
}











