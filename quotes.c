#include "mini_shell.h"

int     check_quotes(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 34 || str[i] == 39)
            return (1);
        i++;
    }
    return (0);
}

int choose_quote(char *str)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (str[i] == 34)
            return (1);
        else if (str[i] == 39)
            return (2);
        i++;
    }
    return (0);
}

int handle_cif_env(char *str)
{
    int i;

    i = 0;
    while (str[i] != '$' && str[i] != '\0')
        i++;
    if (str[i] == '$' && str[i - 1] == '\'')
        return (1);
    else
        return (0);
    
}

char **parse_quotes(char *str)
{
    int end;
    int start;
    t_list *list;
    char *temp;
    char **cmds;
    start = 0;
    end = 0;
    list = NULL;
    cmds = NULL;

    flag_env = handle_cif_env(str);
    while(str[start])
    {
        if (str[start] == '"')
        {
            start++;
            end = start;
            while (str[end] != 34 && str[end] != '\0')
                end++;
            temp = ft_substr(str, start, end - start);
            ft_lstadd_back(&list, ft_lstnew(temp));
            end++;
            start = end;
        }
        else if (str[start] == '\'')
        {
            start++;
            end = start;
            while (str[end] != 39 && str[end] != '\0')
                end++;
            temp = ft_substr(str, start, end - start);
            ft_lstadd_back(&list, ft_lstnew(temp));
            end++;
            start = end;
        }
        else if(str[start] == ' ')
            start++;
        else
        {
            end = start;
            while (str[end] != 32 && str[end] != '\0')
                end++;
            temp = ft_substr(str, start, end - start);
            ft_lstadd_back(&list, ft_lstnew(temp));
            end++;
            start = end;
        }
    }
    cmds = malloc(sizeof(char *) * ft_lstsize(list) + 1);
    int i = 0;
    while (list)
    {
        cmds[i] = ft_strdup((char *)list->content);
        list = list->next;
        i++;
    }
    cmds[i] = 0;
    return (cmds);
}
