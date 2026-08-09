/*
 * TrixieBSD
 * ========================
 *
 * Component   : cat
 * Description : Prototype implementation of a cat-like utility.
 *
 * Status      : Experimental / Prototype
 * Target      : Trixie userspace
 *
 * Copyright (c) 2026 Bryann Brzoskowski
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * This implementation is part of the early development work
 * toward the TrixieBSD operating system and is not representative
 * of the final TrixieBSD userspace architecture.
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 512

int printStream(int);

int main (int argc, char *argv[])
{
    int status = 0;
    int result = 0;

    if (argc == 1)  // No files provided: read from stdin
    {
        result = printStream(STDIN_FILENO);
        if (result == 1)
        {
            status = 1;
        }
    }
    else    // Files provided
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

            if (close(fd) == -1)
            {
                perror("close");
                status = 1;
            }
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
        bytesWritten = write(STDOUT_FILENO, buff, bytesRead);

        if (bytesWritten == -1)
        {
            perror("write");
            return 1;
        }
        if (bytesWritten == 0)
        {
            return 1;
        }
        
        // write remaning bytes if bytesWritten is less than bytesRead
        while (bytesWritten < bytesRead)
        {
            currentWrite = write(STDOUT_FILENO, buff + bytesWritten, bytesRead - bytesWritten);

            if (currentWrite == -1)
            {
                perror("write");
                return 1;
            }
            if (currentWrite == 0)
            {
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
