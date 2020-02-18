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

struct variable findVariable(char* varname, struct variable *memory, int searchArea, int lineNr){
    for (int i = 0; i < searchArea; i++){
        if (strcmp(memory[i].key, varname)==0){
            return memory[i];
        }
    }

    doError(1, lineNr);
}