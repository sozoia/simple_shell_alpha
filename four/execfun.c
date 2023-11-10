#include "main.h"

extern char **environ;
/**
 * execfun - split the input
 * @args: splited command
*/
int execfun(char **args)
{
        int status;
        pid_t pid;
	struct stat st;
	char **env = environ;

	if(!args)
	return(1);

        if (strcmp(args[0], "cd") == 0)
                return (cdfun(args));
        else if (strcmp(args[0], "exit") == 0)
                return (exitfun(args));

        pid = fork();
        if (pid > 0)
        {
                do
                {
                        waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
		return(status);
        }
        else if (pid == 0)
        {
		if(stat(getpath(args[0], env),&st) == 0)
		{
                	_execvp_(args[0], args);
                	fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
                	exit(126);
		}
		fprintf(stderr, "./%s: 1: %s: not found\n", "hsh", args[0]);
		exit(127);
        }
        else
        {
                fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
                exit(127);
        }
}