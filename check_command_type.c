#include "minishell.h"

int check_command_type(char *command)
{
     // check builtins
    for (int i = 0; builtins[i] != NULL; i++) {
        if (strcmp(command, builtins[i]) == 0) {
            return BUILTIN;
        }
    }

    // check external commands
    for (int i = 0; external_commands[i] != NULL; i++) {
        if (strcmp(command, external_commands[i]) == 0) {
            return EXTERNAL;
        }
    }

    return NO_COMMAND;
}