#include "00-main.h"

/**
 * split_string - Splits a string into an array of words
 * @str: The string to split
 *
 * Return: A pointer to an array of strings (words)
 */
char	**split_string(char *str)
{
	char	**tokens;
	char	*token;
	size_t	i = 0;
	size_t	bufsize = 64;

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "split_string: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(str, " ");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "split_string: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return (tokens);
}


/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: A pointer to the duplicated string, or NULL if insufficient memory
 */
char	*_strdup(const char *str)
{
	char	*dup;
	size_t	len;

	if (str == NULL)
		return (NULL);

	len = strlen(str);
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
	{
		perror("Error");
		return (NULL);
	}
	strcpy(dup, str);
	return (dup);
}
