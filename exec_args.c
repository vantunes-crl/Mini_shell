#include "mini_shell.h"

int is_abspath(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

/* funtion exec a comand based on the path env variavables */
void exce_arg(char **cmds, t_list *env)
{
    int i = 0;
    char **paths;
    char *temp_path;
    int abs_path;
    int ret;

    ret = 0;
    abs_path = is_abspath(cmds[0]);
    if (abs_path)
    {
        abs_path = execve(cmds[0], cmds,  NULL);
        if (abs_path < 0)
            error(cmds[0]);
        return ;
    }
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
        temp_path = paths[i]; /* old pointer */
        paths[i] = ft_strjoin(paths[i], "/"); /* new pointer */
        free(temp_path); /* free old */
        temp_path = paths[i]; 
        paths[i] = ft_strjoin(paths[i], cmds[0]);
        free(temp_path);
        ret = execve(paths[i], cmds,  NULL);
        i++;
    }
    free_paths(paths);
    if (ret < 0)
        printf("zsh: command not found: %s\n", cmds[0]);
}

/* function then exec the own commands the builtings and the normal shell commands */
void exec_cmd(char **cmds, t_list **env)
{
    char *temp;

    if (ft_strncmp(cmds[0],"cd", 2) == 0) /* handle all commands events */
        chdir(cmds[1]);
    else if (ft_strncmp(cmds[0],"help", 4) == 0)
        owncmds(1, env);
    else if (ft_strncmp(cmds[0],"env", 3) == 0)
        print_env(*env);
    else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
        print_dir();
    else if (ft_strncmp(cmds[0], "echo", 4) == 0)
        print_echo(env, cmds);
    else if (ft_strncmp(cmds[0], "unset", 5) == 0)
        del_elem_lst(env, cmds[1]);
    else if (ft_strncmp(cmds[0], "export", 6) == 0)
        ft_lstadd_back(env, ft_lstnew(cmds[1]));
    else if (ft_strncmp(cmds[0], "$?", 2) == 0)
    {
        printf("%d\n", exit_status);
        exit_status = 0;
    }
    else if (ft_strncmp(cmds[0], "$", 1) == 0)
    {
        temp = ft_strtrim(*cmds, "$");
        handle_var_env(temp, *env, 1, 1);
    }
    else
        exce_arg(cmds, *env);
    free_paths(cmds);
}

void has_exit(char **cmds_list)
{
    char *temp_str;

    while (*cmds_list)
    {
        temp_str = ft_strtrim(*cmds_list, WHITE_SPACE);
        if (ft_strncmp(temp_str, "exit", 4) == 0)
        {
            free(temp_str);
            exit(0);
        }
        free(temp_str);
        cmds_list++;
    }
}

/* function receive a list of commands and exec one by one in the pipe */
void multiple_pipes(char **cmds_list, t_list **env)
{
    pid_t pid;
    int fd[2]; // fd[0] fd[1] */ 
    int fd_in = 0;
    char **temp_str;

    int temp_exit;
    while (*cmds_list != NULL) /* while has commands */
    {
        if (pipe(fd) < 0)   /* function that creates a pipe in the fd */
            error("pipe");
        pid = fork(); /* function that creates a children process to be killed by exec */
        if (pid < 0)
            error("fork");
        if (pid == 0) /* children process */
        {   
            dup2(fd_in, 0); /* cpy the stdin */
            if (*(cmds_list + 1) != NULL) /* when is the last cmd from the list stop cpy the stdout */
                dup2(fd[1], 1);
            close(fd[0]);
            temp_str = parse_cmds(*cmds_list);
            exec_cmd(temp_str, env); /* exec the comand and kill the process */
            exit(0);
        }
        else
        {
            wait(&temp_exit); /* wait the children end and get the exit status */
            if (temp_exit)
                exit_status = temp_exit;
            close(fd[1]);
            fd_in = fd[0]; /* keep tracking the old stdin */
            cmds_list++;
        }
    }
}