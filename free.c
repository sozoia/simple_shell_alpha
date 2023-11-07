#include "main.h"

/**
 * free_command: free allocated memory for array of string.
 * @arr: array of string (ptr to ptr).
 * 
*/
void free_command(char **arr)
{
	int i;

	if (arr)
	{
		for (i = 0; arr[i]; i++)
		{
			free(arr[i]);
		}
        	free(arr);
	}
}
