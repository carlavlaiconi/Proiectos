#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<wait.h>
#include<sys/types.h>
#include "cd1.h"
#include "tail1.h"
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include "uniq1.h"
#include "externalCommand.h"

void help (char ** command )
{
    if( command[1] != NULL)
    {
        if ( strcmp(command[1], "tail")==0)
            printf("\n\nUsage: tail [OPTION]... [FILE]...\nPrint the last 10 lines of each FILE to standard output.\nWith more than one FILE, precede each with a header giving the file name.\n\nWith no FILE, or when FILE is -, read standard input.\n\nMandatory arguments to long options are mandatory for short options too.\n\n  -c, --bytes=[+]NUM       output the last NUM bytes; or use -c +NUM to\n                             output starting with byte NUM of each file\n\n  -n, --lines=[+]NUM       output the last NUM lines, instead of the last 10;\n                             or use -n +NUM to output starting with line NUM\n\n  -q, --quiet, --silent    never output headers giving file names\n\n  -v, --verbose            always output headers giving file names\n\n\nGNU coreutils online help: <https://www.gnu.org/software/coreutils/>\nFull documentation <https://www.gnu.org/software/coreutils/tail>\n");
        else if ( strcmp(command[1], "cd")==0)
            printf("\n\nUsage: cd [dir]\n\nChange the shell working directory.\n\nChange the current directory to DIR.  The default DIR is the value of the\nHOME shell variable.\n\nThe variable CDPATH defines the search path for the directory containing\nDIR.\nA null directory name is the same as the current directory.  If DIR begins\nwith a slash (/), then CDPATH is not used.\n\nIf the directory is not found, and the shell option `cdable_vars' is set,\nthe word is assumed to be  a variable name.  If that variable has a value,\nits value is used for DIR.\n\nThe default is to follow symbolic links.\n`..' is processed by removing the immediately previous pathname component\nback to a slash or the beginning of DIR.\n\nExit Status:\nReturns 0 if the directory is changed, and if $PWD is set successfully when\n-P is used; non-zero otherwise.\n");
        else if ( strcmp(command[1], "uniq")==0)
            printf("\n\nUsage: uniq [OPTION]... [INPUT [OUTPUT]]\n\nFilter adjacent matching lines from INPUT (or standard input),\nwriting to OUTPUT (or standard output).\n\nWith no options, matching lines are merged to the first occurrence.\n\nMandatory arguments to long options are mandatory for short options too.\n  -d, --repeated        only print duplicate lines, one for each group\n  -i, --ignore-case     ignore differences in case when comparing\n  -u, --unique          only print unique lines\n\nA field is a run of blanks (usually spaces and/or TABs), then non-blank\ncharacters.  Fields are skipped before chars.\n\nNote: 'uniq' does not detect repeated lines unless they are adjacent.\nYou may want to sort the input first, or use 'sort -u' without 'uniq'.\n\nGNU coreutils online help: <https://www.gnu.org/software/coreutils/>\nFull documentation <https://www.gnu.org/software/coreutils/uniq>\nor available locally via: info '(coreutils) uniq invocation'\n");
        }
    else
    {
        printf("\n\nUsage: tail [OPTION]... [FILE]...\nPrint the last 10 lines of each FILE to standard output.\nWith more than one FILE, precede each with a header giving the file name.\n\nWith no FILE, or when FILE is -, read standard input.\n\nMandatory arguments to long options are mandatory for short options too.\n\n  -c, --bytes=[+]NUM       output the last NUM bytes; or use -c +NUM to\n                             output starting with byte NUM of each file\n\n  -n, --lines=[+]NUM       output the last NUM lines, instead of the last 10;\n                             or use -n +NUM to output starting with line NUM\n\n  -q, --quiet, --silent    never output headers giving file names\n\n  -v, --verbose            always output headers giving file names\n\n\nGNU coreutils online help: <https://www.gnu.org/software/coreutils/>\nFull documentation <https://www.gnu.org/software/coreutils/tail>\n");
        printf("\n\nUsage: cd [dir]\n\nChange the shell working directory.\n\nChange the current directory to DIR.  The default DIR is the value of the\nHOME shell variable.\n\nThe variable CDPATH defines the search path for the directory containing\nDIR.\nA null directory name is the same as the current directory.  If DIR begins\nwith a slash (/), then CDPATH is not used.\n\nIf the directory is not found, and the shell option `cdable_vars' is set,\nthe word is assumed to be  a variable name.  If that variable has a value,\nits value is used for DIR.\n\nThe default is to follow symbolic links.\n`..' is processed by removing the immediately previous pathname component\nback to a slash or the beginning of DIR.\n\nExit Status:\nReturns 0 if the directory is changed, and if $PWD is set successfully when\n-P is used; non-zero otherwise.\n");
        printf("\n\nUsage: uniq [OPTION]... [INPUT [OUTPUT]]\n\nFilter adjacent matching lines from INPUT (or standard input),\nwriting to OUTPUT (or standard output).\n\nWith no options, matching lines are merged to the first occurrence.\n\nMandatory arguments to long options are mandatory for short options too.\n  -d, --repeated        only print duplicate lines, one for each group\n  -i, --ignore-case     ignore differences in case when comparing\n  -u, --unique          only print unique lines\n\nA field is a run of blanks (usually spaces and/or TABs), then non-blank\ncharacters.  Fields are skipped before chars.\n\nNote: 'uniq' does not detect repeated lines unless they are adjacent.\nYou may want to sort the input first, or use 'sort -u' without 'uniq'.\n\nGNU coreutils online help: <https://www.gnu.org/software/coreutils/>\nFull documentation <https://www.gnu.org/software/coreutils/uniq>\nor available locally via: info '(coreutils) uniq invocation'\n");

    }
}

