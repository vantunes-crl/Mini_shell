#include "mini_shell.h"

/* function to hold all error events in the program */
void error(char *str)
{
    perror(str); /* function the returns the sistem error + string */
    exit(0);
}

void    kill_handler(int sig_num)
{
    if (flag == 1)
    {
        printf("\n");
        flag = 0;
    }
    else 
    {
        printf("\n");
    }
}


/* main prompet its a loop then hold all program and wait for next cmds*/
int main(int argc, char **argv, char **env)
{
    char inputString[200]; /* small buffer for input string from stdin */
    char **temp_cmds;
    t_list *envp;
    flag = 0;
    exit_status = 0;

    envp = init_env(env); /* create a cpy of env variavables */
    signal(SIGINT, kill_handler);
    

    while (TRUE)
    {
        if (take_line(inputString)) /* keep going while dont have inputs */
            continue;
        else
        {
            temp_cmds = cmds_list(inputString);
            has_exit(temp_cmds);
            multiple_pipes(temp_cmds, &envp); /* exec multiple pipes */
            free_paths(temp_cmds);
        }
    }
    return (0);
}