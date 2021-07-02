#include "mini_shell.h"

char *find_filename(char *cmd)
{
    char **cmd_list;

    cmd_list = ft_split(cmd, ' ');
    if (cmd[0] == '<')
        return(cmd_list[1]);
    else
    {
        while (*(cmd_list + 1))
            cmd_list++;
        return(*cmd_list);
    }
}

char *new_cmd_in(char *cmd)
{
    char **cmd_list;
    char *new_str;

    new_str = ft_strdup("");
    cmd_list = ft_split(cmd, ' ');
    if (cmd[0] == '<')
    {
        cmd_list++;
        cmd_list++;
        while (*cmd_list)
        {
            new_str = ft_super_strjoin(3, new_str, " ", *cmd_list);
            cmd_list++;
        }
        return (new_str);
    }
    else
    {
        while (*cmd_list)
        {
            if (ft_strncmp("<", *cmd_list, 1) == 0)
                break;
            new_str = ft_super_strjoin(3, new_str, " ", *cmd_list);
            cmd_list++;
        }
        return (new_str);
    }
    return (NULL);
}

void simple_redirec_in(char *cmd, t_list **env)
{
    pid_t pid;
    int fd[2];
    int fd_in;
    char *fn;
    char *new_cmd;
    char **temp_cmd;

    pipe(fd);
    fn = find_filename(cmd);
    new_cmd = new_cmd_in(cmd);
    pid = fork();
    if (pid == 0)
    {
        fd_in = open(fn, O_RDWR, 0777);
        if (fd_in < 0)
        {
            perror("minishell");
            exit(0);
        }
        dup2(fd_in, 0);
        close(fd[0]);
        close(fd[1]);
        temp_cmd = parse_cmds(new_cmd);
        exec_cmd(temp_cmd, env);
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