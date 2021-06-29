#include "mini_shell.h"

/* return a command splited and without white spaces */
char **parse_cmds(char *str)
{
    char **cmds;
    char *temp_str;

    temp_str = ft_strtrim(str, WHITE_SPACE); /* take of the withspaces from the begining and end of string */
    cmds = ft_split(temp_str , ' '); /* split based on spaces */
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

    temp_str = ft_strtrim(str, WHITE_SPACE); /* take of all whitespaces from end and begining */
    temp_str = ft_strjoin(temp_str, " |");
    cmds_lst = ft_split(temp_str, '|'); /* split the commands by pipes */
    free(temp_str);
    return(cmds_lst);
}