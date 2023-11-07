#include "main.h"

char **parse(char *line)
{
        int len = 0;
        int cap = ARGBUF;
        char **tokens = malloc(cap * sizeof(char *));
        char *token;

        if (!tokens)
        {
                perror("./shell: tokens error");
                exit(1);
        }

        token = strtok(line, DELIMIT);

        while (token != NULL)
        {
                tokens[len++] = token;
                if (len >= cap)
                {
                        cap += ARGBUF;
                        tokens = realloc(tokens, cap);
                        if (!tokens)
                        {
                                perror("./shell: tokens error");
                                exit(1);
                        }
                }
                token = strtok(NULL, DELIMIT);
        }

        tokens[len] = NULL;
        return (tokens);
}