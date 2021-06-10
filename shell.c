#include "mini_shell.h"

int exce_args(char **cmds)
{
    pid_t pid;
    char **paths;
    int i = 0;
    int j = 0;

    paths = ft_split(getenv("PATH"), ':');
    pid = fork();
    if (pid == -1)
        perror("fork");
    else if (pid == 0)
    {
        while (paths[i])
        {
            paths[i] = ft_strjoin(paths[i], "/");
            paths[i] = ft_strjoin(paths[i], cmds[0]);
            execve(paths[i], cmds,  NULL);
            i++;
        }
        exit(0);
    }
    wait(NULL);
}

int take_line(char *str)
{
    char *buff;

    buff = readline("\033[3;32mMiniShell:");
    if (ft_strlen(buff) != 0)
    {
        add_history(buff);
        ft_memcpy(str, buff , ft_strlen(buff));
        return (0);
    }
    else
        return (1);
}

char **parse_cmds(char *str)
{
    char **cmds;

    str = ft_strtrim(str, "\t ");
    cmds = ft_split(str, ' ');
    return (cmds);
}

int main()
{
    char inputString[200];
    char **cmds;
    char **pipes;
    int i = 0; 

    while (1)
    {
        if (take_line(inputString))
            continue ;
    //pipes = ft_split(inputString, '|');
        cmds = parse_cmds(inputString);
    // while (pipes[i])
    // {
    //     if (pipes[i])
    //         pipes[i] = ft_strtrim(pipes[i], "\t ");
    // }
        exce_args(cmds);
    }
}