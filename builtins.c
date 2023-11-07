#include "main.h"

void cdfun(char **args)
{
        if (args[1] == NULL)
        {
                fprintf(stderr, "./shell: cd missing arguments\n");
        }
        else if (chdir(args[1]) != 0)
                perror("./shell: no directory");
}

void exitfun(char **args)
{
        if (args[1])
                exit(atoi(args[1]));
        exit(0);
}