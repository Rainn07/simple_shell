/*
 * Auth: Jaxn
 * file: shell.c
 * Desc: file containing implementation
 *	of shell related functions
 */

#include <stdlib.h>
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * sig_handler - checks for signal and
 *	prints prompt
 * @sig_num: signal indicator
 */

void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
}

/**
 * parse_input - parses cmd line arguments and tokenize them
 * @input: input from user
 * @arguments: arry of ptr to arguments
 */

void parse_input(char *input, char **arguments)
{
	char *token = strtok(input, " \t\n");
	int arg_index = 0;

	while (token != NULL)
	{
		arguments[arg_index++] = token;
		token = strtok(NULL, " \t\n");
	}
	arguments[arg_index] = NULL;
}

/**
 * process_and_execute - processes command and execute
 * @command: the command from the cmd line
 */

void process_and_execute(char *command)
{
	char *arguments[MAX_ARGUMENTS];
	pid_t child_pid;

	parse_input(command, arguments);

	if (arguments[0] == NULL)
		return;

	/* Fork a child process */
	child_pid = fork();

	if (child_pid == -1)
	{
		perror("Fork failed");
		return;
	}

	if (child_pid == 0)
	{
		/* Child process/Execute the command */
		if (execvp(arguments[0], arguments) == -1)
		{
			perror("Execution error");
			exit(1);
		}
		else
		{
			/* Parent process */
			int status;

			waitpid(child_pid, &status, 0);
		}
	}
}
/**
 * run_shell - interactive shell logic
 */

void run_shell(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			perror(PROMPT);
			exit(1);
		}

		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);

		process_and_execute(command);

		if (!isatty(STDIN_FILENO))
			break;
	}
}

/**
 * non_interactive_shell - !isatty
 * @filename: script to be ran
 */
void non_interactive_shell(const char *filename)
{
	FILE *script;
	char line[MAX_COMMAND_LENGTH];

	script = fopen(filename, "r");
	if (script == NULL)
	{
		perror("Script open failed");
		exit(1);
	}

	while (fgets(line, sizeof(line), script) != NULL)
	{
		/* Process and execute the command */
		process_and_execute(line);
	}
}
