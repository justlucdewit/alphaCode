#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINESIZE 1000

int countlines(char *filename)
{
    // count the number of lines in the file called filename                                    
    FILE *fp = fopen(filename,"r");
    int ch=0;
    int lines=0;

    if (fp == NULL) return 0;

    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        lines++;
    }
    fclose(fp);
    return lines;
}

char** read(char* filename){
    int lineCount = countlines(filename);
    printf("file has %d line\n", lineCount);
    char** lines = malloc(lineCount*sizeof(char*));

    
    FILE* fptr = fopen(filename, "r");
    int currline = 0;

    for (int currline = 0; currline < lineCount; currline++){
        lines[currline] = malloc(MAXLINESIZE);
        fgets(lines[currline], MAXLINESIZE, fptr);
    }

    return lines;
}

void run(char* filename){
    int numOfLines = countlines(filename);
    char** code = read(filename);

    for (int i = 0; i < numOfLines; i++){
        printf(code[i]);
    }
}

void main(int argc, char** argv){
    if (argc > 1){
        char* command = argv[1];
        if (strcmp(command, "run") == 0){
            if (argc > 2){
                run(argv[2]);
            }else{
                puts("not enough commands supplied, try \"alpha run programName.ac\"");
            }
        }

        else{
            puts("unkown command");
        }
    }else{
        puts("please specify a command");
    }
}