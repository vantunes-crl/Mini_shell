#include "mini_shell.h"

void    handle_var_env(char *var_env, t_list *env, int flag, int n)
{
    char *temp;
    int i;
    
    while (env)
    {
        if (ft_strncmp((char *)env->content, var_env, 4) == 0)
            break ;
        env = env->next;
    }
    if (!env)
    {
        if (flag == 0)
            printf("\n");
        free(var_env);
        return ;
    }
    free(var_env);
    var_env = ft_strdup(env->content);
    temp = var_env;
    i = 0;
    while (temp[i] != '=')
        i++;
    var_env = ft_substr(temp, i + 1, ft_strlen(temp));
    free(temp);
    if (flag == 1)
        printf("minishell: command not found: ");
    printf("%s", var_env);
    if (n == 1)
        printf("\n");
    free(var_env);
}

/* builting function to simulate echo in shell */
void print_echo(t_list **env, char **cmds)
{
    int n;
    int i;
    char *var_env;
    char *temp;

    n = 0;
    if (!cmds[1])
    {
        printf("\n");
        return ;
    }
    if (ft_strncmp("-n", cmds[1], 3) == 0 && !cmds[2])
        return ;
    i = 1;
    if (ft_strncmp(cmds[i], "-n", 2) == 0)
    { 
        n = 1;
        i++;
    }
    while (cmds[i])
    {
        if (!cmds[i + 1])
            ft_putstr_fd(cmds[i], 1);
        else
        {
            ft_putstr_fd(cmds[i], 1);
            write(1, " ", 1);
        }
        i++;
    }
    if (!n)
        printf("\n");
    exit(0);
}

void ft_cd(char **temp_cmds)
{
    char **temp_dir;

    temp_dir = ft_split(temp_cmds[0], ' ');
    chdir(temp_dir[1]);
    free_paths(temp_dir);
    free_paths(temp_cmds);
}

void ft_unset(t_list *envp, char **temp_cmds)
{
    char **temp_dir;

    temp_dir = ft_split(temp_cmds[0], ' ');
    del_elem_lst(&envp, temp_dir[1]);
    free_paths(temp_dir);
    free_paths(temp_cmds);
}

void ft_export(t_list *envp, char **temp_cmds)
{
    char **temp_dir;

    temp_dir = ft_split(temp_cmds[0], ' ');
    ft_lstadd_back(&envp, ft_lstnew(temp_dir[1]));
    free_paths(temp_cmds);
}