#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFFER_SIZE 512

int main (int argc, char *argv[])
{
    int status = 0;

    if (argc != 2)
    {
        fprintf(stderr, "No file provided.\n");
        status = 1;
        return status;
    }

    int file = open(argv[1], O_RDONLY);
    if (file == -1)
    {
        perror(argv[1]);
        status = 1;
        return status;
    }

    char buff[BUFFER_SIZE];
    ssize_t bytesRead;
    ssize_t totalBytes = 0;
    ssize_t totalLines = 0;
    ssize_t totalWords = 0;
    bool inWord = false;

    while ((bytesRead = read(file, buff, BUFFER_SIZE)) > 0)
    {
        // process bytes
        totalBytes += bytesRead;
        
        for (ssize_t i = 0; i < bytesRead; i++)
        {
            if (buff[i] == '\n')
            {
                totalLines++;
            }

            if (isspace((unsigned char)buff[i]))
            {
                inWord = false;
            }
            else if (!inWord)
            {
                totalWords++;
                inWord = true;
            }
        }

    }

    if (bytesRead == -1)
    {
        perror("read");
        status = 1;
    }
    else
    {
        printf("%zd %zd %zd %s\n", 
                totalLines, totalWords, totalBytes, argv[1]);
    }

    // Closing the file
    if (close(file) == -1)
    {
        perror("close");
        status = 1;
    }

    return status;
}
