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

	if (args[0] == NULL)
		return (1);

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		command_path = args[0];
	}
	else
	{
		command_path = get_command_path(args[0], environ);
	}

	if (command_path == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
		return (1);
	}

	execute_command_(args);

	if (command_path != args[0])
		free(command_path);

	return (1);
}


/**
 * execute_child_process - Executes the command in the child process
 * @command_path: The path of the command
 * @args: The arguments for the command
 * @environ: The environment variables
 */
void execute_child_process(char *command_path, char **args, char **environ)
{
	/* Execute the command using execve */
	if (execve(command_path, args, environ) == -1)
	{
		/* Handle execution error */
		perror("Execution failed");
		if (command_path != args[0])
			free(command_path);
		exit(EXIT_FAILURE);
	}
}

/**
* execute_ls_with_color - Executes 'ls' with '--color=auto' option
* @args: Array of command arguments
*
* Return: (0) after execution
*/
int execute_ls_with_color(char **args)
{
	/* Allocate space for new arguments */
	char *new_args[100];
	int i = 0;

	/* Copy existing arguments */
	while (args[i] != NULL)
	{
		new_args[i] = args[i];
		i++;
	}

	/* Add '--color=auto' option */
	new_args[i++] = "--color=auto";
	new_args[i] = NULL;

	/* Execute ls with color option */
	execute_command_(new_args);
	return (0); /* Command was handled */
}

/**
 * execute_command_ - Forks and executes a command
 * @args: Array of command arguments
 */
void execute_command_(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}
	if (pid == 0)
	{
		/* In child process, execute the command */
		if (execvp(args[0], args) == -1)
		{
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* In parent process, wait for the child to finish */
		int status;

		wait(&status);
	}
}
