#include "mini_shell.h"

char	*find_filename(char *cmd)
{
	char	**cmd_list;
	char	*temp;
	int		i;

	i = 0;
	cmd_list = ft_split(cmd, ' ');
	if (cmd[0] == '<')
	{
		temp = ft_strdup(cmd_list[1]);
		free_paths(cmd_list);
		return (temp);
	}
	else
	{
		while (*(cmd_list + 1))
			cmd_list++;
		while (cmd_list[i] != NULL)
			free(cmd_list[i++]);
		temp = ft_strdup(*cmd_list);
		return (temp);
	}
}

static	char	*new_cmd_in_2(int i, char **cmd_list, char *temp, char *new_str)
{
	i = i + 2;
	while (cmd_list[i])
	{
		temp = new_str;
		new_str = ft_super_strjoin(3, new_str, " ", cmd_list[i]);
		free(temp);
		i++;
	}
	i = 0;
	while (cmd_list[i] != NULL)
		free(cmd_list[i++]);
	return (new_str);
}

char	*new_cmd_in(char *cmd)
{
	char	**cmd_list;
	char	*new_str;
	char	*temp;
	int		i;

	i = 0;
	new_str = ft_strdup("");
	cmd_list = ft_split(cmd, ' ');
	if (cmd[0] == '<')
		return (new_cmd_in_2(i, cmd_list, temp, new_str));
	else
	{
		while (cmd_list[i])
		{
			if (ft_strncmp("<", cmd_list[i], 1) == 0)
				break ;
			temp = new_str;
			new_str = ft_super_strjoin(3, new_str, " ", cmd_list[i]);
			free(temp);
			i++;
		}
		free_paths(cmd_list);
		return (new_str);
	}
	return (NULL);
}

static	void	child_process(t_process *process,
	char *new_cmd, t_list **env, char **paths)
{
	char	**temp_cmd;

	process->fd_in = open(process->fn, O_RDWR, 0777);
	free(process->fn);
	if (process->fd_in < 0)
	{
		perror("minishell");
		exit(0);
	}
	dup2(process->fd_in, 0);
	close(process->fd[0]);
	close(process->fd[1]);
	temp_cmd = parse_cmds(new_cmd);
	free(new_cmd);
	exec_cmd(temp_cmd, env, paths);
	exit(0);
}

void	simple_redirec_in(char *cmd, t_list **env, char **paths)
{
	char		*new_cmd;
	t_process	process;

	if (pipe(process.fd) < 0)
		perror("pipe");
	process.fn = find_filename(cmd);
	new_cmd = new_cmd_in(cmd);
	process.pid = fork();
	if (process.pid < 0)
		perror("fork");
	if (process.pid == 0)
		child_process(&process, new_cmd, env, paths);
	else
	{
		wait(NULL);
		close(process.fd[0]);
		close(process.fd[1]);
	}
	exit(0);
}
