#include <stdio.h>

#define BUFFER_SIZE 512

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./mycat <filename>\n");
        return 1;
    }

    char buff[BUFFER_SIZE];

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        return 1;
    }

    while(fgets(buff, BUFFER_SIZE, fp) != NULL)
    {
        printf("%s", buff);
    }
    fclose(fp);
    return 0;
}
