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
    if (ft_strncmp(cmds[i], "-n", 2) == 0) /* take of the line breaker */
    { 
        n = 1;
        i++;
    }
    else
    {
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
    }
    if (!n)
        printf("\n");
    exit(0);
}