#include "mini_shell.h"

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
				take_off(cmds_list, i);
			else if (has_redirect == 3)
				red_in_simple(cmds_list, i);
			dup2(fdd, 1);
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
			temp_str = parse_cmds(cmds_list[i], env);
			exec_cmd(temp_str, env, paths);
			free_paths(temp_str);
			error("minishell");
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
	while (wait(&temp_exit) > 0);
	if (WIFEXITED(temp_exit))
		exit_status = WEXITSTATUS(temp_exit);
}
