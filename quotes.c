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
typedef struct s_quotes
{
    int start;
    int end;
}           t_quotes;

static void case1(t_quotes *qt, char *str, t_list *list)
{
    char *temp;

    qt->start++;
    qt->end = qt->start;
    while (str[qt->end] != 34 && str[qt->end] != '\0')
        qt->end++;
    temp = ft_substr(str, qt->start, qt->end - qt->start);
    ft_lstadd_back(&list, ft_lstnew(temp));
    qt->end++;
    qt->start = qt->end;
}

static void case2(t_quotes *qt, char *str, t_list *list)
{
    char *temp;

    qt->start++;
    qt->end = qt->start;
    while (str[qt->end] != 39 && str[qt->end] != '\0')
        qt->end++;
    temp = ft_substr(str, qt->start, qt->end - qt->start);
    ft_lstadd_back(&list, ft_lstnew(temp));
    qt->end++;
    qt->start = qt->end;
}

static void last_case(t_quotes *qt, char *str, t_list *list, char *temp)
{
    qt->end = qt->start;
    while (str[qt->end] != 32 && str[qt->end] != '\0')
        qt->end++;
    temp = ft_substr(str, qt->start, qt->end - qt->start);
    ft_lstadd_back(&list, ft_lstnew(temp));
    qt->end++;
    qt->start = qt->end;
}

char **parse_quotes(char *str)
{
    t_quotes qt;
    t_list *list;
    char *temp;
    char **cmds;

    list = NULL;
    qt.start = 0;
    qt.end = 0;
    flag_env = handle_cif_env(str);
    while(str[qt.start])
    {
        if (str[qt.start] == '"')
            case1(&qt, str, list);
        else if (str[qt.start] == '\'')
            case2(&qt, str, list);
        else if(str[qt.start] == ' ')
            qt.start++;
        else
        {
            qt.end = qt.start;
            while (str[qt.end] != 32 && str[qt.end] != '\0')
                qt.end++;
            temp = ft_substr(str, qt.start, qt.end - qt.start);
            ft_lstadd_back(&list, ft_lstnew(temp));
            qt.end++;
            qt.start = qt.end;
          //  last_case(&qt, str, list, temp);
        }
    }
    cmds = list_to_matriz(list);
    //ft_deletelist(list);
    return (cmds);
}
