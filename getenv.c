#include "main.h"

/**
 * _getenv - Retrieves the value of an environment variable by name.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found or on error.
 */
char *_getenv(const char *name)
{
    extern char **environ;
        char **env;
    for (env = environ; *env != NULL; env++)
    {
        char *equal_sign = strchr(*env, '=');

        if (equal_sign != NULL)
        {
            size_t var_name_length = equal_sign - *env;

            if (strncmp(*env, name, var_name_length) == 0 && name[var_name_length] == '\0')
            {
            
                size_t value_length = strlen(equal_sign + 1);
                char *value = (char *)malloc(value_length + 1);

                if (value != NULL)
                {
                  
                    strcpy(value, equal_sign + 1);
                    return value;
                }
                else
                {
                
                    perror("_getenv: malloc");
                    return NULL;
                }
            }
        }
    }

    return NULL;
}