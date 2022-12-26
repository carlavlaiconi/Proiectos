#include<stdio.h>
#include<string.h>




int main(int argc, char** argv) {
    char sir[100] = "";
    char histo[100][100];
    int hcount = 0;
    printf("$>");
    while (strcmp(sir, "exit") != 0) {
        scanf("%s", sir);
        int k=hcount;
        while(sir[0]=='\33' && (sir[2]=='A' || sir[2]=='B')) {
            if (sir[2]=='A')
                if(histo[k-1][0]!='\0' && k>=1){
                    printf("\n%s", histo[k-1]);
                    k--;
            	} else {printf("($)no more commands\n");
                        k=-1;}

            if (sir[2]=='B')
                if(histo[k+1][0]!='\0' && k<hcount){
                    printf("\n%s", histo[k+1]);
                    k++;
                    }else {printf("($)no more commands\n");
                            k=hcount;}

            printf("\n$>");
            scanf("%s", sir);
            if(strcmp(sir, "exit") == 0)
                return 0;
            if (strcmp(sir, "clear") == 0) system("clear");
        }

        if (sir[0]!='\33' ){
            strcpy(histo[hcount], sir);
            hcount++;
            }

        printf("\n$>");

        if(strchr('|', sir)!= NULL)
            if(strrchr('|', sir)==strchr('|', sir))
                int fd[2];


    }
    }









