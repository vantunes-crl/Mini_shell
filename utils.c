#include "mini_shell.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
}

int	is_abspath(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	**find_path(char **cmds, t_list *env)
{
	char	**paths;

	while (env)
	{
		if (ft_strncmp((char *)env->content, "PATH", 4) == 0)
			break ;
		env = env->next;
	}
	if (env)
		paths = ft_split((char *)env->content, ':');
	else
		paths = NULL;
	return (paths);
}

void	error(char *str)
{
	perror(str);
	exit(127);
}

char	**list_to_matriz(t_list *env)
{
	char	**matriz;
	int		i;

	i = 0;
	matriz = malloc(sizeof(char *) * ft_lstsize(env) + 1);
	while (env)
	{
		matriz[i] = ft_strdup((char *)env->content);
		env = env->next;
		i++;
	}
	matriz[i] = 0;
	return (matriz);
}
