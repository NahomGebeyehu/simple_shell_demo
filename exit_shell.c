#include "shell.h"
#include <stdlib.h>

/**
 * exit_shell - This function exits the shell
 * Return: This returns void
 */
void exit_shell(void)
{
    free(buffer);
    exit(EXIT_SUCCESS);
}

