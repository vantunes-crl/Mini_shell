#include "mini_shell.h"

int	creat_file(int redirect, char *file_name)
{
	int	fd;

	if (redirect == 1)
	{
		fd = open(file_name, O_TRUNC | O_WRONLY | O_CREAT, 0777);
		return (fd);
	}
	else if (redirect == 2)
	{
		fd = open(file_name, O_APPEND | O_WRONLY | O_CREAT, 0777);
		return (fd);
	}
	return (0);
}

char	*new_cmds(char *cmds)
{
	char	*new_cmds;
	int		i;

	i = 0;
	while (cmds[i] != '>' && cmds[i] != '<')
		i++;
	new_cmds = ft_substr(cmds, 0, i);
	return (new_cmds);
}

t_list	*file_name(char *cmds)
{
	t_list	*new_str;
	int		i;
	int		j;

	new_str = NULL;
	i = 0;
	while (cmds[i])
	{
		while (cmds[i] != '>' && cmds[i] != '<')
			i++;
		while (cmds[i] == '>' || cmds[i] == '<')
			i++;
		while (ft_iswhitespace_bonus(cmds[i]))
			i++;
		j = i;
		while (!ft_iswhitespace_bonus(cmds[i]))
			i++;
		ft_lstadd_back(&new_str, ft_lstnew(ft_substr(cmds, j, i - j)));
		i++;
	}
	return (new_str);
}

static	void	freesss(t_vars *vars, t_list *file_list)
{
	free(vars->new_cmd_list);
	free_paths(vars->temp_str);
	ft_deletelist(&file_list);
	exit(0);
}

void	multiple_redirect(int has_redirect, char *cmds_list,
	t_list **env, char **paths)
{
	t_list	*file_list;
	t_vars	vars;

	ft_bzero(&vars, sizeof(vars));
	file_list = NULL;
	file_list = file_name(cmds_list);
	vars.new_cmd_list = new_cmds(cmds_list);
	vars.temp_str = parse_cmds(vars.new_cmd_list, env);
	while (file_list != NULL)
	{
		vars.pid = fork();
		if (vars.pid == 0)
		{
			vars.fd_red = creat_file(has_redirect, (char *)file_list->content);
			dup2(vars.fd_red, 1);
			close(vars.fd_red);
			exec_cmd(vars.temp_str, env, paths);
			exit(0);
		}
		close(vars.fd_red);
		wait(NULL);
		file_list = file_list->next;
	}
	freesss(&vars, file_list);
}
