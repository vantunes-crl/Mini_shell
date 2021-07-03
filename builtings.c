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
    cmds++;
    if (ft_strncmp(*cmds, "-n", 2) == 0) /* take of the line breaker */
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

/* builting function to simulate pwd in shell */
void print_dir()
{
    char str[1040];

    getcwd(str, sizeof(str)); /* function that get the actual Directory from the sistem */
    printf("%s\n",str);
}

/* builting function to simulate env in shell without parameters */
void print_env(t_list *envp)
{
    while (envp != NULL)
    {
        printf("%s\n",(char *)envp->content); /* print all env lst */
        envp = envp->next;
    }
}

void  ft_cd(char **temp_cmds)
{
    char **temp_dir;

    temp_dir = ft_split(temp_cmds[0], ' ');
    chdir(temp_dir[1]);
    free_paths(temp_dir);
    free_paths(temp_cmds);
}

void ft_unset(char **temp_cmds, t_list *envp)
{
    char **temp_dir;

    temp_dir = ft_split(temp_cmds[0], ' ');
    del_elem_lst(&envp, temp_dir[1]);
    free_paths(temp_dir);
    free_paths(temp_cmds);
}

void ft_export(char **temp_cmds, t_list *envp)
{
    char **temp_dir;

    temp_dir = ft_split(temp_cmds[0], ' ');
    ft_lstadd_back(&envp, ft_lstnew(temp_dir[1]));
    free_paths(temp_cmds);
}