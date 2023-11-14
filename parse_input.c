#include "shell.h"
#include <stdlib.h>

/* Custom function to replace strtok */
char *_strtok(char *str, const char *delim)
{
    static char *static_str = 0; /* Save string pointer */
    int index = 0;
    int strlength = 0; /* Length of the delimiter */
    char *beginning;

    /* Copy the delimiter length and the string pointer */
    if (delim == 0 || (str == 0 && static_str == 0))
        return 0;

    if (str == 0)
        str = static_str;

    /* Get length of the delimiter */
    while (delim[strlength])
        strlength++;

    /* Skip leading delimiters */
    while (*str)
    {
        for (index = 0; index < strlength; index++)
        {
            if (*str == delim[index])
                break;
        }
        if (index == strlength) /* Not a delimiter */
            break;
        str++;
    }

    /* String only contained delimiters! */
    if (*str == '\0')
    {
        static_str = 0;
        return 0;
    }

    /* Save beginning of string */
    beginning = str;

    /* Find the end of the string */
    while (*str)
    {
        for (index = 0; index < strlength; index++)
        {
            if (*str == delim[index])
            {
                *str = '\0';
                break;
            }
        }
        str++;
        if (*str == '\0')
        {
            static_str = 0;
            return beginning;
        }
        if (*str == delim[index])
        {
            *str = '\0';
            static_str = str + 1;
            return beginning;
        }
    }

    /* Done, return pointer */
    static_str = 0;
    return beginning;
}

/**
 * parse_input - Tokenizes input into an array of strings
 * @input: User input
 *
 * Return: Array of strings
 */
char **parse_input(char *input)
{
    char **tokens = NULL;
    char *token;
    int i = 0;

    tokens = malloc(MAX_INPUT * 1); /* Replaced sizeof(char *) with 1 */
    if (tokens == NULL)
    {
        perror("malloc");
        _exit(EXIT_FAILURE);
    }

    token = _strtok(input, " ");
    while (token != NULL)
    {
        tokens[i++] = token;
        token = _strtok(NULL, " ");
    }
    tokens[i] = NULL; /* Null-terminate the array */
    return tokens;
}

