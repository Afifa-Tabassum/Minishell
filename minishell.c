#include "minishell.h"

char *external_commands[154];
char prompt_name[20] = "minishell";
char Input_string[25];
Slist *head = NULL; //initialize the header to NULL

int main()
{
    system("clear"); // to clear the screen

    extract_external_commands(external_commands);
    // function call
    scan_input(prompt_name, Input_string);
}