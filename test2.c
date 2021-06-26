#include "mini_shell.h"

int which_redirect(char *str)
{
    if (ft_strncmp(">", str, 1) == 0)
        return (1);
    else if(ft_strncmp(">>", str, 2) == 0)
        return (2);
    else if(ft_strncmp("<", str, 1) == 0)
        return (3);
    else if(ft_strncmp("<<", str, 2) == 0)
        return (4);
    return (0);
}

char **remake_cmd(char **cmd)
{
    int ret;
    char *new_str;

    while (*cmd != NULL)
    {   
        if (which_redirect(*(cmd + 1)))
            break;
        new_str = ft_super_strjoin(3, *cmd, " ", *(cmd + 1));
        cmd++;
    }
    return (ft_split(new_str, ' '));
}


int creat_file(int redirect, char *file_name)
{
    int fd;

    if (redirect == 1)
    {
        fd = open(file_name, O_WRONLY | O_CREAT, 0777);
        return (fd);
    }
    return (0);
}

int redirect(char ***cmds)
{
    char **new_cmds;
    int has_redirect;
    int fd;

    has_redirect = 0;
    new_cmds = *cmds;
    while (*new_cmds != NULL)
    {
        has_redirect = which_redirect(*new_cmds);
        if (has_redirect)
        {
            fd = creat_file(has_redirect, *(new_cmds + 1));
            return (fd);
        }
        new_cmds++;
    }
    return 0;
}

int main(int argc, char **argv)
{
    char str[] = "ls -l > file1";
    char **cmds;

    cmds = ft_split(str, ' ');
    redirect(&cmds);
    remake_cmd(cmds);

    return (0);
}