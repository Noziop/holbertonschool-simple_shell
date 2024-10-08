#include "StarHeader.h"

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
	/* (void)argv; Unused parameter */

	/* Main loop of the shell */
	while (status)
	{
		/* Display the prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			display_prompt();

		/* Read a line of input from the user */
		if (getline(&input, &bufsize, stdin) == -1)
		{
			free(input); /* Free the input buffer */
			exit(EXIT_SUCCESS); /* Exit the shell on EOF */
		}

		/* avoid CTRL+C */
		signal(SIGINT, sigint_handler);
		/* Remove the newline character from the input */
		remove_newline(input);
		/* Split the input into an array of arguments */
		args = split_string(input);
		/* Handle built-in commands */
		if (handle_builtin_commands(args, input, envp, argv[0]) == 0)
		{
			free(args); /* Free the arguments array */
			continue; /* Continue the loop for the next command */
		}
		/* Execute external commands */
		status = execute_command(args, envp, argv[0]);
		free(args); /* Free the arguments array */
	}
	free(input); /* Free the input buffer */
	return (0); /* Return success */
}

/**
 * display_prompt - function to display prompt
 */
void display_prompt(void)
{
	char cwd[PATH_MAX]; /* Buffer to store the current working directory */
	char *username; /* Pointer to store the username */

	/* Get the username from the environment */
	username = getenv("USER");
	if (username == NULL)
		username = "unknown"; /* Fallback if USER is not set */

	/* Get the current working directory */
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return;
	}

	/* Display the prompt in green with username and current directory */
	if (isatty(STDIN_FILENO))
	printf("\033[1;32m%s@\033[0m", username);
	printf("\033[1;31mXa-C24&Noziop_shell\033[0m:");
	printf("\033[1;34m%s\033[0m$ ", cwd);
}

