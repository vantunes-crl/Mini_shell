#include "mini_shell.h"

void	child_main_process(char **cmds_list, t_fds *fds,
	t_list **env, char **paths)
{
	int		has_redirect;
	char	**temp_str;

	has_redirect = 0;
	has_redirect = which_redirect(cmds_list[fds->i]);
	if (has_redirect == 1 || has_redirect == 2)
		multiple_redirect(has_redirect, cmds_list[fds->i], env, paths);
	else if (has_redirect == 4)
		take_off(cmds_list, fds->i);
	else if (has_redirect == 3)
		red_in_simple(cmds_list, fds->i);
	dup2(fds->fdd, 1);
	dup2(fds->fd[0], 0);
	close(fds->fd[0]);
	close(fds->fd[1]);
	temp_str = parse_cmds(cmds_list[fds->i], env);
	exec_cmd(temp_str, env, paths);
	free_paths(temp_str);
	error("minishell");
}

void	main_process(char **cmds_list, t_list **env, char **paths)
{
	t_fds	fds;

	fds.fdd = 1;
	fds.heredoc_buff = heredoc_input(cmds_list);
	fds.i = cont_list(cmds_list) - 1;
	while (fds.i-- > 0)
	{
		if (pipe(fds.fd) < 0)
			error("pipe");
		fds.pid = fork();
		if (fds.pid < 0)
			error("fork");
		if (fds.pid == 0)
			child_main_process(cmds_list, &fds, env, paths);
		if (fds.fdd != 1)
			close(fds.fdd);
		fds.fdd = fds.fd[1];
		close(fds.fd[0]);
	}
	if (fds.heredoc_buff)
		write_heredoc(fds.heredoc_buff, fds.fd[1]);
	while (wait(&fds.temp_exit) > 0)
		;
	if (WIFEXITED(fds.temp_exit))
		g_exit_status = WEXITSTATUS(fds.temp_exit);
}
