#include "mini_shell.h"

/* function to hold all error events in the program */
void error(char *str)
{
    perror(str); /* function the returns the sistem error + string */
    exit(0);
}

/* main prompet its a loop then hold all program and wait for next cmds*/
int main(int argc, char **argv, char **env)
{
    char inputString[200]; /* small buffer for input string from stdin */
    char **cmds;
    t_list *envp;

    envp = init_env(env); /* create a cpy of env variavables */
    while (TRUE)
    {
        if (take_line(inputString)) /* keep going while dont have inputs */
            continue;
        if (has_pipes(inputString))
            multiple_pipes(cmds_list(inputString), &envp); /* exec multiple pipes */
        else
            exec_cmd(parse_cmds(inputString), &envp); /* exec normal cmd */
    }
    return (0);
}