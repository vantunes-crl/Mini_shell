#include "mini_shell.h"

void error(char *str)
{
    perror(str);
    exit(0);
}

int main()
{
    char inputString[200];
    char **cmds;

    while (TRUE)
    {
        if (take_line(inputString))
            continue;
        if (has_pipes(inputString))
            multiple_pipes(2);
        else
        {
            cmds = parse_cmds(inputString);
            if (ft_strncmp(cmds[0],"cd", 2) == 0)
                chdir(cmds[1]);
            else if (ft_strncmp(cmds[0],"exit", 4) == 0)
                exit(0);
            else
            {
                pid_t pid;
                pid = fork();
                if (pid == 0)
                    exce_arg(cmds);
                else
                    wait(NULL);
            }
        }
    }
}