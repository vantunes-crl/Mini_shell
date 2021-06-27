#include "mini_shell.h"

int which_redirect(char *str)
{
    if (ft_strnstr(str, " > ", ft_strlen(str)))
        return (1);
    else if(ft_strnstr(str , " >> ", ft_strlen(str)))
        return (2);
    else if(ft_strnstr(str, " < ", ft_strlen(str)))
        return (3);
    else if(ft_strnstr(str, " << ", ft_strlen(str)))
        return (4);
    return (0);
}

int creat_file(int redirect, char *file_name)
{
    int fd;

    if (redirect == 1)
    {
        fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
        return (fd);
    }
    return (0);
}

char *new_cmds(char *cmds)
{
    char *new_cmds;
    int i;

    i = 0;
    while (cmds[i] != '>' && cmds[i] != '<')
        i++;
    new_cmds = ft_substr(cmds, 0, i);
    return (new_cmds);
}

t_list *file_name(char *cmds)
{
    t_list *new_str;
    new_str = NULL;
    int i;
    int j;

    i = 0;
    while (cmds[i])
    {
        while (cmds[i] != '>' && cmds[i] != '<')
            i++;
        while (cmds[i] == '>' || cmds[i] == '<')
            i++;
        while (ft_iswhitespace_bonus(cmds[i]))
            i++;
        j = i;
        while (!ft_iswhitespace_bonus(cmds[i]))
            i++;
        ft_lstadd_back(&new_str, ft_lstnew(ft_substr(cmds, j, i - j)));
        i++;
    }
    return (new_str);
}

int main(int argc, char **argv)
{
    char *str = "ls -l > file1 > file2 > file5";
    char *str1;
    char *str2;
    int fd;

    t_list *elem;

    elem = file_name(str);
    while (elem != NULL)
    {
        fd = creat_file(1, (char *)elem->content);
        elem = elem->next;
        close(fd);
    }
    return (0);
}