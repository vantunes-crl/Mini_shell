#include "mini_shell.h"

void	heredoc_redin(char *cmds_list, t_list **env,
	char **paths, int has_redirect)
{
	if (has_redirect == 3)
		simple_redirec_in(cmds_list, env, paths);
	else
		exec_redin(cmds_list, env, paths);
}

void	main_process_child(t_process *process,
	char **cmds_list, t_list **env, char **paths)
{
	process->has_redirect = which_redirect(cmds_list[process->i]);
	if (process->has_redirect == 1 || process->has_redirect == 2)
		multiple_redirect(process->has_redirect, *cmds_list, env, paths);
	else if (process->has_redirect == 4 || process->has_redirect == 3)
		heredoc_redin(cmds_list[process->i], env, paths, process->has_redirect);
	else if (cmds_list[process->i + 1] != NULL)
		dup2(process->fd[1], 1);
	dup2(process->fd_in, 0);
	close(process->fd[0]);
	process->temp_str = parse_cmds(cmds_list[process->i]);
	exec_cmd(process->temp_str, env, paths);
	free_paths(process->temp_str);
	exit(0);
}

void	main_process(char **cmds_list, t_list **env, char **paths)
{
	t_process	process;

	process.i = 0;
	while (cmds_list[process.i])
	{
		if (pipe(process.fd) < 0)
			error("pipe");
		process.pid = fork();
		if (process.pid < 0)
			error("fork");
		if (process.pid == 0)
			main_process_child(&process, cmds_list, env, paths);
		else
		{
			wait(&process.temp_exit);
			if (process.temp_exit)
				g_exit_status = process.temp_exit;
			close(process.fd[1]);
			process.fd_in = process.fd[0];
			process.i++;
		}
	}
}
