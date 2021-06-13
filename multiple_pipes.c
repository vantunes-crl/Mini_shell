
#include "mini_shell.h"

void multiple_pipes(int pipes)
{
    pid_t pid;
    pid_t pid2;
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
        close(fd[0][1]);
        close(fd[0][0]);
        close(fd[1][0]);
        close(fd[1][1]);
        exce_arg(parse_cmds("ls -l"));
    }

    pid2 = fork();
    if (pid2 == 0)
    {   
        dup2(fd[0][0], 0); // cpy from stdin to the first pipe
        dup2(fd[1][1],1); // cpy from pipe1 to pipe2
        close(fd[0][1]);
        close(fd[0][0]);
        close(fd[1][1]);
        close(fd[1][0]);
        exce_arg(parse_cmds("ls -l"));
    }

    pid_t pid3;

    pid3 = fork();
    if (pid3 == 0)
    {
        dup2(fd[1][0],0); //cpy from pipe1 to pipe2
        close(fd[0][1]);
        close(fd[0][0]);
        close(fd[1][1]);
        close(fd[1][0]);
        exce_arg(parse_cmds("cat -e"));
    }

    close(fd[0][1]);
    close(fd[0][0]);
    close(fd[1][1]);
    close(fd[1][0]);
    wait(NULL);
    wait(NULL);
    wait(NULL);
}