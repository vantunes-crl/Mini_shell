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

    buff = readline("\033[3;32mMiniShell\e[0m\U0001F916:");
    if (ft_strlen(buff) != 0)
    {
        add_history(buff);
        strcpy(str, buff);
        return (0);
    }
    else
        return (1);
}

char **parse_cmds(char *str)
{
    char **cmds;
    int i = 0;

    cmds = ft_split(str, ' ');
    while (cmds[i] != NULL)
    {
        cmds[i] = ft_strtrim(cmds[i], "\t ");
        i++;
    }
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
         if (ft_strncmp(cmds[0],"cd", 2) == 0)
            chdir(cmds[1]);
         else if (ft_strncmp(cmds[0],"exit", 4) == 0)
            exit(0);
         else
            exce_args(cmds);
    }
}