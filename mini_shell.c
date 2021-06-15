#include "mini_shell.h"

void error(char *str)
{
    perror(str);
    exit(0);
}

int main(int argc, char **argv, char **env)
{
    char inputString[200];
    char **cmds;
    t_list *envp;

    envp = init_env(env);
    while (TRUE)
    {
        if (take_line(inputString))
            continue;
        if (has_pipes(inputString))
            multiple_pipes(cmds_list(inputString), &envp);
        else
            exec_cmd(parse_cmds(inputString), &envp);
    }
    return (0);
}