void versionOfTerminal()
{
    printf("******************** \nAuthor : Vlaiconi Carla\nVersion : vxk--1.0.3.5\n******************** \n ");
}

int redirect(char* last_command)
{
    if (strchr(last_command, '>')!=NULL)
    {
        if( strchr(last_command, '>') == strrchr(last_command,'>'))
            return 1; // o sagetica
        else return 2; // doua sagetele
    }
    return -1; // nu avem sagetele
}


void executeCommands(int num_commands, char **commands)
{
    int main_pid=getpid();
    int i;
    int input_fd = 0;
    int pipes[2];
    int case_redirect = -1;
    char* token2;

    for (i = 0; i < num_commands; i++)
    {

        if(i== num_commands-1)
        {
            case_redirect = redirect(commands[i]);

            if(case_redirect != -1)
            {
                char copii[100];
                strcpy(copii, commands[i]);
                char* token1= strtok( copii, ">");
                free(commands[i]);
                commands[i]=malloc(sizeof(token1));
                strcpy(commands[i], token1);
                token1= strtok(NULL, ">");
                int aux = 0;
                while ( token1[aux]==' ')
                    aux++;
                token2 = malloc(sizeof(token1));
                strcpy(token2, token1+aux);

            }
        }
        char *args[10];
        int num_args = 0;
        char *token = strtok(commands[i], " ");
        while (token != NULL)
        {
            args[num_args] = token;
            num_args++;
            token = strtok(NULL, " ");
        }
        args[num_args] = NULL;

        if (i < num_commands - 1)
        {
            if (pipe(pipes) < 0)
            {
                perror("pipe");
                exit(1);
            }

        }
        if(strcmp(args[0], "cd")==0)
        {

            maincd(num_args, args);

        }else {

        // Fork the process
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // child process 
            if (dup2(input_fd, STDIN_FILENO) < 0)
            {
                perror("dup2");
                exit(1);
            }
            if (i < num_commands - 1)
            {
                if (dup2(pipes[1], STDOUT_FILENO) < 0)
                {
                    perror("dup2");
                    exit(1);
                }
            }

            // Close pipes
            if (input_fd != STDIN_FILENO)
            {
                close(input_fd);
            }

            if (i < num_commands - 1)
            {
                close(pipes[0]);
                close(pipes[1]);
            }

            if(i != num_commands-1)
            {
                // Execute commands

                if(strcmp(args[0], "exit")!=0)
                {
                    if(strcmp(args[0], "uniq")==0)
                    {
                        mainuniq(num_args, args);
                    }
                    else if(strcmp(args[0], "tail")==0)
                    {
                        maintail(num_args, args);
                    }
                    else if(strcmp(args[0], "help")==0)
                    {
                        help(args);
                    }
                    else if(strcmp(args[0], "version")==0)
                    {
                        versionOfTerminal();
                    }
                    else if (strcmp(args[0], "exit")!=0)
                    {
                        if (execvp(args[0], args) < 0)
                        {
                            perror("execvp");
                            exit(1);
                        }

                    }
                    else if (strcmp(args[0], "exit")==0)
                        exit(0);
                    if(getpid()!=main_pid)
                        exit(0);
                }
                else exit(0);
            }
            else
            {
                if(case_redirect == -1)
                {

                    if(strcmp(args[0], "exit")!=0)
                    {
                        if(strcmp(args[0], "uniq")==0)
                        {
                            mainuniq(num_args, args);
                        }
                        else if(strcmp(args[0], "tail")==0)
                        {
                            maintail(num_args, args);
                        }
                        else if(strcmp(args[0], "help")==0)
                        {
                            help(args);
                        }
                        else if(strcmp(args[0], "version")==0)
                        {
                            versionOfTerminal();
                        }
                        else if (strcmp(args[0], "exit")!=0)
                        {
                            if (execvp(args[0], args) < 0)
                            {
                                perror("execvp");
                                exit(1);
                            }
                        }
                        else if (strcmp(args[0], "exit")==0)
                            exit(0);
                        if(getpid()!=main_pid)
                            exit(0);
                    }
                    else exit(0);
                }
                else if (case_redirect==1)
                {
                    int print_T= dup(STDOUT_FILENO);
                    int file_descriptor=open(token2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(file_descriptor, STDOUT_FILENO);
                    close(file_descriptor);
                    if(strcmp(args[0], "exit")!=0)
                    {
                        if(strcmp(args[0], "uniq")==0)
                        {
                            mainuniq(num_args, args);
                        }
                        else if(strcmp(args[0], "tail")==0)
                        {
                            maintail(num_args, args);
                        }
                        else if (strcmp(args[0], "exit")!=0)
                        {
                            if (execvp(args[0], args) < 0)
                            {
                                perror("execvp");
                                exit(1);
                            }
                        }
                        else if (strcmp(args[0], "exit")==0)
                            exit(0);
                        if(getpid()!=main_pid)
                            exit(0);
                    }
                    else exit(0);
                    dup2(print_T, STDOUT_FILENO);
                    close(print_T);


                }
                else if(case_redirect==2)
                {
                    int print_T= dup(STDOUT_FILENO);
                    int file_descriptor=open(token2, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(file_descriptor, STDOUT_FILENO);
                    close(file_descriptor);
                    if(strcmp(args[0], "exit")!=0)
                    {
                        if(strcmp(args[0], "uniq")==0)
                        {
                            mainuniq(num_args, args);
                        }
                        else if(strcmp(args[0], "tail")==0)
                        {
                            maintail(num_args, args);
                        }
                        else if (strcmp(args[0], "exit")!=0)
                        {
                            if (execvp(args[0], args) < 0)
                            {
                                perror("execvp");
                                exit(1);
                            }
                        }
                        else if (strcmp(args[0], "exit")==0)
                            exit(0);
                        if(getpid()!=main_pid)
                            exit(0);
                    }
                    else exit(0);
                    dup2(print_T, STDOUT_FILENO);
                    close(print_T);

                }
            }

        }

        else
        {
            //functie ca sa schimbam pipe-ul

            if (input_fd != STDIN_FILENO)
            {
                close(input_fd);
            }
            if (i < num_commands - 1)
            {
                close(pipes[1]);
            }
            input_fd = pipes[0];

        }
        }

    }
    for (i = 0; i < num_commands; i++)
        wait(NULL);

}



