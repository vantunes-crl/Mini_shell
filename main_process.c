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
                char *buff;
                char **str;
                char *str2;
                char *final_buff;
                char *temp;
                char *delimiter;
                char *line;

                final_buff = ft_strdup("");
                delimiter = get_delimiter(*cmds_list);
                if (*cmds_list[0] == '<')
                    str2 = take_off_begin(*cmds_list);
                else
                    str2 = take_off_middle(*cmds_list);
                while(1)
                {
                    buff = readline(">");
                    if (ft_strncmp(buff, delimiter, ft_strlen(buff)) == 0)
                        break;
                    temp = final_buff;
                    final_buff = ft_strjoin(final_buff, buff);
                    free(temp);
                    line = ft_strdup("\n");
                    final_buff = ft_strjoin(final_buff, line);
                    free(buff);
                    free(line);
                }
                free(delimiter);
                write(fd_in, final_buff, ft_strlen(final_buff));
                free(final_buff);

            }
            else if (has_redirect == 3)
            {
                if (*(cmds_list + 1) != NULL)
                    dup2(fd[1], 1);
                char *fn = find_filename(*cmds_list);
                char *new_cmd = new_cmd_in(*cmds_list);
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