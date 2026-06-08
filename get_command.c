#include "minishell.h"

char *get_command(char *Input_string)
{
    // allocate dynamically
    char *command = calloc(strlen(Input_string) + 1, sizeof(char));

    // skip leading spaces
    int i = 0;
    while (isspace((unsigned char)Input_string[i])) {
        i++;
    }

    // store charector by charector from input string to command until '_' or '\0'
    for (i=0; Input_string[i] != '\0'; i++)
    {
        if (Input_string[i] == ' ')
        {
            break; // stops at first space
        }
        command[i] = Input_string[i];
    }
    command[i] = '\0';

    return command;
}