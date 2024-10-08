#include "StarHeader.h"

/**
 * handle_builtin_commands - Handles built-in shell commands
 * @args: Array of command arguments
 * @input: The input string
 * @environ: The environment variables
 * @program_name: name of shell exec to print correct error output
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int handle_builtin_commands(char **args, char *input,
					char **environ, char *program_name)
{
	/* Check if there are any arguments */
	if (args == NULL || args[0] == NULL)
		return (1);

	/* Check for "exit" command */
	if (strcmp(args[0], "exit") == 0)
	{
		shell_exit(args, input, program_name);
	}

	/* Check for "env" command */
	if (strcmp(args[0], "env") == 0)
	{
		print_env(environ);
		return (0);
	}

	/* Check for "cd" command */
	if (strcmp(args[0], "cd") == 0)
	{
		return (builtin_cd(args, environ));
	}

	/* Check for "ls" command */
	if (strcmp(args[0], "ls") == 0)
	{
		return (execute_ls_with_color(args, environ));
	}

	/* Check for "help" command */
	if (strcmp(args[0], "help") == 0)
	{
		return (help_builtin(args));
	}

	/* If not a builtin command, continue shell execution */
	return (1);
}

/**
 * builtin_cd - Change the current directory
 * @args: Arguments passed to cd command
 * @env: Environment variables
 * Return: 0 on success, -1 on failure
 */
int builtin_cd(char **args, char **env)
{
	char cwd[PATH_MAX], *dir = NULL, *home_dir = NULL;
	static char old_pwd[PATH_MAX] = {0};
	int i;

	/* Get current working directory */
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (-1);

	/* Find HOME directory in environment variables */
	for (i = 0; env[i]; i++)
		if (strncmp(env[i], "HOME=", 5) == 0)
		{
			home_dir = env[i] + 5;
			break;
		}

	/* Determine target directory */
	if (!args[1] || strcmp(args[1], "~") == 0 || strcmp(args[1], "$HOME") == 0)
		dir = home_dir;
	else if (strcmp(args[1], "-") == 0)
	{
		if (old_pwd[0] != '\0')
		{
			dir = old_pwd;
			printf("%s\n", dir);
		}
		else
			return (0);
	}
	else
		dir = args[1];

	/* Change directory */
	if (chdir(dir) == 0)
	{
		strcpy(old_pwd, cwd);
		return (0);
	}
	perror("cd");
	return (-1);
}

/**
 * shell_exit - exit shell terminal
 * @args: Array of command arguments
 * @input: The input string
 * @program_name: name of shell exec to print correct error output
 * Return: EXIT_SUCCESS if no argument is given by user
 *          exit_code provided by user within args[1]
 */
int shell_exit(char **args, char *input, char *program_name)
{
	int exit_code;

	/* Check if an exit code is provided */
	if (args[1] != NULL)
	{
		/* Validate the exit code */
		if (args[1][0] == '-' || !is_valid_number(args[1]))
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", program_name, args[1]);
			return (1);
		}
		exit_code = _atoi(args[1]);
	}
	else
	{
		exit_code = EXIT_SUCCESS;
	}

	/* Free allocated memory and exit */
	free(args);
	free(input);
	exit(exit_code);
}

/**
 * help_builtin - Provide information on internal orders.
 * @args: Array of command arguments.
 *
 * Return: return (0) function has been completed successfully.
 */
int help_builtin(char **args)
{
	char cd[] = "\033[1;32mcd\033[0m", exit[] = "\033[1;32mhelp\033[0m";

	/* If no specific command is specified, show general help */
	if (args[1] == NULL)
	{
		printf("here are the builtins commands we've implemented so far :\n\n");
		printf("%s : allows you to navigate through the file system\n", cd);
		printf("use this command to get more help about cd :  help cd\n\n");
		printf("\033[1;32mexit\033[0m : exits the shell programm\n");
		printf("use this command to get more help about exit :  help exit\n\n");
		printf("\033[1;32menv\033[0m : displays environment variables\n");
		printf("use this command to get more help about env :  help env\n\n");
		printf("%s :  displays help about help builtin command\n", exit);
		printf("use this command to get more help about help :  help help\n\n");
	}
	else
	{
		/* Show help for specific command */
		help_builtin_cmd(args);
	}
	return (0);
}

/**
 * help_builtin_cmd - displays help for builtins cmd
 * @args: command to display help for
 */
void help_builtin_cmd(char **args)
{
	char green[] = "\033[1;32m", end[] = "\033[0m";

	/* Display help for 'cd' command */
	if (strcmp(args[1], "cd") == 0)
	{
		printf("%scd%s allows you to navigate ", green, end);
		printf("through the file system.\n");
		printf("Usage: cd [directory] example : cd /path/to/");
		printf("desired/destination. \n\nYou can also use :\n");
		printf("%scd ..%s : moves up one level ", green, end);
		printf("in the directory tree.\n");
		printf("%scd -%s : returns to the last visited directory\n", green, end);
		printf("%scd /%s : goes to the file system root\n", green, end);
		printf("%scd  ~%s or %scd $HOME%s", green, end, green, end);
		printf(" or %scd%s : goes to home directory\n", green, end);
	}
	/* Display help for 'exit' command */
	else if (strcmp(args[1], "exit") == 0)
	{
		printf("%sexit%s: quits the shell programm.\n", green, end);
		printf("Usage: %sexit [return code]%s\n", green, end);
		printf("you can then, verify exit code with the command : ");
		printf("'%secho $?%s'\n", green, end);
	}
	/* Display help for 'env' command */
	else if (strcmp(args[1], "env") == 0)
	{
		printf("%senv%s: Displays environment variables.", green, end);
		printf("\nUsage (simply type): %senv%s\n", green, end);
	}
	/* Display help for 'help' command */
	else if (strcmp(args[1], "help") == 0)
	{
		printf("%shelp%s : Displays these informations.\n", green, end);
		printf("To display help for the help builtin command, ");
		printf("type: '%shelp help%s'\n", green, end);
		printf("(you're already here nonetheless,");
		printf(" as you've typed \"%shelp help%s\")\n", green, end);
	}
}
