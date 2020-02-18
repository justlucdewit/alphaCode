#include <string.h>

int numberOfParts(char* code){
  int pieces = 0;
  int len = strlen(code);

  int readingWord = 0;
  int readingstring = 0;

  for (int i = 0; i < len; i++){
    char letter = code[i];
    if (letter == '#'){
        break;
    }

    if (letter == '"'){
        if (readingstring){
            readingstring = 0;
        }else{
            readingstring = 1;
        }
    }

    if ((letter != '\n' && letter != ' ' && letter != '\t') || readingstring){
      readingWord = 1;
    }else if (readingWord){
      pieces += 1;
      readingWord = 0;
    }
  }

  if (readingWord){
    pieces += 1;
  }

  return pieces;
}