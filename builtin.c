#include "main.h"

/**
 * cdfun - this is impelemntaion of the builtin "cd" command.
 * @command: an array of string contain the command cd with the new WD.
 * Return: 0 if success  else -1.
*/
int cdfun(char **command)
{
	char *pwd = NULL, *old = NULL;

	if(!command[1])				/*if no path don't do anything*/
		return(1);			/*no error message either !!*/
	if(_strcmp(command[1], "-") == 0)	/*last WD from env var*/
	{
		old = _getenv("OLDPWD");
		pwd = _getenv("PWD");
		if(!old || !pwd)
		{
			if(old)
				free(old);
			if(pwd)
				free(pwd);
			return(1);
		}
		if (chdir(old) == -1)
		{
			free(pwd);	/*cause _getenv allocate mem*/
			free(old);
			fprintf(stderr, "./hsh: 1: %s: can't cd to %s\n",command[0], command[1]);
			return(2);
		}
		printf("%s\n",old);		/*when cd - should print the new path (old)*/
		setenv("OLDPWD", pwd, 1);	/*we need to update the env var*/
		setenv("PWD", old, 1);		/*we need to update the env var*/
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
	if(!pwd)
		return(1);
	setenv("OLDPWD", pwd, 1);	/*we need to update the env var*/
	setenv("PWD", command[1], 1);	/*we need to update the env var*/
	free(pwd);
	return(0);
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
	free_command(command);		/*because i am exiting the prccess*/
	exit(exit_stat);	/*exit_stat is global var*/
	}

	status = atoi(command[1]);
	if (isNumber(command[1]) == 0)
	{
		fprintf(stderr,"./hsh: 1: exit: Illegal number: %s\n",command[1]);
		return(2);
	}

       if (command[1] && status >= 0)
       {
		free_command(command);
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
