#include "minishell.h"

int status;
int pid;

void scan_input(char *prompt_name, char *Input_string)
{
    //Register a signals
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGCHLD, signal_handler);

    while(1) 
    {
        printf(ANSI_COLOR_GREEN "%s$:" ANSI_COLOR_RESET, prompt_name); // prompt

        // print current directory path
        char path[50];
        getcwd(path, sizeof(path));
        printf(ANSI_COLOR_BLUE "~%s " ANSI_COLOR_RESET, path);

        // read input until newline
        if (scanf("%[^\n]", Input_string) != 1) {
            getchar(); // consume newline
            continue;
        }
        getchar();

        // Validations for PS1
        if (strncmp(Input_string, "PS1=", 4) == 0)
        {
            if (Input_string[4] == ' ' || Input_string[4] == '\0')
            {
                printf("Invalid command\n");
                return;
            } else{
                strcpy(prompt_name, Input_string + 4);
            }
            // clear Input_string buffer 
            memset(Input_string, 0, sizeof(Input_string));
            continue;
        } 

        char *command = get_command(Input_string);
        int type = check_command_type(command);

        if (type == 2)
        {
            pid = fork();
            if (pid == 0)
            {
                // CHILD
                // changing signals to default
                signal(SIGINT, SIG_DFL);
                signal(SIGTSTP, SIG_DFL);
                execute_external_commands(Input_string);
            }
            else
            {
                // PARENT
                waitpid(pid, &status, WUNTRACED);
            }
        }
        else if (type == 1)
        {
            execute_internal_commands(Input_string);
        } else {
            printf("Command not found\n");
        }
    }
}