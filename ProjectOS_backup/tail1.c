#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "tail1.h"



void print_usage(char *progname)
{
    fprintf(stderr, "Usage: %s [-c num_bytes] [-n num_lines] [-v] [-q] [file...]\n", progname);
}



int maintail(int argc, char*argv[])
{
    int opt;
    int c=0;
    int n=0;
    int numberLines=10;
    int numberBytes=10;
    int verbose = 0;
    int quiet = 0;
    char buffer[1024]="";
    int lines_to_print = numberLines;
    int bytes_to_print = numberBytes;
    int number_of_lines_of_file =0;
    int number_of_bytes_of_file =0;
    int more_than_one_file=0;
    optind = 1;

    while ((opt = getopt(argc, argv, "c:n:vq")) != -1)
    {
        switch (opt)
        {
        case 'c':
            numberBytes = atoi(optarg);
            c=1;
            break;
        case 'n':
            numberLines = atoi(optarg);
            n=1;
            break;
        case 'v':
            verbose = 1;
            break;
        case 'q':
            quiet = 1;
            break;
        default:
            print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }


    if (optind >= argc)
    {
        // no input file
        strcpy(buffer, "");
        lines_to_print = numberLines;
        bytes_to_print = numberBytes;
         number_of_lines_of_file =0;
        number_of_bytes_of_file =0;
        char words[1024][1024];

        while (fgets(buffer, 1024, stdin) != NULL)
        {
            strcpy(words[number_of_lines_of_file], buffer);
            number_of_lines_of_file++;
            for(int i =0; i<strlen(buffer) ; i++)
                number_of_bytes_of_file++;
        }


// VERBOSE
            if (verbose)
            {
                printf("\n==> standard input <==\n");

                    if(n)
                    {
                        int lineToPrintFrom = number_of_lines_of_file - lines_to_print;
                        for(int i= lineToPrintFrom; i<number_of_lines_of_file; i++ )
                                printf("%s", words[i]);

                    }

                    else if(c)
                    {
                        int byteToPrintFrom = number_of_bytes_of_file - bytes_to_print;
                        int counter=0;
                        for(int i= 0; i<number_of_lines_of_file; i++ ){
                            for( int j = 0; words[i][j]; j++ ){
                            counter++;
                            if(counter>byteToPrintFrom)
                                printf("%c", words[i][j]);}
                        }

                    }
                    else
                    {
                        int lineToPrintFrom = number_of_lines_of_file - 10;
                        for(int i= lineToPrintFrom; i<number_of_lines_of_file; i++ )
                                printf("%s", words[i]);
                    }
            }
//QUIET
            else if (quiet)
            {
                if(n)
                    {
                        int lineToPrintFrom = number_of_lines_of_file - lines_to_print;
                        for(int i= lineToPrintFrom; i<number_of_lines_of_file; i++ )
                                printf("%s", words[i]);

                    }

                    else if(c)
                    {
                        int byteToPrintFrom = number_of_bytes_of_file - bytes_to_print;
                        int counter=0;
                        for(int i= 0; i<number_of_lines_of_file; i++ ){
                            for( int j = 0; words[i][j]; j++ ){
                            counter++;
                            if(counter>byteToPrintFrom)
                                printf("%c", words[i][j]);}
                        }

                    }
                    else
                    {
                        int lineToPrintFrom = number_of_lines_of_file - 10;
                        for(int i= lineToPrintFrom; i<number_of_lines_of_file; i++ )
                                printf("%s", words[i]);
                    }
            }

//BYTES
            else if(c)
            {
                int byteToPrintFrom = number_of_bytes_of_file - bytes_to_print;
                        int counter=0;
                        for(int i= 0; i<number_of_lines_of_file; i++ ){
                            for( int j = 0; words[i][j]; j++ ){
                            counter++;
                            if(counter>byteToPrintFrom)
                                printf("%c", words[i][j]);}
                        }
            }

// LINES

            else if(n)
            {
                int lineToPrintFrom = number_of_lines_of_file - lines_to_print;
                        for(int i= lineToPrintFrom; i<number_of_lines_of_file; i++ )
                                printf("%s", words[i]);


            }
//DEFAULT
            else
            {
                int lineToPrintFrom = number_of_lines_of_file - 10;
                        for(int i= lineToPrintFrom; i<number_of_lines_of_file; i++ )
                                printf("%s", words[i]);
        }
         }


    else
    {

        number_of_lines_of_file =0;
        number_of_bytes_of_file =0;
        bytes_to_print = numberBytes;
        lines_to_print = numberLines;
        more_than_one_file = argc - optind;

        for (int i = optind; i < argc; i++)
        {

            char *filename = argv[i];
            FILE* fd = fopen(filename, "r");
            if (fd == NULL)
            {
                perror("open");
                return 1;
            }
            else
            {
                char line[1000];
                number_of_lines_of_file =0;
                number_of_bytes_of_file =0;
                while (fgets(line, 1000, fd)!=NULL)
                {
                    number_of_lines_of_file++;
                    for(int i =0; i<strlen(line) ; i++)
                        number_of_bytes_of_file++;
                }
            }
            fclose(fd);
// VERBOSE
            if (verbose)
            {
                printf("\n==> %s <==\n", filename);

                char line[1000];
                char *filename = argv[i];
                int lineToPrintFrom;
                FILE* fd = fopen(filename, "r");
                if (fd == NULL)
                {
                    perror("open");
                    return 1;
                }
                else
                {
                    if(n)
                    {
                        lineToPrintFrom = number_of_lines_of_file - lines_to_print;
                        int counter=0;
                        while (fgets(line, 1000, fd)!=NULL)
                        {
                            counter++;
                            if(counter>lineToPrintFrom)
                                printf("%s", line);
                        }
                    }
                    else if(c)
                    {
                        int byteToPrintFrom = number_of_bytes_of_file - bytes_to_print;
                        int counter=0;
                        int character;
                        while ((character = fgetc(fd)) != EOF)
                        {
                            counter++;
                            if(counter>byteToPrintFrom)
                                printf("%c", character);
                        }

                    }
                    else
                    {
                        int lineToPrintFrom = number_of_lines_of_file - 10;
                        int counter=0;
                        while (fgets(line, 1000, fd)!=NULL)
                        {
                            counter++;
                            if(counter>lineToPrintFrom)
                                printf("%s", line);
                        }
                    }
                }
                fclose(fd);
            }
//QUIET
            else if (quiet)
            {
                char line[1000];
                int byteToPrintFrom;
                char *filename = argv[i];
                int lineToPrintFrom;
                FILE* fd = fopen(filename, "r");
                if (fd == NULL)
                {
                    perror("open");
                    return 1;
                }
                else
                {
                    if(n)
                    {
                        lineToPrintFrom = number_of_lines_of_file - lines_to_print;
                        int counter=0;
                        while (fgets(line, 1000, fd)!=NULL)
                        {
                            counter++;
                            if(counter>lineToPrintFrom)
                                printf("%s", line);
                        }
                    }
                    else if(c)
                    {
                        byteToPrintFrom = number_of_bytes_of_file - bytes_to_print;
                        int counter=0;
                        int character;
                        while ((character = fgetc(fd)) != EOF)
                        {
                            counter++;
                            if(counter>byteToPrintFrom)
                                printf("%c", character);
                        }

                    }
                    else
                    {


                        int lineToPrintFrom = number_of_lines_of_file - 10;
                        int counter=0;
                        while (fgets(line, 1000, fd)!=NULL)
                        {
                            counter++;
                            if(counter>lineToPrintFrom)
                                printf("%s", line);
                        }
                    }
                }
                fclose(fd);
                if(more_than_one_file>1 )
                    printf("\n\n");
            }

//BYTES
            else if(c)
            {
                if(more_than_one_file>1 && verbose==0 && quiet==0)
                    printf("\n==> %s <==\n", filename);
                char *filename = argv[i];
                FILE* fd = fopen(filename, "r");
                if (fd == NULL)
                {
                    perror("open");
                    return 1;
                }
                else
                {
                    int byteToPrintFrom = number_of_bytes_of_file - bytes_to_print;
                    int counter=0;
                    int character;
                    while ((character = fgetc(fd)) != EOF)
                    {
                        counter++;
                        if(counter>byteToPrintFrom)
                            printf("%c", character);
                    }
                }
                fclose(fd);
            }

// LINES

            else if(n)
            {
                if(more_than_one_file>1 && verbose==0 && quiet==0)
                    printf("\n==> %s <==\n", filename);
                char line[1000];
                char *filename = argv[i];
                FILE* fd = fopen(filename, "r");
                if (fd == NULL)
                {
                    perror("open");
                    return 1;
                }
                else
                {
                    int lineToPrintFrom = number_of_lines_of_file - lines_to_print;
                    int counter=0;
                    while (fgets(line, 1000, fd)!=NULL)
                    {
                        counter++;
                        if(counter>lineToPrintFrom)
                            printf("%s", line);
                    }
                }
                fclose(fd);

            }
//DEFAULT
            else
            {
                if(more_than_one_file>1 && verbose==0 && quiet==0)
                    printf("\n==> %s <==\n", filename);
                char line[1000];
                char *filename2 = argv[i];
                FILE* fd2 = fopen(filename2, "r");
                if (fd2 == NULL)
                {
                    perror("open");
                    return 1;
                }
                else
                {
                    int lineToPrintFrom = number_of_lines_of_file - 10;
                    int counter=0;
                    while (fgets(line, 1000, fd2)!=NULL)
                    {
                        counter++;
                        if(counter>lineToPrintFrom)
                            printf("%s", line);
                    }
                }
                fclose(fd2);

            }

        }
    }

    return 0;

}
