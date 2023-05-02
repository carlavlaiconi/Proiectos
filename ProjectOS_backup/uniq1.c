#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "uniq1.h"

int compare_ignoring_case(const char *a, const char *b)
{
    char *a_copy = strdup(a);
    char *b_copy = strdup(b);
    for (int i = 0; a_copy[i]; i++)
        a_copy[i] = tolower(a_copy[i]);
    for (int i = 0; b_copy[i]; i++)
        b_copy[i] = tolower(b_copy[i]);
    int res = strcmp(a_copy, b_copy);
    free(a_copy);
    free(b_copy);
    return res;
}



int mainuniq(int argc, char *argv[])
{
    int only_duplicates = 0;
    int only_unique = 0;
    int ignore_case = 0;
    FILE *input_file = stdin;
    FILE *output_file = stdout;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            only_duplicates = 1;
        }
        else if (strcmp(argv[i], "-u") == 0)
        {
            only_unique = 1;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            ignore_case = 1;
        }
        else if (strcmp(argv[i], "-") != 0)
        {
            if (input_file == stdin)
            {
                input_file = fopen(argv[i], "r");
                if (input_file == NULL)
                {
                    fprintf(stderr, "Error: Could not open input file '%s'\n", argv[i]);
                    return 1;
                }
            }
            else
            {
                output_file = fopen(argv[i], "w");
                if (output_file == NULL)
                {
                    fprintf(stderr, "Error: Could not open output file '%s'\n", argv[i]);
                    return 1;
                }
            }
        }
        else
        {

        }

    }


    int prev_comparison=2;
    int actual_comparison=2;
    char * buffer = malloc(sizeof(char) * 1024);
    char *prev_line = NULL;


    while (fgets(buffer, 1024, input_file) != NULL)
    {
        int compare = -1;
        if(prev_line!=NULL)
        {
            //the case sensitive test
            if (ignore_case==1)
            {
                compare = compare_ignoring_case(prev_line, buffer);
            }
            else
            {
                compare = strcmp(prev_line, buffer);
            }
        }

        prev_comparison= actual_comparison;
        if(compare==0)
            actual_comparison=0;
        else
            actual_comparison=1;

        if(compare!=0 && prev_line!=NULL)
        {
            if(only_duplicates==0)
                if(only_unique==1)
                {
                    if(actual_comparison==1 &&  prev_comparison==1 )
                    {
                        if(output_file!=stdout)
                            fprintf(output_file, "%s", prev_line);
                        else printf("%s", prev_line);
                    }
                }
                else
                {
                    if(output_file!=stdout)
                        fprintf(output_file, "%s", prev_line);
                    else printf("%s", prev_line);
                }
        }
        else if(compare==0)
        {
            if(only_duplicates==1)
            {
                if(output_file!=stdout)
                    fprintf(output_file, "%s", prev_line);
                else printf("%s", prev_line);
            }
        }

        free(prev_line);
        prev_line = (char *)malloc(strlen(buffer) + 1);
        strcpy(prev_line, buffer);


    } //while closed

    if((only_unique==1 || ignore_case==1) || (only_unique==0 && ignore_case==0 && only_duplicates==0))
    {
        if(!(actual_comparison==0 && only_unique==1))
        {
            if(output_file!=stdout)
                fprintf(output_file, "%s", prev_line);
            else printf("%s", prev_line);
        }
    }

    free(prev_line);

    if (input_file != stdin)
    {
        fclose(input_file);
    }
    if (output_file != stdout)
    {
        fclose(output_file);
    }


    return 0;
} //function closed


