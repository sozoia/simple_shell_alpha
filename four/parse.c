#include "main.h"

/**
 * parse - split the input
 * @line: command
 * Return: array of splited command
*/
char **parse(char *line)
{
        int len = 0;
        int cap = ARGBUF;
        char **tokens;
        char *token;

	tokens = malloc(cap * sizeof(char *));
        if (!tokens)
        {
                perror("./shell: tokens error");
                return(NULL);
        }

        token = strtok(line, DELIMIT);

        while (token != NULL)
        {
                tokens[len++] = token;
                if (len >= cap)
                {
                        cap += ARGBUF + 1;
                        tokens = realloc(tokens, cap);
                        if (!tokens)
                        {
                                perror("./shell: tokens error");
                                return(NULL);
                        }
                }
                token = strtok(NULL, DELIMIT);
        }

        tokens[len] = NULL;
        return (tokens);
}