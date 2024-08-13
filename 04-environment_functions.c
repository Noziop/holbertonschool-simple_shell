#include "00-main.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: The name of the environment variable
 * @environ: The current environment variables
 *
 * Return: The value of the environment variable or NULL if not found
 */
char	*_getenv(const char *name, char **environ)
{
	size_t	len = strlen(name);
	int	i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			return (environ[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}
