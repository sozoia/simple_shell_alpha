#include "main.h"

/**
 * copy_environment - Creates a copy of the current environment.
 * Return: The copied environment.
 */
char **copy_environment(void)
{
	char **env = NULL;
	int i, j, k;

	for (i = 0; environ[i]; i++)
		;

	env = malloc((i + 1) * sizeof(char *));
	if (!env)
		return NULL;

	for (j = 0; j < i; j++)
	{
		env[j] = strdup(environ[j]);
		if (!env[j])
		{
			for (k = 0; k < j; k++)
				free(env[k]);
			free(env);
			return NULL;
		}
	}

	env[i] = NULL;

	return env;
}

/**
 * _setenv - Sets or updates an environment variable.
 * @args: An array containing the variable name, new value, and a flag (0 or 1).
 * Return: 0 if success, 1 if error.
 */
int _setenv(char **args)
{
	char **env = copy_environment();
	size_t len = 0, new_len = 0;
	int i, name_len;

	if (!args || !args[1] || !args[2])
	{
		free(env);
		return 1;
	}

	name_len = strlen(args[1]);

	for (i = 0; env[i]; i++)
		len += strlen(env[i]) + 1;

	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], args[1], name_len) == 0 && env[i][name_len] == '=')
		{
			if (strcmp(args[3], "0") == 0)  /*if the third para is 0 don't do anythinf*/
			{
				free(env[i]);
				break;
			}
			else
			{
				new_len = len + name_len + strlen(args[2]) + 2;
				env[i] = realloc(env[i], new_len);
				if (!env[i])
				{
					free(env);
					return 1;
				}
				snprintf(env[i], new_len, "%s=%s", args[1], args[2]);
			}
			environ = env;
			return 0;
		}
	}

	new_len = len + name_len + strlen(args[2]) + 2;
	env = realloc(env, (i + 2) * sizeof(char *));
	if (!env)
	{
		free(env);
		return 1;
	}

	env[i] = malloc(new_len);
	if (!env[i])
	{
		free(env);
		return 1;
	}

	snprintf(env[i], new_len, "%s=%s", args[1], args[2]);
	env[i + 1] = NULL;

	environ = env;
	return 0;
}
/**
 * _unsetenv - Unsets an environment variable.
 * @name: The name of the environment variable to unset.
 * Return: 0 if success, 1 if error.
 */
int _unsetenv(const char *name)
{
    char **env = NULL;
    size_t len = 0;
    int i, j, name_len;

    if (!name)
        return 1;

    name_len = strlen(name);

    /* Copy the current environment variables */
    for (i = 0; environ[i]; i++)
        len += strlen(environ[i]) + 1;

    env = (char **)malloc((i + 1) * sizeof(char *));
    if (!env)
        return 1;

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
        {
            /* Skip the environment variable to unset */
            continue;
        }

        env[i] = strdup(environ[i]);
        if (!env[i])
        {
            /* Handle memory allocation failure */
            perror("_unsetenv: strdup");
            for (j = 0; j < i; j++)
                free(env[j]);
            free(env);
            return 1;
        }
    }

    env[i] = NULL;

    /* Set the modified environment variables */
    environ = env;

    return (0);
}
