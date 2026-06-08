#include "minishell.h"

void extract_external_commands(char **external_commands)
{
    // open the file in read mode
    int fdr = open("external_commands.txt", O_RDONLY, 0666);
    if (fdr == -1)
    {
        printf("File doesn't exist1\n");
        exit(0);
    }

    char ch;
    char cmd[20];
    int i = 0; // pos in cmd buf
    int j = 0; // no. of cmd we have stored
    int ret;

    while((ret = read(fdr, &ch, 1)) > 0)
    {
        if (ch == '\n' || ch == '\r') 
        {
            cmd[i] = '\0';
            if (i > 0) {
                external_commands[j++] = strdup(cmd);
            }
            i = 0; // reset for next command
        } 
        else {
            cmd[i++] = ch;
        }
    }
    external_commands[j] = NULL;
    close(fdr);
}