#ifndef SHELL_H
#define SHELL_H


#include <stdlib.h>
#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
/*argument length & shell name*/
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define SHELL_NAME "./hsh"
#define PROMPT "CisFun$ "

/*shell modes*/
void run_shell();
void non_interactive_shell(const char *filename);

/*shell helpers*/
void sig_handler(int sig_num);
void process_and_execute(char *command);
void parse_input(char *input, char **arguments);
#endif
