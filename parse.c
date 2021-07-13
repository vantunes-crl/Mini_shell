#include "mini_shell.h"

char    *take_care_of_env(char *str, t_list *env)
{
    int i;
    char *var;
    int quote;
    int end;
    char *new;
    char *def_var;

    i = 0;
    quote = 0;
    end = 0;

    while (str[i])
    {
        if (str[i] == '\'')
            quote++;
        if (str[i] == '$')
            break ;
        i++;
    }
    if (str[i] == '$' && quote == 0)
    {
        i++;
        if (str[i] == '?')
            return (str);
        end = i;
        while (str[end] >= 'A' && str[end] <= 'Z')
            end++;
        var = ft_substr(str, i, end - i);
        while (env)
        {
            if (ft_strncmp((char *)env->content, var, ft_strlen(var)) == 0)
                break ;
            env = env->next;
        }
        if (!env)
        {
            new = ft_substr(str, 0, i - 2);
            char *temp = ft_strjoin(new, ft_substr(str, end, ft_strlen(str) - end));
            free(new);
            free(var);
            return (temp);
        }
        else
        {
            char *temp_var = ft_strdup((char *)env->content); 
            int x = 0;
            while (temp_var[x] != '=')
                x++;
            x++;
            def_var = ft_substr(temp_var, x, ft_strlen(temp_var) - x);
            new = ft_substr(str, 0, i - 1);
            char *temp = ft_strjoin(new, def_var);
            free(new);
            new = ft_strjoin(temp, ft_substr(str, end, ft_strlen(str) - end));
            return (new);
        }
    }
    else
        return (str);
}

char **parse_cmds(char *str, t_list **env)
{
    char **cmds;
    char *temp_str;
    temp_str = ft_strtrim(str, WHITE_SPACE);

    int i = 0;
    while (temp_str[i])
    {
        if (temp_str[i] == '$')
            temp_str = take_care_of_env(temp_str, *env);
        
        i++;
    }
    if (check_quotes(str) == 1)
        cmds = parse_quotes(temp_str);
    else
        cmds = ft_split(temp_str , ' ');
    free(temp_str);
    return (cmds);
}

/* return number of pipes*/
int has_pipes(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (str[i] == '|')
            count++;
        i++;
    }
    return (count); /* if has pipes return TRUE and number of pipes else FALSE */
}

/* return a cmd list  if have more then one with pipe */
char **cmds_list(char *str)
{
    char **cmds_lst;
    char *temp_str;

    temp_str = ft_strjoin(str, " |");
    cmds_lst = ft_split(temp_str, '|'); /* split the commands by pipes */
    free(temp_str);

    return(cmds_lst);
}