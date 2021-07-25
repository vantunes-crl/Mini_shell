#include "mini_shell.h"

int check_delim(char *str, int i)
{
    while (str[i])
    {
        if (str[i] == 39 || str[i] == 34)
        {
            char c = str[i];
            i++;
            while (str[i] != c)
                i++;
            return (i);
        }
        else if (str[i] == '|')
        {
            i++;
            return (i);
        }
        i++;
    }
    return (0);
}

static int list_cmds2(char *str, int i, t_list **quoted_lst)
{
    char *temp;
    char *temp2;
    int dlimiter;
    int x;

    x = 0;
    dlimiter = check_delim(str, i);
    temp = malloc(sizeof(char) * check_delim(str, i) + 1);
    while (i <= dlimiter && str[i])
        temp[x++] = str[i++];
    temp[x] = '\0';
    temp2 = temp;
    temp = ft_strtrim(temp, " |");
    free(temp2);
    if (temp[0])
        ft_lstadd_back(quoted_lst, ft_lstnew(ft_strdup(temp)));
    free(temp);
    return (i);
}

char **list_cmds(char *str)
{
    int i;
    t_list *quoted_lst;
    char **cmds;

    ft_strlcat(str, " |", ft_strlen(str) + 3);
    quoted_lst = NULL;
    i = 0;
    cmds = NULL;
    if (check_quotes(str))
    {
        while (str[i])
           i = list_cmds2(str, i, &quoted_lst);
        cmds = list_to_matriz(quoted_lst);
        return (cmds);
    }
    else
        return (cmds = ft_split(str, '|'));
    return (NULL);
}