#include "mini_shell.h"

char *new_cmds_in(char *cmd)
{
    int i;
    int j = 0;
    i = 0;
    char *cmd1;
    char *cmd2;
    char *new_cmds;
    if (cmd[0] == '<')
    {
        i++;
        while (ft_iswhitespace_bonus(cmd[i]))
            i++;
        j = i;
        while(!ft_iswhitespace_bonus(cmd[i]))
            i++;
        cmd1 = ft_substr(cmd, j, i - j);
        while (ft_iswhitespace_bonus(cmd[i]))
            i++;
        cmd2 = ft_substr(cmd, i, ft_strlen(cmd) - i);
    }
    else
        return cmd;
    new_cmds = ft_super_strjoin(3, cmd2, " ", cmd1);
    return (new_cmds);
}

char *redirect_input(int redirect, char *buff)
{
    char *buff2;
    char *temp_buff;
    int i = 0;

    if (redirect == 3)
        return (new_cmds_in(buff));
    else if (redirect == 4)
    {
        while (buff[i] != '<')
            i++;
        while(buff[i] == '<')
            i++;
        while(ft_iswhitespace_bonus(buff[i]))
            i++;
        temp_buff = ft_substr(buff, i, ft_strlen(buff) - i);
        buff2 = readline("\rheredoc>");
        while(TRUE)
        {   
            if (ft_strncmp(temp_buff, buff2, ft_strlen(buff2)) == 0)
                break ;
            buff2 = readline("\rheredoc>");
            write(0, buff2, ft_strlen(buff2));
        }
        i = 0;
        while (!ft_iswhitespace_bonus(buff[i]))
            i++;
        return (ft_substr(buff, 0, i));
    }
    return (NULL);
}

/* < file1 cat */