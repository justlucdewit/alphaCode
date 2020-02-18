#include <stdio.h>

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