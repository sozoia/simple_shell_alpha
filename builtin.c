#include "main.h"

/**
 * cdfun - this is impelemntaion of the builtin "cd" command.
 * @command: an array of string contain the command cd with the new WD.
 * Return: 0 if success  else -1.
*/
int cdfun(char **command)
{
	char *pwd = NULL, *old = NULL;

	if(!command[1])		/*if no path don't do anything*/
		return(1);	/*no error message either !!*/

	if(strcmp(command[1], "-") == 0)	/*last WD from env var*/
	{
		old = _getenv("OLDPWD");
		pwd = _getenv("PWD");

		if(!old || !pwd)
		return(1);

		if (chdir(old) == -1)
		{
			free(pwd);
			free(old);
			printf("got err\n");
			fprintf(stderr, "./hsh: 1: %s: can't cd to %s\n",command[0], command[1]);
			return(2);
		}
		setenv("OLDPWD", pwd, 1);
		setenv("PWD", old, 1);
		printf("info updated\n");
		free(old);
		free(pwd);
		return(0);
	}
	else if (chdir(command[1]) == -1)
	{
		fprintf(stderr, "./hsh: 1: %s: can't cd to %s\n",command[0], command[1]);
		return(2);
	}
		pwd = _getenv("PWD");
		printf("pwd: %s\n",pwd);
		if(!pwd)
		{
			free(pwd);
			return(1);
		}
		printf("pwd: %s\n",pwd);
		setenv("OLDPWD", pwd, 1);
		setenv("PWD", command[1], 1);
		free(pwd);
		return(0);
}
/**
 * isNumber - Check if a string is a valid number.
 * @str: The input string to check.
 *
 * Return: 1 if the string is a number, 0 otherwise.
 */
int isNumber(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);  /* Base 10 for decimal integers */

    /* Check if strtol successfully parsed the entire string */
    if (*endptr != '\0') {
        return 0;
    }

    return 1;
}

/**
 * exitfun - this is impelemntaion of the builtin "exit" command.
 * @command: an array of string contain the command exit.
 * Return: 0 if success  else -1.
*/
int exitfun(char **command)
{
	int status;

	if (!command[1])
	{
	free(command);
	exit(exit_stat);
	}

	status = atoi(command[1]);
	if (isNumber(command[1]) == 0)
	{
		fprintf(stderr,"./hsh: 1: exit: Illegal number: %s\n",command[1]);
		return(2);
	}

       if (command[1] && status >= 0)
       {
		free(command);
        	exit(status);
       }
	else
	fprintf(stderr,"./hsh: 1: exit: Illegal number: %s\n",command[1]);

	return(2);
}
/**
 * envfun - print the env vars
 * @args: command arr of str
 * Return: 0 if success else 1
*/
int envfun(char ** args)
{
	char **env = environ;
	unsigned long int i;

	(void)args;

	if(!env)
	return(1);

	for(i = 0; env[i]; i++)
	{
		printf("%s\n",env[i]);
	}
	return(0);
}
