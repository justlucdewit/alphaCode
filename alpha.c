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
    char** lines = malloc(lineCount*sizeof(char*));

    
    FILE* fptr = fopen(filename, "r");
    int currline = 0;

    for (int currline = 0; currline < lineCount; currline++){
        lines[currline] = malloc(MAXLINESIZE);
        fgets(lines[currline], MAXLINESIZE, fptr);
    }

    return lines;
}

void cmd_quit(int lineNr, int exitCode){
    printf("program exited on line %d with code %d\n", lineNr, exitCode);
    exit(0);
}

void run(char* filename){
    int numOfLines = countlines(filename);
    char** code = read(filename);

    char command[30];
    char firstchar;
    int arg1;

    int lineNr = 0;


    while(lineNr <= numOfLines){
        //printf("now on line %d\n", lineNr);
        //* comments
        if (sscanf(code[lineNr], "%c", &firstchar) == 1 && firstchar == '#'){
            lineNr++;
            continue;//line is a comment
        }

        //* exit
        if (sscanf(code[lineNr], "%30s", command) == 1 && strcmp(command, "exit") == 0){
            if (sscanf(code[lineNr], "%s %d", command, &arg1) == 2){
                cmd_quit(lineNr+1, arg1);
            }else{
                //! not enough arguments supplied for exit command
                printf("[ERROR 001] exit command on line %d needs a argument to indicate the exit-code\n", lineNr+1);
            }
        }

        //*print
        if (sscanf(code[lineNr], "%30s", command) == 1 && strcmp(command, "print") == 0){
            int pos = 6;
            while (code[lineNr][pos] != '\n'){
                putchar(code[lineNr][pos]);
                pos++;
            }

            putchar('\n');
        }

        //* goto
        if (sscanf(code[lineNr], "%30s", command) == 1 && strcmp(command, "goto") == 0){
            if (sscanf(code[lineNr], "%30s %d", command, &arg1) == 2){
                lineNr = arg1-1;
                continue;
            }else{
                //! not enough arguments supplied for goto command
                printf("[ERROR 002] exit command on line %d needs a argument to indicate the exit-code\n", lineNr+1);
            }
        }

        lineNr++;
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