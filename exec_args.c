#include "mini_shell.h"

void exce_arg(char **cmds)
{
    char **paths;
    int i = 0;

    paths = ft_split(getenv("PATH"), ':');
    while (paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        paths[i] = ft_strjoin(paths[i], cmds[0]);
        execve(paths[i], cmds,  NULL);
        i++;
    }
}

void exec_pipes(char *str)
{
    char **cmds_lst;
    int fd[2];
    pid_t pid1;
    pid_t pid2;
    int status;

    cmds_lst = cmds_list(str);
    if (pipe(fd) < 0)
        error("pipe");
    pid1 = fork();
    if (pid1 < 0)
        error("fork");
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
	    close(fd[0]);
	    close(fd[1]);
        exce_arg(parse_cmds(cmds_lst[0]));
    }
    else
    {
        pid2 = fork();
        if (pid2 < 0)
            error("fork");
        if (pid2 == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            exce_arg(parse_cmds(cmds_lst[1]));
        }
        else
        {
            wait(NULL);
            wait(NULL);
        }
    }
    close(fd[1]);
    close(fd[0]);
}