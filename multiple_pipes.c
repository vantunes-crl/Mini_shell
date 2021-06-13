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

void multiple_pipes(int pipes)
{
    pid_t pid;
    int i = -1;
    int **fd;

    fd = ft_calloc(pipes + 1, sizeof(int));
    while (++i < pipes)
        fd[i] = ft_calloc(2, sizeof(int));
    i = -1;
    while (++i < pipes)
        pipe(fd[i]);

    pid = fork();
    if (pid == 0)
    {   
        dup2(fd[0][1], 1); // cpy from stdout to the first pipe
        close_fds(pipes, fd);
        exce_arg(parse_cmds("ls -l"));
    }

    pid = fork();
    if (pid == 0)
    {   
        dup2(fd[0][0], 0); // cpy from stdin to the first pipe
        dup2(fd[1][1],1); // cpy from pipe1 to pipe2
        close_fds(pipes, fd);
        exce_arg(parse_cmds("ls -l"));
    }

    pid = fork();
    if (pid == 0)
    {
        dup2(fd[1][0],0); //cpy from pipe1 to pipe2
        close_fds(pipes, fd);
        exce_arg(parse_cmds("cat -e"));
    }
    close_fds(pipes, fd);
    i = -1;
    while (++i <= pipes)
        wait(NULL);
}