#include "mini_shell.h"

char *find_filename(char *cmd)
{
    char **cmd_list;
    char *temp;
    int i;

    i = 0;
    cmd_list = ft_split(cmd, ' ');
    if (cmd[0] == '<')
    {
        temp = ft_strdup(cmd_list[1]);
        free_paths(cmd_list);
        return(temp);
    }
    else
    {
        while (*(cmd_list + 1))
            cmd_list++;
        while (cmd_list[i] != NULL)
            free(cmd_list[i++]);
        temp = ft_strdup(*cmd_list);
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
    if (cmd[0] == '<')
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

void simple_redirec_in(char *cmd, t_list **env, char **paths)
{
    pid_t pid;
    int fd[2];
    int fd_in;
    char *fn;
    char *new_cmd;
    char **temp_cmd;

    if (pipe(fd) < 0)
        perror("pipe");
    fn = find_filename(cmd);
    new_cmd = new_cmd_in(cmd);
    pid = fork();
    if (pid < 0)
        perror("fork");
    if (pid == 0)
    {
        fd_in = open(fn, O_RDWR, 0777);
        free(fn);
        if (fd_in < 0)
        {
            perror("minishell");
            exit(0);
        }
        dup2(fd_in, 0);
        close(fd[0]);
        close(fd[1]);
        temp_cmd = parse_cmds(new_cmd);
        free(new_cmd);
        exec_cmd(temp_cmd, env, paths);
        exit(0);
    }
    else
    {
        wait(NULL);
        close(fd[0]);
        close(fd[1]);
    }
    exit(0);
}