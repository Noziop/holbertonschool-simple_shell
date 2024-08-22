#include "StarHeader.h"

/**
 * execute_command - Executes a command if it exists
 * @args: An array of arguments for the command
 * @environ: The environment variables
 * @program_name: name of program
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int execute_command(char **args, char **environ, char *program_name)
{
	char *command_path;

	/* Check if there's a command to execute */
	if (args[0] == NULL)
		return (1);

	/* Get the full path of the command */
	command_path = get_command_path(args[0], environ);

	/* If command not found, print error and return */
	if (command_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (1);
	}

	/* Execute the command in a child process */
	execute_child_process(command_path, args, environ);

	/* Free allocated memory if command_path is different from args[0] */
	if (command_path != args[0])
		free(command_path);

	/* Return 1 to continue shell execution */
	return (1);
}

/**
* execute_ls_with_color - Executes 'ls' with '--color=auto' option
* @args: Array of command arguments
* @environ: bla
*
* Return: (0) after execution
*/
int execute_ls_with_color(char **args, char **environ)
{
	char *new_args[100];
	int i = 0;
	char *command_path;

	/* Copy existing arguments */
	while (args[i] != NULL)
	{
		new_args[i] = args[i];
		i++;
	}

	/* Add '--color=auto' option */
	new_args[i++] = "--color=auto";
	new_args[i] = NULL;

	/* Get the command path for 'ls' */
	command_path = get_command_path("ls", environ);
	if (command_path == NULL)
	{
		fprintf(stderr, "ls: command not found\n");
		return (1);
	}

	/* Execute ls with color option */
	execute_child_process(command_path, new_args, environ);

	free(command_path);
	return (0); /* Command was handled */
}

/**
 * execute_child_process - Forks and executes a command
 * @command_path: Full path of the command to execute
 * @args: Array of command arguments
 * @environ: Environment variables
 */
void execute_child_process(char *command_path, char **args, char **environ)
{
	/* Create a new process */
	pid_t pid = fork();

	/* Check if fork failed */
	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}

	/* Child process */
	if (pid == 0)
	{
		/* Execute the command */
		if (execve(command_path, args, environ) == -1)
		{
			/* If execution fails, print error and exit */
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	/* Parent process */
	else
	{
		int status;

		/* Wait for child process to complete */
		waitpid(pid, &status, 0);
	}
}
