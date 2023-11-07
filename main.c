#include "main.h"

int main(void)
{
	char *line, **tokens;
	char *prompt = " #cisfun$ ";
	while(1)
	{
		write(1, prompt, strlen(prompt));
		line = readLine();
		tokens = parse(line);

		if (tokens[0])
			execfun(tokens);
		
		free(tokens);
		free(line);
	}
}