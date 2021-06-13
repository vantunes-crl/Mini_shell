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

    while (TRUE)
    {
        if (take_line(inputString))
            continue;
        if (has_pipes(inputString))
            multiple_pipes(cmds_list(inputString));
        else
            exec_cmd(parse_cmds(inputString), env);
    }
    return (0);
}