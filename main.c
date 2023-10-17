#include "shell.h"
/*
 * Auth: Jaxn
 * File: main.c
 * Project: simple_shell
 * chosen prompt in interactive mode: CisFun$
 */

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	if (argc == 1)
		run_shell();
	else if (argc == 2)
		run_non_interactive_shell(argv[1]);
	else
		fprintf(stderr, "Usage: %s [script]\n", argv[0]);

	return (1);
}
