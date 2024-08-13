#include "00-main.h"

/**
 * find_in_path - Searches for an executable in the PATH directories
 * @command: The command to find
 * @environ: The environment variables
 *
 * Return: The full path of the executable, or NULL if not found
 */
char *find_in_path(char *command, char **environ)
{
	/* Retrieve the PATH environment variable */
	char *path_env = _getenv("PATH", environ);
	char *path_copy, *token, *full_path; /* Variables for path manipulation */
	 /* Structure to hold file status information */
	struct stat st;

	/* Return NULL if PATH is not found */
	if (!path_env)
		return (NULL);

	/* Duplicate the PATH string to avoid modifying the original */
	path_copy = _strdup(path_env);
	if (!path_copy)
		return (NULL);

	/* Tokenize the PATH string using ':' as a delimiter */
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		/* Allocate memory for the full path of the command */
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (!full_path)
		{
			free(path_copy); /* Free the duplicated PATH string */
			return (NULL);
		}
		/* Construct the full path by concatenating the token and command */
		sprintf(full_path, "%s/%s", token, command);

		/* Check if the constructed path is a valid executable */
		if (stat(full_path, &st) == 0)
		{
			free(path_copy); /* Free the duplicated PATH string */
			return (full_path); /* Return the valid path */
		}
		free(full_path); /* Free the constructed path if not valid */
		token = strtok(NULL, ":"); /* Get the next token */
	}
	free(path_copy); /* Free the duplicated PATH string */
	return (NULL); /* Return NULL if the command is not found in PATH */
}
