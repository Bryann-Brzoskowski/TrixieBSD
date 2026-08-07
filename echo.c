#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

void printStream(int);

int main (int argc, char *argv[])
{
    int status = 0;
    if (argc == 1)
    {
        printStream(0);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1)
            {
                perror(argv[i]);
                status = 1;
                continue;
            }
            printStream(fd);
            close(fd);
        }
    }
    return status;
}

void printStream (int fd)
{
    char buff[BUFFER_SIZE];
    ssize_t bytesRead;
    while((bytesRead = read(fd, buff, BUFFER_SIZE)) > 0)
    {
        write(1, buff, bytesRead);
    }
}
