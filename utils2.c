#include "mini_shell.h"

int	cont_list(char **list)
{
	int	i;

	i = 0;
	while (list[i++])
		;
	return (i);
}

char	*first_heredoc(char *str, char **cmds, int i)
{
	char	*temp_str;

	temp_str = str;
	str = ft_strjoin(str, child_readin(cmds[i]));
	free(temp_str);
	return (str);
}

char	*heredoc_input(char **cmds)
{
	char	*str;
	char	*temp_str;
	t_vars	vars;

	vars.i = -1;
	vars.count = 0;
	vars.flag = 0;
	while (cmds[++vars.i])
	{
		if (which_redirect(cmds[vars.i]) == 4)
		{
			if (vars.flag == 1)
				str = first_heredoc(str, cmds, vars.i);
			else
			{
				str = child_readin(cmds[vars.i]);
				vars.flag = 1;
			}
		}
		else
			vars.count++;
	}
	if (vars.count == vars.i)
		return (NULL);
	return (str);
}

void	take_off(char **cmds_list, int i)
{
	char	*temp_str;

	temp_str = cmds_list[i];
	if (cmds_list[i][0] == '<')
		cmds_list[i] = take_off_begin(cmds_list[i]);
	else
		cmds_list[i] = take_off_middle(cmds_list[i]);
	free(temp_str);
}

void	red_in_simple(char **cmds_list, int i)
{
	char	*fn;
	char	*new_cmd;
	int		fd_in;

	fn = find_filename(cmds_list[i]);
	new_cmd = cmds_list[i];
	cmds_list[i] = new_cmd_in(cmds_list[i]);
	free(new_cmd);
	fd_in = open(fn, O_RDWR, 0777);
	if (fd_in < 0)
		error("minishell");
}
