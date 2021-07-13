#include "mini_shell.h"

int which_redirect(char *str)
{
    if (ft_strnstr(str, " >> ", ft_strlen(str)))
        return (2);
    else if(ft_strnstr(str , " > ", ft_strlen(str)))
        return (1);
    else if(ft_strnstr(str, "<<", ft_strlen(str)))
        return (4);
    else if(ft_strnstr(str, "<", ft_strlen(str)))
        return (3);
    return (0);
}

int creat_file(int redirect, char *file_name)
{
    int fd;

    if (redirect == 1)
    {
        fd = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0777);
        return (fd);
    }
    else if (redirect == 2)
    {
        fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0777);
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

void multiple_redirect(int has_redirect, char *cmds_list, t_list **env, char **paths)
{
    char **temp_str;
    t_list *file_list = NULL;
    pid_t pid;
    int fd_red;
    char *new_cmd_list;

    file_list = file_name(cmds_list);
    new_cmd_list = new_cmds(cmds_list);
    temp_str = parse_cmds(new_cmd_list);
    while (file_list != NULL)
    {
        pid = fork();
        if (pid == 0)
        {
            fd_red = creat_file(has_redirect, (char *)file_list->content);
            dup2(fd_red, 1);
            close(fd_red);
            exec_cmd(temp_str, env, paths);
            exit(0);
        }
        close(fd_red);
        file_list = file_list->next;
    }
    while (wait(NULL) > 0);
    free(new_cmd_list);
    free_paths(temp_str);
    deleteList(&file_list);
    exit(0);
}