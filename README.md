# Projet `C - Simple Shell`

This `README.md` contains the files needed for the Simple Shell. 
This is our third group project, and we will be working in pairs. 
Our team consists of **Fassih Belmokthar** "Noziop" and **Xavier Piedallu** "Xa-C24".


First, clone this repository to your local machine:

			git clone https://github.com/Noziop/holbertonschool-simple_shell.git

For this project, we will adopt the following method to facilitate collaboration:

Working on a local branch:
	
Each team member will work on their own branch locally. Create a branch from `main` with a descriptive name:

				- git branch Xa
				- git branch fassih

Common branch: main

The Simple Shell is a simple UNIX command interpreter written entirely in C. 
The program runs based on bash commands obtained from the command line interface (CLI) given by the user. 
Any text seperated by a any number of spaces, tabs or a combination of both is considered to be an argument. 
The respective command typed by the user is then parsed and executed as if in a regular UNIX shell.


To begin with, we decided to devide the work:


Fassih will: .Creat GitHub repository
		     .Create flowchart
		     .Create all files
				

Xavier	will: .Create README.md
	      .Create man_page
	      .Create blog on Medium	


Note : This `README.md` will be updated several times as the project progresses.

##  Summary

1  -  [Summary](#summary)  
2  -  [Requierements](#requierements)  
3  -  [Files](#Files)  
4  -  [Operating System:](#operating-system)  
5  -  [Compilation flags](#compilation-flags) 
6  -  [Code snippets](#Code snippets)  
7  -  [Exemples](#Exemples)  
8  -  [Glossary (in alphabetical order)](#glossary-in-alphabetical-order)  
9  -  [`simple_shell`](#_simple_shell)  
10 -  [How to use `simple_shell` and its specifier?](#how-to-use-_printf-and-its-specifier)  
11 -  [Manpage `simple_shell`](#manpage-man_1_simple_shell)  
12 -  [Blog on Medium](#blog-on-Medium)  
13 -  [How we tested our project.](#how-we-tested-our-project)  
14 -  [Some tests to try:](#some-tests-to-try)  
15 -  [Flowchart](#flowchart)  
16 -  [Conclusion](#conclusion)  
17 -  [Author](#author)  


## Requierements

## Files

| Files names | Descriptions |
|-----------| -------------------------------------------------------------------------------------------------------------|
|StarHeader.h | Contains the declarations of functions defined in other .c files. |
|01-MainFalcon.c | Is the header file which contains the standared header file and prototype of o function used in the program.|		
|02-split_string.c |  This code contains two utility functions for a simple C shell: split_string - _strdup	|	
|03-execute_command.c | Code for execute the command. |
|04-environnement_function.c |  Is used to obtain the value of an environment variable from an array of character strings.|
|05-O_built_one_kenobi.c | This C file implements several functions that manage built-in commands for a simple shell program.|
|07-What happens? | Blog post explaining what happens when you type 'ls -l *.c' in the shell.|
|helpers.c | Custom ATOI function |
|.gitignore| Which files and folders should be ignored by Git when tracking changes in a repository.|
|LICENSE | The licence grants to anyone who obtains a copy of the software the right to use the software without restriction.|
|README.md | Description about the project repository.|
|man_1_simple_shell | Is the man page for the shell we are going to write.|
|AUTHORS | File at the root of your repository, listing all individuals having contributed content to the repository.|
|simpleshell.flowchart.png | Flow diagram illustrating the operation or structure of a simple shell project.|

Before begining, ensure that you have the following requirements:

### Operating System:

  - Ubuntu 22.04 LTS (of compatible version)

- **Softwares**:

  - **Visual Studio Code:** Ensure you have the latest version installed (You can find it [here](https://code.visualstudio.com/))

  - **GCC (GNU Compiler Collection):** Requiered for compiling the project. You can install it on your **Visual Code** using this: 
  
```sh
sudo apt-get install gcc
```
  
  - **Betty Style:** A style guide for the C programming language used by the Holberton School and ensuring a well structured and readable code. Ensure you have the Betty linter installed:

```sh
git clone https://github.com/holbertonschool/Betty.git

cd Betty

./install.sh
```

  - **Valgrind:** A tool for memiiry debugging, memory leak detection, and profiling. Install it using:

```sh
sudo apt-get install valgrind
``` 

- **Version Control**

**Git:** Ensure you have Git installed for version control:

```sh
sudo apt-get install git
```


### Compilation flags

This project must be compiled with the following flags:

```sh
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 .c -o hsh
```

- **`-Wall`:** Enables all standard compiler warnings.

- **`-Wextra`:** Enables additional warnings not covered by **`-Wall`**.

- **`-Werror`:** Treats all warnings as errors, stopping compilation.

- **`-pedantic`:** Enforces strict ISO C compliance.

- **`-std=gnu89`:** Uses the GNU89 standard for C, allowing GNU extensions to the ANSI C standard

- **`Wno-format`:** Disables format warnings.

## Code snippets
```
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
```


## Exemples

You can use aowr in interactiv mode:

```bash
root@hey-coucou-xav:~/holbertonschool-simple_shell# ./test/simple_shell
root@Xa-C24&Noziop_shell:/root/holbertonschool-simple_shell$ ls -l
total 880
-rw-r--r-- 1 root root   2231 Aug 21 16:58  01-MainFalcon.c
-rw-r--r-- 1 root root   1740 Aug 21 16:58  02-SplitSabers.c
-rw-r--r-- 1 root root   1984 Aug 21 17:05  03-execute_command_66.c
-rw-r--r-- 1 root root   2893 Aug 21 16:58  04-This_is_the_path.c
-rw-r--r-- 1 root root   4990 Aug 22 08:38  05-O_built_one_kenobi.c
-rw-r--r-- 1 root root   3708 Aug 16 12:04 '07- What_happens?'
-rw-r--r-- 1 root root   3157 Aug 19 11:08 '07-What_happens?'
-rw-r--r-- 1 root root    166 Aug 19 11:08  AUTHORS
-rw-r--r-- 1 root root   1063 Aug 12 11:54  LICENSE
-rw-r--r-- 1 root root  12254 Aug 22 08:48  README.md
-rw-r--r-- 1 root root   1234 Aug 22 08:38  StarHeader.h
-rw-r--r-- 1 root root    803 Aug 20 13:28  helpers.c
-rwxr-xr-x 1 root root  22312 Aug 22 08:49  hs
-rwxr-xr-x 1 root root  22272 Aug 22 08:37  hsh
-rw-r--r-- 1 root root   2900 Aug 21 16:58  man_1_simple_shell
-rw-r--r-- 1 root root 770248 Aug 19 11:08  simpleshell.flowchart.png
drwxr-xr-x 1 root root   4096 Aug 22 08:49  test
root@Xa-C24&Noziop_shell:/root/holbertonschool-simple_shell$ 
```

Or you can use it non interactiv mode:
```bash
root@hey-coucou-xav:~/holbertonschool-simple_shell# echo "ls -l" | ./test/simple_shell 
total 884
-rw-r--r-- 1 root root   2231 Aug 21 16:58  01-MainFalcon.c
-rw-r--r-- 1 root root   1740 Aug 21 16:58  02-SplitSabers.c
-rw-r--r-- 1 root root   1984 Aug 21 17:05  03-execute_command_66.c
-rw-r--r-- 1 root root   2893 Aug 21 16:58  04-This_is_the_path.c
-rw-r--r-- 1 root root   4990 Aug 22 08:38  05-O_built_one_kenobi.c
-rw-r--r-- 1 root root   3708 Aug 16 12:04 '07- What_happens?'
-rw-r--r-- 1 root root   3157 Aug 19 11:08 '07-What_happens?'
-rw-r--r-- 1 root root    166 Aug 19 11:08  AUTHORS
-rw-r--r-- 1 root root   1063 Aug 12 11:54  LICENSE
-rw-r--r-- 1 root root  13510 Aug 22 08:51  README.md
-rw-r--r-- 1 root root   1234 Aug 22 08:38  StarHeader.h
-rw-r--r-- 1 root root    803 Aug 20 13:28  helpers.c
-rwxr-xr-x 1 root root  22312 Aug 22 08:49  hs
-rwxr-xr-x 1 root root  22272 Aug 22 08:37  hsh
-rw-r--r-- 1 root root   2900 Aug 21 16:58  man_1_simple_shell
-rw-r--r-- 1 root root 770248 Aug 19 11:08  simpleshell.flowchart.png
drwxr-xr-x 1 root root   4096 Aug 22 08:49  test
root@hey-coucou-xav:~/holbertonschool-simple_shell#
```


## Glossary (in alphabetical order)

**B**

  - **bash**: A Unix shell and command language
	
  - **Betty Style:** A style guide for the C programming language ensuring code readibility and consistency 

**C**

  - **character:** A single alphanumeric symbol
 
  - **Compilation flags:** Options passed to the compiler to control the compilation process. 

**F**  

  - **Formatted output:** Output that is formatted according to specified rules, such as alignement, width, and (here) type of data.
  
  - **Format specifier:** A placeholder in the format string that indicates how a value should be formatted and displayed.
  
  - **`FormatSpec`:** A struct used to map specifiers to their corresponding functions.
  
  - **Function:** A block of code that performs a specific task.   

**G**  

  - **GCC (GNU Compiler Collection):** A compiler system supporting various programming languages, including C. 
  
  - **Git:** A version control software used for tracking changes in source code during software development. 

**I**  

  - **Integer:** A whol number, positive of negative, without decimals 

**M**

  - **Manual page (manpage):** A document that provides informations about a command for UNIX and UNIX-LIKE operating systems, accessible via the `man` command. 
  
  - **Memory leak:** A situation where a program does not release memory that is no longer needed, leading to a gradual loss of available memory. 

**N**

  - **`NULL`:** A macro representing a null pointer, indicating the end of a list or no value. 

**P**  

  - **Plain text:** Ordinary characters in the format string that are printed as-is 
  - **`Printing_Function`:** A member of the Formatspec struc, representing the function to handle the corresponding specifier.

**R**  

  - **README.md:** A markdown file containing information about a project, includings instructions, requirements, and other essential details.

**S**

  - **Specifier:** A symbol in the format string that specifies the type of data to be formatted.
  
  - **`Specifier_Entry`:** A member of the `FormatSpec` struct, representing the format specifier.
  
  - **String:** A sequence of characters. 

**U**

  - **Ubuntu:** A popular Linux distribution based on Debian, known for its user-friendliness. 

**V**

  - **Valgrind:** A programming tool for memory debugging, memory leak detection, and profiling.
  
  - **Variadic function:** A function that accepts a variable numbers or arguments. 
  
  - **Visual Studio Code:** A source-code editor made by Microsoft, providing support for debugging, syntax highlighting, and version control. 

## `simple_shell`

**Definition:**

`simple_shell` A simple shell is a computer program that acts as an interface between the user and the operating system. It allows the user to enter commands via a command line interface, which are then interpreted and executed by the system.

**Why use it?**

`simple_shell`, such as Bash, has several significant advantages:

1. **Efficiency:** The shell lets you execute commands quickly via a command-line interface, which is often more efficient than graphical interfaces, especially for repetitive or complex tasks 1 2.
2. **Automation:** The shell can be used to automate tasks using scripts. These scripts can combine several commands into a single operation, reducing the time and effort needed to perform repetitive tasks 5.
3. **Total control:** By using the shell, users can interact directly with the operating system, offering more granular control over system operations, such as file and process management 3 4. 
4. **Portability:** Bash is available on many Linux distributions and other Unix systems, making it a versatile and accessible tool for developers and system administrators 3 5. 
5. **Customisation:** The shell can be customised, allowing users to change colours, keyboard shortcuts and add custom commands, enhancing the user experience 3. 
6. **Learning Unix systems:** Mastery of the shell is essential for understanding and working effectively with Unix systems, as many administrative tasks and scripts are written in shell 1 2.

### How to use `simple_shell`

`simple_shell` open a terminal or command prompt window on your system.


## Manpage `simple_shell`

A "Manpage" is short for "Manual Page". This is a command scripted to display the manual page of `simple_shell`, explaining the command and how to use it, while being in bash. Xavier wrote one for us and here is how to install it on you local visual code.

**Step 1: Creating the Directory Structure**

First, it's requiered to create the necessary directories if they don't already exist.

```sh
sudo mkdir -p /usr/local/man/man1
```

**Step 2: Install the manpage**

After creating the directory structure, installing the manpage with `sudo`to ensure to have the necessary permissions:

```sh
sudo cp man_1_simple_shell /usr/local/man/man1/man_1_simple_shell.1
```

Little breakdown about what this all about:

  - **`-o root`:** Specifies the owner of the file (root in this case).

  - **`-m 0644`:** Sets the permissions of the file (readable and writable by the owner, readable by others).

  - **`man_1_simple_shell`:** The source file for the manpage.

  - **`/usr/local/man/man1/man_1_simple_shell.1`:** The destination path for the installed manpage.


**Step 3: Update the manpage database**

You already have a manpage database holding the man of other commands. You need to update it so that `man` can find the new manpage:

```sh
sudo mandb
```

**Step 4: Try it**

```sh
man man_1_simple_shell
```

## Blog on Medium [#What happens?]

Link to the blog created by Xa-C24&Nozoip on the Medium platform explaining what happens when you type "ls -l *c" in the shell terminal.

Click and you'll see, it's magic >>>>> [Read this article on Medium](https://medium.com/@9335/what-happens-when-you-type-ls-l-c-in-the-shell-c677b2804141)



### How we tested our project

In this section, we are going to focus on the construction of the script itself and especially how we tested it, more than explaining how it works (it has already been explained in previous section).

So, to provide a safe environnement to test our functions without messing everything up, we created a `test` directory, in our local visual code. This directory holds a copy of each file as they were at the time of the developpement of the script, and we kept it updated regularly.

When we needed to test something, we worked in that directory, on our `simple_shell`file in this directory. We adjusted or implemented the changes what we wanted to try, then compiled everything together like this:

```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Flowchart
	
![simple_shell](https://www.fassih.fr/simpleshell.flowchart.png)

## Conclusion

The simple shell, like Bash, is a powerful and versatile tool that offers numerous advantages for interacting with the operating system.

## Author

**Fassih Belmokthar** &
**Xavier Piedallu**
