#include "main.h"

int exit_stat = 0;

/**
 * length - this function calculate the length of array of string
 * @array: array of string
 * Return: the length
*/
size_t length(char **array) 
{
    size_t length = 0;

    while (array[length] != NULL)
    {
        length++;
    }
    return (length);
}

/**
 * main - entry point
 * Return: 0
*/
int main(void)
{
        char *line = NULL, **tokens;
	size_t len = 0;
        const char *prompt = "(shell A&M)$ ";
        static int status = 0;
        long unsigned int envo = length(environ);

        while(1)
        {
		if(isatty(STDIN_FILENO) != 0)
		write(1,prompt,12);

		if (getline(&line, &len, stdin) == -1)
			break;

                tokens = parse(line);

                if(tokens[0])
                        status = execfun(tokens);
                exit_stat = status;
		if(tokens)
                        free(tokens);
        }
	if(line)
		free(line);
        if(envo != length(environ))      /*this should only work if i set or unset a new env var*/
                free(environ);          /*there was an infinite memorl leak*/
        exit(status);
        return (0);
}
