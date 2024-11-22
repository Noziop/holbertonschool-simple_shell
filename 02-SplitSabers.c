#include "StarHeader.h"

/**
 * remove_newline - replace the '\n' by a null byte
 * @str: string to be tested
 */
void remove_newline(char *str)
{
	size_t i = 0;

	/* Iterate over the string until the newline */
	/* character or end of string is found */
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			str[i] = '\0'; /* Replace newline with null terminator */
			break;
		}
		i++;
	}
}

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
