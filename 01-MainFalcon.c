#include "00-StarHeader.h"


/**
 * handle_builtin_commands - Handles built-in shell commands
 * @args: Array of command arguments
 * @input: The input string
 * @environ: The environment variables
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int handle_builtin_commands(char **args, char *input, char **environ)
{
	/* Check if args is NULL or the first argument is NULL */
	if (args == NULL || args[0] == NULL)
		return (1);

	/* If the command is 'exit', free resources and exit the shell */
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(input);
		exit(EXIT_SUCCESS);
	}

	/* If the command is 'env', print the environment variables */
	if (strcmp(args[0], "env") == 0)
	{
		print_env(environ);
		return (0); /* Return 0 to indicate command was handled */
	}

	/* Return 1 to indicate that the command is not a built-in */
	return (1);
}

/**
 * main - Entry point of the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char **argv, char **envp)
{
	char *input = NULL; /* Buffer to store user input */
	size_t bufsize = 0; /* Size of the input buffer */
	char **args; /* Array to store command arguments */
	int status = 1; /* Status flag to control the shell loop */

	(void)argc; /* Unused parameter */
	(void)argv; /* Unused parameter */

	/* Main loop of the shell */
	while (status)
	{
		/* Display the prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			printf("#cisfun$ ");

		/* Read a line of input from the user */
		if (getline(&input, &bufsize, stdin) == -1)
		{
			free(input); /* Free the input buffer */
			exit(EXIT_SUCCESS); /* Exit the shell on EOF */
		}

		/* Remove the newline character from the input */
		input[strcspn(input, "\n")] = 0;
		/* Split the input into an array of arguments */
		args = split_string(input);

		/* Handle built-in commands */
		if (handle_builtin_commands(args, input, envp) == 0)
		{
			free(args); /* Free the arguments array */
			continue; /* Continue the loop for the next command */
		}

		/* Execute external commands */
		status = execute_command(args, envp);
		free(args); /* Free the arguments array */
	}
	free(input); /* Free the input buffer */
	return (0); /* Return success */
}
