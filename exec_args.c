#include "mini_shell.h"

/* funtion exec a comand based on the path env variavables */
void exce_arg(char **cmds, t_list *env)
{
    int i = 0;
    char **paths;
    while (env)
    {
        if (ft_strncmp((char *)env->content, "PATH", 4) == 0) /* find the env PATH in the env(cpy) list */
            break ;
        env = env->next;
    }
    if (!env) /* if dont exists path env var */
        error("No such file or directory");
    paths = ft_split((char *)env->content, ':'); /* split all bin directorys */
    while (paths[i]) /* keep trying exec until sucess */
    {
        paths[i] = ft_strjoin(paths[i], "/");
        paths[i] = ft_strjoin(paths[i], cmds[0]);
        execve(paths[i], cmds,  NULL);
        i++;
    }
}

/* function then exec the own commands the builtings and the normal shell commands */
void exec_cmd(char **cmds, t_list **env)
{
    if (ft_strncmp(cmds[0],"cd", 2) == 0) /* handle all commands events */
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

/* function receive a list of commands and exec one by one in the pipe */
void multiple_pipes(char **cmds_list, t_list **env)
{
    pid_t pid;
    int fd[2];
    int fd_in = 0;
    while (*cmds_list != NULL) /* while has commands */
    {
        pipe(fd); /* function that creates a pipe in the fd */
        pid = fork(); /* function that creates a children process to be killed by exec*/
        if (pid == 0) /* children process */
        {   
            dup2(fd_in, 0); /* cpy the stdin */
            if (*(cmds_list + 1) != NULL) /* when is the last cmd from the list stop cpy the stdout */
                dup2(fd[1], 1);
            close(fd[0]);
            exce_arg(parse_cmds(*cmds_list), *env); /* exec the comand and kill the process */
        }
        else
        {
            wait(NULL); /* wait the children end */
            close(fd[1]);
            fd_in = fd[0]; /* keep tracking the old stdin */
            cmds_list++;
        }
    }
}