#include "mini_shell.h"

char **parse_cmds(char *str)
{
    char **cmds;
    int i = 0;

    cmds = ft_split(str, ' ');
    while (cmds[i] != NULL)
    {
        cmds[i] = ft_strtrim(cmds[i], WHITE_SPACE);
        i++;
    }
    return (cmds);
}

int has_pipes(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (TRUE);
        i++;
    }
    return (FALSE);
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