#include "mini_shell.h"

int cont_list(char **cmds_list)
{
    int i;

    i = 0;
    while (cmds_list[i])
        i++;
    return (i);
}
/* function receive a list of commands and exec one by one in the pipe */
void multiple_pipes(char **cmds_list, t_list **env, char **paths)
{
    pid_t pid;
    int fd[2];
    int fd_in = 0;
    int has_redirect = 0;
    char **temp_str;
    int i = 0;

    int temp_exit;
    while (cmds_list[i] != NULL)
    {
        if (pipe(fd) < 0)
            error("pipe");
        pid = fork();
        if (pid < 0)
            error("fork");
        if (pid == 0) 
        {
            has_redirect = which_redirect(cmds_list[i]);
            if (has_redirect == 1 || has_redirect == 2)
                multiple_redirect(has_redirect, cmds_list[i], env, paths);
            else if (has_redirect == 4)
            {
                int fd_new;
                if (cont_list(cmds_list) > 1)
                    fd_new = fd[1];
                else
                    fd_new = 1;
                char *temp;
                temp = cmds_list[i];
                cmds_list[i] = exec_redin(cmds_list[i], env, paths, fd_new);
                free(temp);
                i--;
                close(fd[0]);
                close(fd[1]);
                exit(0);
            }
            else if (has_redirect == 3)
            {
                if (cmds_list[i + 1] != NULL)
                    dup2(fd[1], 1);
                char *fn = find_filename(cmds_list[i]);
                char *new_cmd = new_cmd_in(cmds_list[i]);
                fd_in = open(fn, O_RDWR, 0777);
                if (fd_in < 0)
                {
                    perror("minishell");
                    exit(0);
                }
                char **temp_cmd = parse_cmds(new_cmd);
                free(new_cmd);
                close(fd[1]);
                close(fd[0]);
                exec_cmd(temp_cmd, env, paths);
                exit(0);
            }
            else if (cmds_list[i + 1] != NULL)
                dup2(fd[1], 1);
            dup2(fd_in, 0);
            close(fd[0]);
            close(fd[1]);
            temp_str = parse_cmds(cmds_list[i]);
            exec_cmd(temp_str, env, paths);
            free_paths(temp_str);
            exit(0);
        }
        else
        {
            if (WIFEXITED(temp_exit))
                exit_status = WEXITSTATUS(temp_exit);
            close(fd[1]);
            fd_in = fd[0];
            wait(&temp_exit);
            i++;
        }
    }  

}