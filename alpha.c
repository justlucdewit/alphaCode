/*
    alpha code is a project started by luc de wit
    it was started on 12-2-2020

    it was originally meant to be a improvement on
    the language zettacode made by joseph catanzarit
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
commands:
    comments
        # the text after this will be ignored
    
    exit [int]
        will quit the execution of the program emediatly
        and return its argument as exit-code

    print [str/int]
        will print its first argument to the console
        line

    goto [int]
        will change the current reading position of the
        program, and continue on that line given as the first argument

    def [str] [str/int]
        will store the string or int in the second argument
        as a variable with the name given as the first argument    

    debug
        will print a list of all currently available variables
*/

#define MAXLINESIZE 1000
#define VARIABLESIZELIM 1000 //! this shouldnt be a thing

typedef enum Types{
    alph_int,
    alph_str
}alph_type;

struct variable{
    char* key;
    alph_type type;
    union{
        char* str_val;
        int int_val;
    };
};

//? look into strstr()
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

    char strarg1[258];
    char strarg2[258];
    int arg1;

    int lineNr = 0;
    int numOfVars = 0;

    struct variable *memory = malloc(1);


    while(lineNr <= numOfLines){
        //printf("now on line %d\n", lineNr);
        //* comments
        if (sscanf(code[lineNr], "%c", &firstchar) == 1 && firstchar == '#'){
            lineNr++;
            continue;//line is a comment
        }

        //*print
        if (strncmp(code[lineNr], "print", 5) == 0){
            int pos = 6;
            while (code[lineNr][pos] != '\n'){
                putchar(code[lineNr][pos]);
                pos++;
            }

            putchar('\n');
        }
        //* exit
        else if (strncmp(code[lineNr], "exit", 4) == 0){
            if (sscanf(code[lineNr], "%s %d", command, &arg1) == 2){
                cmd_quit(lineNr+1, arg1);
            }else{
                //! not enough arguments supplied for exit command
                printf("[ERROR 001] exit command on line %d needs a argument to indicate the exit-code\n", lineNr+1);
            }
        }


        //* goto
        else if (strncmp(code[lineNr], "goto", 4) == 0){
            if (sscanf(code[lineNr], "%30s %d", command, &arg1) == 2){
                lineNr = arg1-1;
                continue;
            }else{
                //! not enough arguments supplied for goto command
                printf("[ERROR 002] exit command on line %d needs a argument to indicate the exit-code\n", lineNr+1);
            }
        }

        //* def
        else if (strncmp(code[lineNr], "let", 3) == 0){
            //* define int variable
            if (sscanf(code[lineNr], "%30s %258s %d", command, strarg1, &arg1) == 3){
                // make a copy of the variable name string
                char *newvarname = malloc((sizeof(char))*258);
                strcpy(newvarname, strarg1);
                newvarname[257] = '\0';

                // create the variable struct
                struct variable newvar = {.key = newvarname, .type = alph_int, .int_val = arg1};
                
                //increase memory buffer size
                numOfVars++;
                memory = realloc(memory, (sizeof(newvar))*numOfVars);
                memory[numOfVars-1] = newvar;
            }

            //* define string variable
            else if (sscanf(code[lineNr], "%30s %258s %[a-zA-Z ]", command, strarg1, strarg2)){
                //make a copy of the variable name string
                char *newvarname = malloc((sizeof(char))*258);
                strcpy(newvarname, strarg1);
                newvarname[257] = '\0';

                //clone variable value in new buffer
                char *newvarvalue = malloc((sizeof(char))*strlen(strarg2));
                strcpy(newvarvalue, strarg2);

                //create the variable struct
                struct variable newvar = {.key = newvarname, .type = alph_str, .str_val = newvarvalue};

                //increase memory buffer size
                numOfVars++;
                memory = realloc(memory, (sizeof(newvar))*numOfVars);
                memory[numOfVars-1] = newvar;
            }
        }

        //* debug
        else if (strncmp(code[lineNr], "debug", 5) == 0){
            puts("[DEBUG] available variables:");
            for (int i = 0; i < numOfVars; i++){
                struct variable var = memory[i];
                if (var.type == alph_int){
                    printf("%s = %d\n", var.key, var.int_val);
                }

                else if (var.type == alph_str){
                    printf("%s = '%s'\n", var.key, var.str_val);
                }
            }
        }

        //read next line in the following itter         
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