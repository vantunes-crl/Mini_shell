#include "mini_shell.h"

char	*find_filename(char *cmd)
{
	char	**cmd_list;
	char	*temp;
	int		i;

	i = 0;
	cmd_list = ft_split(cmd, ' ');
	if (ft_strncmp(cmd_list[0], "<", 1) == 0)
	{
		temp = ft_strdup(cmd_list[1]);
		free_paths(cmd_list);
		return (temp);
	}
	else
	{
		while (*(cmd_list + 1))
			cmd_list++;
		temp = ft_strdup(*cmd_list);
		while (cmd_list[i] != NULL)
			free(cmd_list[i++]);
		return (temp);
	}
}

static char	*begin_red(char **cmd_list, char *new_str)
{
	int		i;
	char	*temp;

	i = 2;
	while (cmd_list[i])
	{
		temp = new_str;
		new_str = ft_super_strjoin(3, new_str, " ", cmd_list[i]);
		free(temp);
		i++;
	}
	free_paths(cmd_list);
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
	if (ft_strncmp(cmd_list[0], "<", 1) == 0)
		return (begin_red(cmd_list, new_str));
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
