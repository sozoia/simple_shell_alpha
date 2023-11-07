#include "main.h"

char *readLine()
{
        char *line;
        size_t buflen = 0;
        ssize_t len = getline(&line, &buflen, stdin);
        errno = 0;

        if (len < 0)
        {
                if (errno)
                        perror("./shell: getline error");
                exit(1);
        }
        return (line);
}