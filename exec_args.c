#include "mini_shell.h"

void exce_arg(char **cmds, t_list *env)
{
    int i = 0;
    char **paths;
    while (env)
    {
        if (ft_strncmp((char *)env->content, "PATH", 4) == 0)
            break ;
        env = env->next;
    }
    if (!env)
        error("No such file or directory");
    paths = ft_split((char *)env->content, ':');
    while (paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        paths[i] = ft_strjoin(paths[i], cmds[0]);
        execve(paths[i], cmds,  NULL);
        i++;
    }
}

void print_env(t_list *envp)
{
    while (envp != NULL)
    {
        printf("%s\n",(char *)envp->content);
        envp = envp->next;
    }
}

void exec_cmd(char **cmds, t_list **env)
{
    if (ft_strncmp(cmds[0],"cd", 2) == 0)
        chdir(cmds[1]);
    else if (ft_strncmp(cmds[0],"exit", 4) == 0)
        owncmds(0);
    else if (ft_strncmp(cmds[0],"help", 4) == 0)
        owncmds(1);
    else if (ft_strncmp(cmds[0],"env", 3) == 0)
        print_env(*env);
    else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
        print_dir();
    else if (ft_strncmp(cmds[0], "echo", 4) == 0)
        print_echo(cmds);
    else if (ft_strncmp(cmds[0], "unset", 5) == 0)
        del_elem_lst(env, cmds[1]);
    else if (ft_strncmp(cmds[0], "export", 6) == 0)
        ft_lstadd_back(env, ft_lstnew(cmds[1]));
    else
    {
        pid_t pid;
        pid = fork();
        if (pid == 0)
            exce_arg(cmds, *env);
        else
            wait(NULL);
    }
}

void multiple_pipes(char **cmds_list, t_list **env)
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
            exce_arg(parse_cmds(*cmds_list), *env);
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