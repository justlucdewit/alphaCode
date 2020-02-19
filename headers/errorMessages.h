#include <stdio.h>
#include <stdlib.h>

void doError(int type, int lineNr){
    switch(type){
        //odd
        case 1: printf("[ERROR 001] variable not defined on line %d", lineNr);break;
        case 2: printf("[ERROR 002] trying to assign int to str variable on line %d", lineNr);break;
        case 3: printf("[ERRPR 003] trying to assign str to int variable on line %d", lineNr);break;

        //wrong arg type
        case 101: printf("[ERROR 101] exit command on line %d expects args of type [int]\n", lineNr);break;
        case 102: printf("[ERROR 102] goto command on line %d expects args of type [int]\n", lineNr);break;
        case 103: printf("[ERROR 103] let command on line %d expects args of type [str] [str/int]\n", lineNr);break;
        case 104: printf("[ERROR 104] get command on line %d expects args of type [str]\n", lineNr);break;
        case 105: printf("[ERROR 105] print command on line %d expects args of type [str/var]\n", lineNr);break;

        //to little args
        case 201: printf("[ERROR 201] exit command on line %d has to little arguments, it needs 1", lineNr);break;
        case 202: printf("[ERROR 202] goto command on line %d has to little arguments, it needs 1", lineNr);break;
        case 203: printf("[ERROR 203] let command on line %d has to little arguments, it needs 2", lineNr);break;
        case 204: printf("[ERROR 204] print command on line %d has to little arguments, it needs 1", lineNr);break;
        case 205: printf("[ERROR 205] get command on line %d has to little arguments, it needs 1", lineNr);break;

        //to many args
        case 301: printf("[ERROR 301] exit command on line %d has to many arguments, it needs 1", lineNr);break;
        case 302: printf("[ERROR 302] goto command on line %d has to many arguments, it needs 1", lineNr);break;
        case 303: printf("[ERROR 303] let command on line %d has to many arguments, it needs 2", lineNr);break;
        case 304: printf("[ERROR 304] get command on line %d has to many arguments, it needs 1", lineNr);break;
        case 305: printf("[ERROR 305] print command on line %d has to many arguments, it needs 1", lineNr);break;
        case 306: printf("[ERROR 306] debug command on line %d has to many arguments, it needs 0", lineNr);break;

        default: printf("[ERROR 69420] unreachable state reached");
    }
    exit(1);
}