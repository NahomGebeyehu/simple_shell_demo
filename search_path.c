#include "shell.h"
#include <stdlib.h>

/* Custom function to replace strlen */

/**
 * search_path - Search for the command in the PATH directories
 * @command: The command to search for
 * @path: The PATH environment variable
 */
char *search_path(char *command, char *path)
{
    char *token, *full_path;
    /*char *delimiters = ":\n";*/
    char *path_copy = NULL;
    size_t path_len, token_len, full_path_len, i, j;

    /* Duplicate path using allowed functions */
    path_len = _strlen(path);

    path_copy = malloc(path_len + 1);
    if (path_copy == NULL)
    {
        perror("malloc");
        _exit(EXIT_FAILURE);
    }

    for (i = 0; i < path_len; i++)
        path_copy[i] = path[i];
    path_copy[i] = '\0';

    token = path_copy;

    while (*token != '\0')
    {
        /* Find the length of the current token */
        token_len = 0;
        while (token[token_len] != '\0' && token[token_len] != ':' && token[token_len] != '\n')
            token_len++;

        /* Allocate memory for full_path using allowed functions */
        full_path_len = token_len + _strlen(command) + 2;
        full_path = malloc(full_path_len);
        if (full_path == NULL)
        {
            perror("malloc");
            _exit(EXIT_FAILURE);
        }

        /* Construct full path using allowed functions */
        for (i = 0; i < token_len; i++)
            full_path[i] = token[i];

        full_path[i] = '/';
        i++;

        for (j = 0; j < _strlen(command); j++, i++)
            full_path[i] = command[j];

        full_path[i] = '\0';

        /* Check if the constructed path is executable using allowed functions */
        if (access(full_path, F_OK | X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);

        /* Move to the next token */
        token += token_len;
        if (*token == ':' || *token == '\n')
            token++;
    }

    free(path_copy);
    return NULL;
}

