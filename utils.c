#include "mini_shell.h"

char	**find_path(char **cmds, t_list *env)
{
	char	**paths;

	while (env)
	{
		if (ft_strncmp((char *)env->content, "PATH", 4) == 0)
			break ;
		env = env->next;
	}
	if (!env)
		error(cmds[0]);
	else
		paths = ft_split((char *)env->content, ':');
	return (paths);
}

void	error(char *str)
{
	perror(str);
}

void	double_free(char *elem1, char *elem2)
{
	free(elem1);
	free(elem2);
}

char	*get_delimiter(char *str)
{
	char	**list;
	char	*temp;
	int		i;

	i = 0;
	list = ft_split(str, ' ');
	while (ft_strncmp(*list, "<<", 2))
		list++;
	list++;
	temp = ft_strdup(*list);
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	return (temp);
}
