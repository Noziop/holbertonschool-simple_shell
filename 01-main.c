#include "00-main.h"

/**
 * main - Entry point of the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * Return: Always 0 (Success)
 */
int	main(int argc, char **argv, char **envp)
{
	char	*input = NULL;
	size_t	bufsize = 0;
	char	**args;
	int	status = 1;

	(void)argc;
	(void)argv;

	while (status)
	{
		printf("#cisfun$ "); /* Display the prompt */
		if (getline(&input, &bufsize, stdin) == -1)
		{
			if (feof(stdin))
			{
				free(input);
				exit(EXIT_SUCCESS); /* Handle EOF (Ctrl+D) */
			}
			else
			{
				perror("getline");
				free(input);
				exit(EXIT_FAILURE);
			}
		}
		/* Remove newline character */
		input[strcspn(input, "\n")] = 0;
		/* Split the input into arguments */
		args = split_string(input);

		/* Execute the command */
		if (args != NULL)
		{
			status = execute_command(args, envp);
		}
		free(args);
	}
	free(input);
	return (0);
}
