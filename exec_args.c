#include "mini_shell.h"

int exce_arg(char **cmds)
{
    pid_t pid;
    char **paths;
    int i = 0;

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
    waitpid(pid, NULL,0);
}

void exec_pipes(char *str)
{
    char **cmds_lst;
    int fd[2];
    pid_t pid1;
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
        dup2(fd[0], STDIN_FILENO);
	    close(fd[0]);
	    close(fd[1]);
        exce_arg(parse_cmds(cmds_lst[1]));
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
}