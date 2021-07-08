#include "mini_shell.h"

/* function receive a list of commands and exec one by one in the pipe */
void multiple_pipes(char **cmds_list, t_list **env, char **paths)
{
    pid_t pid;
    int fd[2];
    int fd_in = 0;
    int has_redirect = 0;
    char **temp_str;

    int temp_exit;
    while (*cmds_list != NULL)
    {
        if (pipe(fd) < 0)
            error("pipe");
        pid = fork();
        if (pid < 0)
            error("fork");
        if (pid == 0) 
        {
            dup2(fd_in, 0);
            has_redirect = which_redirect(*cmds_list);
            if (has_redirect == 1 || has_redirect == 2)
                multiple_redirect(has_redirect, *cmds_list, env, paths);
            else if (has_redirect == 4)
            {
                close(fd[1]);
                close(fd[0]);
                exec_redin(*cmds_list, env, paths);
            }
            else if (has_redirect == 3)
            {
                close(fd[1]);
                close(fd[0]);
                simple_redirec_in(*cmds_list, env, paths);
            }
            else if (*(cmds_list + 1) != NULL)
                dup2(fd[1], 1);
            close(fd[0]);
            temp_str = parse_cmds(*cmds_list);
            exec_cmd(temp_str, env, paths);
            free_paths(temp_str);
            exit(0);
        }
        else
        {
            wait(&temp_exit);
            if (temp_exit)
                exit_status = temp_exit;
            close(fd[1]);
            fd_in = fd[0];
            cmds_list++;
        }
    }  
}