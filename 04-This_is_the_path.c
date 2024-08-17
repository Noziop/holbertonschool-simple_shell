#include "StarHeader.h"


/**
 * get_command_path - Determines the path of the command
 * @command: The command to find
 * @environ: The environment variables
 *
 * Return: The full path of the executable, or NULL if not found
 */
char *get_command_path(char *command, char **environ)
{
	/* Structure to hold file status information */
	struct stat st;
	char *command_path; /* Path to the command executable */

	/* Check if the command is a full path and exists */
	if (command[0] == '/' && stat(command, &st) == 0)
	{
		return (command);
	}
	/* Search for the command in the PATH */
	command_path = find_in_path(command, environ);
	return (command_path);
}

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

/**
 * sigint_handler - avoid ctrl+c to quit program
 * @sig: keybordentry.
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	display_prompt();
	fflush(stdout);
}

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
