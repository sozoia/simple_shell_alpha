#include "main.h"

/**
 * token - tokenaiz string which is the input to the shell
 * @str: string that will be tokenaized
 * Return: array of string
*/
char **token(char *str)
{
	int i = 0;
	char *token;
	char **result = NULL;

	result = (char **)malloc(sizeof(char * ) * 2); 
	if(!result)
	{
        	perror("malloc");
        	return (NULL);
	}

    token = strtok(str, " \n\t\"\"");

	while (token) 
	{
        	result[i] = strdup(token); 
        	if (!result[i])
		{
           		perror("malloc");
           		return NULL;
        	}

        	i++;
		result = (char **)realloc(result, sizeof(char *) * (i + 2)); 
		if (!result) 
		{
        		perror("realloc");
            		return (NULL);
        	}
		token = strtok(NULL, " \n\t\"\"");
	}
	result[i] = NULL;

	return (result);
}
