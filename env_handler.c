#include "mini_shell.h"

/* function make a copy on the first envirement variavables on the sistem */
t_list *init_env(char **env)
{
    t_list *elem;
    char **envp;

    elem = NULL;
    envp = env;
    while (*envp != NULL) /* cpy all env from the sistem to a linked list */
        ft_lstadd_back(&elem,ft_lstnew(*envp++));
    return (elem);
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

void deleteList(t_list **env)
{
    t_list *current = *env;
    t_list *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *env = NULL;
}