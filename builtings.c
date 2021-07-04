#include "mini_shell.h"

static void handler_part(char *content, int flag, int n)
{
    char *var_env;
    char *temp;
    int i;

    var_env = ft_strdup(content);
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

void    handle_var_env(char *var_env, t_list *env, int flag, int n)
{
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
    handler_part((char *)env->content, flag, n);
}

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
    cmds++;
    if (ft_strncmp(*cmds, "-n", 2) == 0)
    { 
        n = 1;
        cmds++;
    }
    if (ft_strncmp(*cmds, "$", 1) == 0)
    {
        i = 0;
        var_env = ft_strdup(*cmds);
        temp = var_env;
        var_env = ft_strtrim(temp, "$");
        free(temp);
        if (n)
            handle_var_env(var_env, *env, 0, 0);
        else
            handle_var_env(var_env, *env, 0, 1);
        return ;
    }
    else
    {
        while (*cmds)
        {
            if (*(cmds + 1) == NULL)
                printf("%s", *cmds);
            else
                printf("%s ", *cmds);
            cmds++;
        }
    }
    if (!n)
        printf("\n");
}

void print_dir()
{
    char str[1040];

    getcwd(str, sizeof(str));
    printf("%s\n",str);
}

void print_env(t_list *envp)
{
    while (envp != NULL)
    {
        printf("%s\n",(char *)envp->content);
        envp = envp->next;
    }
}