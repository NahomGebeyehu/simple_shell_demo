#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Define MAX_INPUT to the desired value */
#define MAX_INPUT 1024

/* Function prototypes */
char **parse_input(char *input);
char *search_path(char *command, char *path);
int run_simple_shell(void);
size_t _strlen(char *s);
#endif /* SHELL_H */

