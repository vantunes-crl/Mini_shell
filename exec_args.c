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

void execve_exec(char **paths, char **cmds)
{
    char *temp_path;
    int i;
    int ret;

    i = 0;
    ret = 0;
    while (paths[i])
    {
        temp_path = paths[i];
        paths[i] = ft_strjoin(paths[i], "/");
        free(temp_path);
        temp_path = paths[i]; 
        paths[i] = ft_strjoin(paths[i], cmds[0]);
        free(temp_path);
        ret = execve(paths[i], cmds,  NULL);
        i++;
    }
    if (ret < 0)
        printf("minishell: command not found: %s\n", cmds[0]);
}

/* funtion exec a comand based on the path env variavables */
char **find_path(char **cmds, t_list *env)
{
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
    return (paths);
}

void exce_arg(char **cmds, t_list *env, char **paths)
{
    int abs_path;

    abs_path = is_abspath(cmds[0]);
    if (abs_path)
    {
        abs_path = execve(cmds[0], cmds,  NULL);
        if (abs_path < 0)
            error(cmds[0]);
        return ;
    }
    execve_exec(paths, cmds);
}

/* function then exec the own commands the builtings and the normal shell commands */
void exec_cmd(char **cmds, t_list **env, char **paths)
{
    char *temp;

    if (ft_strncmp(cmds[0],"env", 3) == 0)
        print_env(*env);
    else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
        print_dir();
    else if (ft_strncmp(cmds[0], "echo", 4) == 0)
        print_echo(env, cmds);
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
        exce_arg(cmds, *env, paths);
}

void has_exit(char **cmds_list, t_list **env)
{
    while (*cmds_list)
    {
        if (ft_strncmp(*cmds_list, "exit", 4) == 0)
        {
            deleteList(env);
            free_paths(cmds_list);
            exit(0);
        }
        cmds_list++;
    }
}

void multiple_redirect(int has_redirect, char *cmds_list, t_list **env, char **paths)
{
    char **temp_str;
    t_list *file_list = NULL;
    pid_t pid;
    int fd_red;

    file_list = file_name(cmds_list);
    cmds_list = new_cmds(cmds_list);
    temp_str = parse_cmds(cmds_list);

    while (file_list != NULL)
    {
        pid = fork();
        if (pid == 0)
        {
            fd_red = creat_file(has_redirect, (char *)file_list->content);
            dup2(fd_red, 1);
            close(fd_red);
            exec_cmd(temp_str, env, paths);
            exit(0);
        }
        else
        {
            wait(NULL);
            close(fd_red);
        }
        file_list = file_list->next;
    }
    exit(0);
}

/* function receive a list of commands and exec one by one in the pipe */
void multiple_pipes(char **cmds_list, t_list **env, char **paths)
{
    pid_t pid;
    int fd[2]; // fd[0] fd[1] */ 
    int fd_in = 0;
    int has_redirect = 0;
    char **temp_str;

    int temp_exit;
    while (*cmds_list != NULL) /* while has commands */
    {
        temp_str = NULL;
        if (pipe(fd) < 0)   /* function that creates a pipe in the fd */
            error("pipe");
        pid = fork(); /* function that creates a children process to be killed by exec */
        if (pid < 0)
            error("fork");
        if (pid == 0) /* children process */
        {
            has_redirect = which_redirect(*cmds_list);
            if (has_redirect == 1 || has_redirect == 2)
                multiple_redirect(has_redirect, *cmds_list, env, paths);
            else if (has_redirect == 4)
            {
                close(fd[1]);
                close(fd[0]);
                exec_redin(*cmds_list, env, paths);
            }
            else if (has_redirect == 3)
            {
                close(fd[1]);
                close(fd[0]);
                simple_redirec_in(*cmds_list, env, paths);
            }
            else if (*(cmds_list + 1) != NULL) /* when is the last cmd from the list stop cpy the stdout */
                dup2(fd[1], 1);
            dup2(fd_in, 0);
            close(fd[0]);
            temp_str = parse_cmds(*cmds_list);
            exec_cmd(temp_str, env, paths); /* exec the comand and kill the process */
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