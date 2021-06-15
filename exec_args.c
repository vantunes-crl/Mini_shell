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

void exec_cmd(char **cmds, char **env)
{
    if (ft_strncmp(cmds[0],"cd", 2) == 0)
        chdir(cmds[1]);
    else if (ft_strncmp(cmds[0],"exit", 4) == 0)
        owncmds(0);
    else if (ft_strncmp(cmds[0],"help", 4) == 0)
        owncmds(1);
    else if (ft_strncmp(cmds[0],"env", 3) == 0)
        print_env(env);
    else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
        print_dir();
    else if (ft_strncmp(cmds[0], "echo", 4) == 0)
        print_echo(cmds);
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

void multiple_pipes(char **cmds_list)
{
    pid_t pid;
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
    }
}