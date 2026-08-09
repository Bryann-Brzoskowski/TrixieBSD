#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

#define AUTHORS \
    proper_name ("Bryann Brzoskowski")

int printStream(int);

int main (int argc, char *argv[])
{
    // error status
    int status = 0;
    int result = 0;

    if (argc == 1)  // If only 1 arg is provided
    {
        result = printStream(0);
        if (result == 1)
        {
            status = 1;
        }
    }
    else    // If 2 or more arguments
    {
        // Loops through each argv
        for (int i = 1; i < argc; i++)
        {
            // POSIX open each argv as O_RDONLY / Read-Only
            int fd = open(argv[i], O_RDONLY);
            
            // Checks if opening a file failed
            if (fd == -1)
            {
                perror(argv[i]);
                status = 1;
                continue;
            }
            result = printStream(fd);
            
            // Cecks if printStream  failed
            if (result == 1)
            {
                status = 1;
            }
            close(fd);
        }
    }
    return status;
}

// Read every file provided
int printStream (int fd)
{
    char buff[BUFFER_SIZE];
    ssize_t bytesRead;
    ssize_t bytesWritten;
    ssize_t currentWrite;

    while ((bytesRead = read(fd, buff, BUFFER_SIZE)) > 0)
    {
        bytesWritten = write(1, buff, bytesRead);

        if (bytesWritten == -1)
        {
            perror("write");
            return 1;
        }
        
        // write remaning bytes if bytesWritten is less than bytesRead
        while (bytesWritten < bytesRead)
        {
            currentWrite = write(1, buff + bytesWritten, bytesRead - bytesWritten);

            if (currentWrite == -1)
            {
                perror("write");
                return 1;
            }

            bytesWritten += currentWrite;
        }

    }

    if (bytesRead == -1)
    {
        perror("read");
        return 1;
    }
    return 0;
}
