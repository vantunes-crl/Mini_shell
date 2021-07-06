#include "mini_shell.h"

void	deleteList(t_list **env)
{
	t_list	*current;
	t_list	*next;

	current = *env;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*env = NULL;
}

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
