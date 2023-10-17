#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/*argument length*/
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void run_shell();
void non_interactive_shell();
#endif
