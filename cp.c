#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 512

int main (int argc, char *argv[])
{
    int status = 0;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        status = 1;
        return status;
    }

    int sourceFile = open(argv[1], O_RDONLY);
    if (sourceFile == -1)
    {
        perror(argv[1]);
        status = 1;
        return status;
    }

    int destFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFile == -1)
    {
        perror(argv[2]);
        close(sourceFile);
        status = 1;
        return status;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    ssize_t bytesWritten;
    ssize_t totalWritten;

    while ((bytesRead = read(sourceFile, buffer, BUFFER_SIZE)) > 0)
    {
        totalWritten = 0;
        
        while (totalWritten < bytesRead)
        {
            bytesWritten = write(destFile, buffer + totalWritten, bytesRead - totalWritten);
            if (bytesWritten == -1)
            {
                perror("write");
                status = 1;
                break;
            }
            if (bytesWritten == 0)
            {
                status = 1;
                break;
            }

            totalWritten += bytesWritten;
        }
        if (status != 0)
        {
            break;
        }
    }
    if (bytesRead == -1)
    {
        perror("read");
        status = 1;
    }

    if (close(sourceFile) == -1)
    {
        perror("close");
        status = 1;
    }
    if (close(destFile) == -1)
    {
        perror("close");
        status = 1;
    }

    return status;
}
