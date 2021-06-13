#include "mini_shell.h"

void error(char *str)
{
    perror(str);
    exit(0);
}

void owncmds(int cmd)
{
    char *str;

    str = getenv("USER");
    if (cmd == 0) // exit
    {
        printf("\033[0;31mGood  Bye\e[0m %s \U0001F97A\U0001F97A\U0001F97A\U0001F97A\n", str);
        exit(0);
    }
    else if (cmd == 1)
    {
        printf("--------------------------------------Help--------------------------------------\n");
        printf("exit == quit the program\n");
        printf("cd `dest` == change the directory\n");
        printf("--------------------------------------------------------------------------------\n");
    }
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
            multiple_pipes(cmds_list(inputString));
        else
        {
            cmds = parse_cmds(inputString);
            if (ft_strncmp(cmds[0],"cd", 2) == 0)
                chdir(cmds[1]);
            else if (ft_strncmp(cmds[0],"exit", 4) == 0)
                owncmds(0);
            else if (ft_strncmp(cmds[0],"help", 4) == 0)
                owncmds(1);
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