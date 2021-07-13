#include "mini_shell.h"

int cont_list(char **list)
{
	int i = 0;
	while(list[i++]);
	return (i);
}

char *heredoc_input(char **cmds)
{
	int i;
	char *str;
	char *temp_str;
	int count = 0;
	int flag = 0;
	i = 0;

	while (cmds[i])
	{
		if (which_redirect(cmds[i]) == 4)
		{
			if (flag == 1)
			{
				temp_str = str;
				str = ft_strjoin(str, child_readin(cmds[i]));
				free(temp_str);
			}
			else
			{
				str = child_readin(cmds[i]);
				flag == 1;
			}
		}
		else
			count++;
		i++;
	}
	if (count == i)
		return (NULL);
	return(str);
}

void	main_process(char **cmds_list, t_list **env, char **paths)
{
	pid_t	pid;
	int		fd[2];
	int		fdd = 1;
	int		has_redirect;
	char	**temp_str;
	int		temp_exit;
	char	*str;
	int i = 0;
	int heredoc = 0;

	str = heredoc_input(cmds_list);
	i = cont_list(cmds_list) - 1;
	has_redirect = 0;
	while (i-- > 0)
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
                printf("CHEGOU\n");

				char *temp_str;
				temp_str = cmds_list[i];
				if (cmds_list[i][0] == '<')
        			cmds_list[i] = take_off_begin(cmds_list[i]);
    			else
        			cmds_list[i] = take_off_middle(cmds_list[i]);
				free(temp_str);
			}
			else if (has_redirect == 3)
			{
                char *fn = find_filename(cmds_list[i]);
				char *new_cmd = cmds_list[i];
                cmds_list[i] = new_cmd_in(cmds_list[i]);
				free(new_cmd);
                int fd_in = open(fn, O_RDWR, 0777);
                if (fd_in < 0)
                {
                    perror("minishell");
                    exit(0);
                }
			}
			dup2(fdd, 1);   // child's output
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
			temp_str = parse_cmds(cmds_list[i], env);
			exec_cmd(temp_str, env, paths);
			free_paths(temp_str);
			perror("error");
			exit(1);
		}
		if (fdd != 1) 
			close(fdd);   // close if a pipe write end
		fdd = fd[1];    // preceding child's output is pipe write end
		close(fd[0]);
	}
	if (str)
	{
		write(fd[1], str, ft_strlen(str));
		close(fd[1]);   // signal EOF to child
	}
	while (wait(&temp_exit) > 0) ; 
	if (WIFEXITED(temp_exit))
		exit_status = WEXITSTATUS(temp_exit);
}
