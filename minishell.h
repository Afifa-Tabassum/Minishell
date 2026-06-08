#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stddef.h>
#include <ctype.h>
 
#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define SUCCESS 0
#define FAILURE -1

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct node
{
	int pid;
    char command[20];
	struct node *link;
}Slist;

extern Slist *head;

extern char *builtins[];        // declaration 
extern char *external_commands[];    

void scan_input(char *prompt, char *Input_string);
char *get_command(char *input_string);

int check_command_type(char *command);
void echo(char *input_string, int status);
void execute_internal_commands(char *Input_string);
void execute_external_commands(char *Input_string);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);

int insert_first(Slist **head);
int delete_first(Slist **head);
void print_list(Slist *head);

#endif