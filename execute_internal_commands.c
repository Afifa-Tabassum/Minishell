#include "minishell.h"

extern int status;

void execute_internal_commands(char *Input_string)
{
    if (strcmp(Input_string, "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(Input_string, "pwd") == 0)
    {
        char path[50];
        getcwd(path, sizeof(path));
        printf("%s\n", path);
    }
    else if(strcmp(Input_string, "cd") == 0)
    {
        chdir(Input_string+3);
    }
    else if(strcmp(Input_string, "echo $$") == 0)
    {
        int ret = getpid();
        printf("%d\n", ret);
    }
    else if(strcmp(Input_string, "echo $?") == 0)
    {
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("%d\n", WEXITSTATUS(status));
        }
    }
    else if(strcmp(Input_string, "echo $SHELL") == 0)
    {
        char *buf = getenv("SHELL");
        if (buf != NULL) {
        printf("%s\n", buf);
    }
    }
    else if(strcmp(Input_string, "jobs") == 0)
    {
        print_list(head);
    } 
    else if(strcmp(Input_string, "bg") == 0)
    {
        kill(head->pid, SIGCONT);
    }
    else if(strcmp(Input_string, "fg") == 0)
    {
        kill(head->pid, SIGCONT);   // resume the stopped process
        int pid = waitpid(head->pid, &status, WUNTRACED); // waits for the process to finish or be stopped.
        if(pid == head->pid)
        {
            delete_first(&head);
        }
    } 
}