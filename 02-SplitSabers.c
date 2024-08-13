#include "00-main.h"

/**
 * split_string - Splits a string into an array of words
 * @str: The string to split
 *
 * Return: A pointer to an array of strings (words)
 */
char **split_string(char *str)
{
	char **tokens; /* Array to store pointers to the tokens (words) */
	char *token; /* Pointer to the current token */
	size_t i = 0, bufsize = 64; /* Index and buffer size for tokens array */

	/* Allocate initial memory for tokens array */
	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
	{
		/* Print error message and exit if memory allocation fails */
		fprintf(stderr, "split_string: allocation error\n");
		exit(EXIT_FAILURE);
	}

	/* Use strtok to split the string into tokens based on spaces */
	token = strtok(str, " ");
	while (token != NULL)
	{
		tokens[i] = token; /* Store the token in the tokens array */
		i++;

		/* Reallocate memory if the buffer size is exceeded */
		if (i >= bufsize)
		{
			bufsize += 64; /* Increase buffer size */
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				/* Print error message and exit if reallocation fails */
				fprintf(stderr, "split_string: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		/* Get the next token */
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL; /* Null-terminate the array of tokens */
	return (tokens); /* Return the array of tokens */
}

/**
 * _strdup - Duplicates a string
 * @str: The string to duplicate
 *
 * Return: A pointer to the duplicated string, or NULL if insufficient memory
 */
char *_strdup(const char *str)
{
	char *dup; /* Pointer to the duplicated string */
	size_t len; /* Length of the input string */

	/* Return NULL if the input string is NULL */
	if (str == NULL)
		return (NULL);

	len = strlen(str); /* Get the length of the input string */
	/* Allocate memory for the duplicated string */
	dup = malloc((len + 1) * sizeof(char));
	if (dup == NULL)
	{
		/* Print error message and return NULL if allocation fails */
		perror("Error");
		return (NULL);
	}
	strcpy(dup, str); /* Copy the input string to the duplicated string */
	return (dup); /* Return the duplicated string */
}
