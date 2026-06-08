#include "minishell.h"

extern int pid;
extern int status;
extern char Input_string[25];

void signal_handler(int signum)
{
    if (signum == SIGINT)  // ^C
    {
        if (pid == 0) {
            printf(ANSI_COLOR_GREEN "\nminishell$ " ANSI_COLOR_RESET);
            fflush(stdout);
        }
    }
    else if (signum == SIGTSTP)  // ^Z
    {
        if (pid == 0) {
            printf(ANSI_COLOR_GREEN "\nminishell$ " ANSI_COLOR_RESET);
            fflush(stdout);
        }
        else
        {
            insert_first(&head);
        }
    }
    else if (signum == SIGCHLD)
    {
       int pid = waitpid(-1, &status, WNOHANG);
       if (pid > 0) {
           delete_first(&head);
       }
    }
}

int insert_first(Slist **head)
{
    Slist *new = malloc(sizeof(Slist));
    if (!new)
      return FAILURE;

    new->pid = pid;
    strcpy(new->command, Input_string);
    new->link = *head;
    *head = new;
  
    return SUCCESS;
}

int delete_first(Slist **head)
{
    if (*head == NULL) {
        return FAILURE;
    }

    Slist *temp = *head;
    *head = temp->link;
    free(temp);
    
    return SUCCESS;
}

void print_list(Slist *head)
{
	if (head == NULL) {
		printf("INFO : List is empty\n");
	}
    while (head) {
		printf("%d   ", head->pid);
        if(strcmp(Input_string, "bg") == 0) {
            printf("Running   ");
        } else {
            printf("Stopped   ");
        }
        printf("%s\n", head->command);
		head = head -> link;
	}
}