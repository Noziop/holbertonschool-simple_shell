#include "00-StarHeader.h"


/**
 * _getenv - Gets the value of an environment variable
 * @name: The name of the environment variable
 * @environ: The current environment variables
 *
 * Return: The value of the environment variable or NULL if not found
 */
char *_getenv(const char *name, char **environ)
{
	size_t len = strlen(name); /* Length of the environment variable name */
	int i = 0; /* Index for iterating through the environment variables */

	/* Iterate through the environment variables */
	while (environ[i])
	{
		/* Check if the current variable matches the name */
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			/* Return the value of the environment variable */
			return (environ[i] + len + 1);
		}
		i++;
	}
	/* Return NULL if the environment variable is not found */
	return (NULL);
}

/**
 * print_env - Prints the current environment variables
 * @environ: The environment variables
 */
void print_env(char **environ)
{
	int i = 0; /* Index for iterating through the environment variables */

	/* Iterate through the environment variables */
	while (environ[i])
	{
		/* Print each environment variable */
		printf("%s\n", environ[i]);
		i++;
	}
}
