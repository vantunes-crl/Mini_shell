#include "mini_shell.h"

char *find_filename(char *cmd)
{
    char **cmd_list;
    char *temp;
    int i;

    i = 0;
    cmd_list = ft_split(cmd, ' ');
    if (ft_strncmp(cmd_list[0], "<", 1) == 0)
    {
        temp = ft_strdup(cmd_list[1]);
        free_paths(cmd_list);
        return(temp);
    }
    else
    {
        while (*(cmd_list + 1))
            cmd_list++;
        temp = ft_strdup(*cmd_list);
        while (cmd_list[i] != NULL)
            free(cmd_list[i++]);
        return(temp);
    }
}

char *new_cmd_in(char *cmd)
{
    char **cmd_list;
    char *new_str;
    char *temp;
    char temp2;
    int i;

    i = 0;
    new_str = ft_strdup("");
    cmd_list = ft_split(cmd, ' ');
    if (ft_strncmp(cmd_list[0], "<", 1) == 0)
    {
        cmd_list++;
        cmd_list++;
        while (*cmd_list)
        {
            temp = new_str;
            new_str = ft_super_strjoin(3, new_str, " ", *cmd_list);
            free(temp);
            cmd_list++;
        }
        while (cmd_list[i] != NULL)
            free(cmd_list[i++]);
        return (new_str);
    }
    else
    {
        while (*cmd_list)
        {
            if (ft_strncmp("<", *cmd_list, 1) == 0)
                break;
            temp = new_str;
            new_str = ft_super_strjoin(3, new_str, " ", *cmd_list);
            free(temp);
            cmd_list++;
        }
        while (cmd_list[i] != NULL)
            free(cmd_list[i++]);
        return (new_str);
    }
    return (NULL);
}