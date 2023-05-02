#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>
#include<stdlib.h>
#include "cd1.h"

int maincd(int argc, char** argv)
{
    //printf("am intrat\n");

    char* directory;
    if (argc < 2)
    {
        directory = getenv("HOME");
    }
    else if (strcmp(argv[1], "..") == 0)
    {
        directory = "..";
    }
    else if (strcmp(argv[1], "/") == 0)
    {
        directory = "/";
    }
    else
    {
        directory = argv[1];
    }

    if (chdir(directory) != 0)
    {
        perror("Error");
        return 1;
    }
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s", cwd);

    }
    else
    {
        perror("getcwd() error");
        return 1;
    }


    return 0;
}

