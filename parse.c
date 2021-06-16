#include "mini_shell.h"

/* return a command splited and without white spaces */
char **parse_cmds(char *str)
{
    char **cmds;
    int i = 0;

    str = ft_strtrim(str, WHITE_SPACE); /* take of the withspaces from the begining and end of string */
    cmds = ft_split(str, ' '); /* split based on spaces */
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
    int i = 0;

    cmds_lst = ft_split(str, '|'); /* split the commands by pipes */
    while (cmds_lst[i] != NULL)
    {
        cmds_lst[i] = ft_strtrim(cmds_lst[i], WHITE_SPACE); /* take of all whitespaces from end and begining */
        i++;
    }
    return(cmds_lst);
}