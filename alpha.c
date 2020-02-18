/*
    alpha code is a project started by luc de wit
    it was started on 12-2-2020

    it was originally meant to be a improvement on
    the language zettacode made by joseph catanzarit
*/

//330

#include <ctype.h>
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

//v1.1.7 will have variable printing
//v1.2 will have all functionality of zetacode

#define VERSION "alphaCode V1.1.7"
#define MAXLINESIZE 1000
#define VARIABLESIZELIM 1000 //! this shouldnt be a thing

#include "headers/numberOfParts.h"
#include "headers/errorMessages.h"
#include "headers/countlines.h"
#include "headers/isNumeric.h"
#include "headers/tokens.h"

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
        //printf("now on line %d\n", lineNr+1);
        //* comments
        if (sscanf(code[lineNr], "%c", &firstchar) == 1 && firstchar == '#'){
            lineNr++;
            continue;//line is a comment
        }

        //* print
        if (strncmp(code[lineNr], "print ", 6) == 0){
            int parts = numberOfParts(code[lineNr]);
            if (parts != 2){
                if (parts < 2){
                    doError(205, lineNr+1);
                }else{
                    doError(305, lineNr+1);
                }
            }


            char* string = malloc((sizeof(char))*(strlen(code[lineNr])-8));
            string[strlen(code[lineNr])-7] = '\0';
            if (sscanf(code[lineNr], "%s \"%[a-zA-Z _+-=*/^]\"", command,  string) == 2){
                printf("%s\n", string);
                putchar('\n');
            }else if (code[lineNr][6] != '"'){//printing a variable
                char *varname = malloc((sizeof(char))*256);
                sscanf(code[lineNr], "print %s", varname);
                struct variable varstruct = findVariable(varname, memory, numOfVars, lineNr);
                //printf("%s", varstruct.);

                if (varstruct.type == alph_str){
                    printf("%s\n", varstruct.str_val);
                }else{
                    printf("%d", varstruct.int_val);
                }
            }else{
                doError(105, lineNr+1);
            }
        }

        //* exit
        else if (strncmp(code[lineNr], "exit ", 5) == 0){
            int parts = numberOfParts(code[lineNr]);
            if (parts != 2){
                if (parts < 2){
                    doError(201, lineNr+1);
                }else{
                    doError(301, lineNr+1);
                }
            }

            if (sscanf(code[lineNr], "%s %d", command, &arg1) == 2){
                cmd_quit(lineNr+1, arg1);
            }else{
                doError(101, lineNr+1);
            }
        }


        //* goto
        else if (strncmp(code[lineNr], "goto ", 5) == 0){
            int parts = numberOfParts(code[lineNr]);
            if (parts != 2){
                if (parts < 2){
                    doError(202, lineNr+1);
                }else{
                    doError(302, lineNr+1);
                }
            }

            if (sscanf(code[lineNr], "%30s %d", command, &arg1) == 2){
                lineNr = arg1-1;
                continue;
            }else{
                doError(102, lineNr+1);
            }
        }

        //* let
        else if (strncmp(code[lineNr], "let ", 4) == 0){
            int parts = numberOfParts(code[lineNr]);
            if (parts != 3){
                if (parts < 3){
                    doError(203, lineNr+1);
                }else{
                    doError(303, lineNr+1);
                }
            }

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
            else if (sscanf(code[lineNr], "%30s %258s \"%[a-zA-Z _+-=*/^]\"", command, strarg1, strarg2) == 3){
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

            else{
                doError(103, lineNr+1);
            }
        }

        //* get value
        else if (strncmp(code[lineNr], "get", 3) == 0){
            int parts = numberOfParts(code[lineNr]);
            if (parts != 2){
                if (parts < 2){
                    doError(204, lineNr+1);
                }else{
                    doError(304, lineNr+1);
                }
            }

            if (sscanf(code[lineNr], "get %256[a-zA-Z_]", strarg1) == 1){
                char *newvarname = malloc((sizeof(char))*258);
                strcpy(newvarname, strarg1);
                newvarname[257] = '\0';

                char *varVal = malloc((sizeof(char))*1000);//! limits shouldnt be a thing
                fgets(varVal, 1000, stdin);
                sscanf(varVal, "%[^\n]", varVal);
                
                struct variable newvar = {.key = newvarname, .type = alph_str, .str_val = varVal};
                
                numOfVars++;
                memory = realloc(memory, (sizeof(newvar))*numOfVars);
                memory[numOfVars-1] = newvar;
            }else{
                doError(104, lineNr+1);
            }
        }

        //* debug
        else if (strncmp(code[lineNr], "debug", 5) == 0){
            int parts = numberOfParts(code[lineNr]);
            if (parts != 1){
                doError(306, lineNr+1);
            }

            puts("\n[DEBUG] available variables:");
            for (int i = 0; i < numOfVars; i++){
                struct variable var = memory[i];
                if (var.type == alph_int){
                    printf("\t%s = %d\n", var.key, var.int_val);
                }

                else if (var.type == alph_str){
                    printf("\t%s = '%s'\n", var.key, var.str_val);
                }
            }
            puts("\n");
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

        if (strcmp(command, "version") == 0){
            puts(VERSION);
        }

        else{
            puts("unkown command");
        }
    }else{
        puts("please specify a command");
    }
}