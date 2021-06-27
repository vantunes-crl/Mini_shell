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

char *file_name(char *cmds)
{
    char *new_str;
    int i;

    i = 0;
    while (cmds[i] != '>' && cmds[i] != '<')
        i++;
    while (cmds[i] == '>' || cmds[i] == '<')
        i++;
    while (ft_iswhitespace_bonus(cmds[i]))
        i++;
    new_str = ft_substr(cmds, i, ft_strlen(cmds) - i);
    return (new_str);
}

// int main(int argc, char **argv)
// {
//     char *str = "ls -l > file1";
//     char *str1;
//     char *str2;

//     str1 = redirect(str);
//     str2 = new_cmds(str);
//     printf("%s\n", str1);
//     printf("%s\n", str2);
    
//     return (0);
// }