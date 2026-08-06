#include <stdio.h>

#define BUFFER_SIZE 512

void printStream(FILE *stream);

int main (int argc, char *argv[])
{
    int status = 0;
    if (argc == 1)
    {
        printStream(stdin);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL)
            {
                perror(argv[i]);
                status = 1;
                continue;
            }
            printStream(fp);
            fclose(fp);
        }
    }
    return status;
}

void printStream (FILE *stream)
{
    char buff[BUFFER_SIZE];
    while(fgets(buff, BUFFER_SIZE, stream) != NULL)
    {
        printf("%s", buff);
    }
}
