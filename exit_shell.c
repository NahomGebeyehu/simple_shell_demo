#include "shell.h"
#include <stdlib.h>

/**
 * exit_shell - Exits the shell
 */
void exit_shell(void)
{
    free(buffer); // Assuming buffer is a global variable
    exit(EXIT_SUCCESS);
}

