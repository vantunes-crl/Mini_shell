#include "mini_shell.h"

char **parse_cmds(char *str)
{
    char **cmds;
    int i = 0;

    str = ft_strtrim(str, WHITE_SPACE);
    cmds = ft_split(str, ' ');
    return (cmds);
}

/* return number of pipes */
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
    return (count);
}

/* return a cmd list */
char **cmds_list(char *str)
{
    char **cmds_lst;
    int i = 0;

    cmds_lst = ft_split(str, '|');
    while (cmds_lst[i] != NULL)
    {
        cmds_lst[i] = ft_strtrim(cmds_lst[i], WHITE_SPACE);
        i++;
    }
    return(cmds_lst);
}