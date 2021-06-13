#include "mini_shell.h"

void close_fds(int pipes, int **fd)
{
    int i = 0;
    int j;

    while (i < pipes)
    {
        j = 0;
        while (j < 2)
        {
            close(fd[i][j]);
            j++;
        }
    i++;
    }
}

void multiple_pipes(char **cmds_list)
{
    pid_t pid;
    int i = 0;
    int fd[2];
    int fd_in = 0;
    while (*cmds_list != NULL)
    {
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {   
            dup2(fd_in, 0);
            if (*(cmds_list + 1) != NULL)
                dup2(fd[1], 1);
            close(fd[0]);
            exce_arg(parse_cmds(*cmds_list));
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            fd_in = fd[0];
            cmds_list++;
        }
       i++;
    }
}