#include "mini_shell.h"

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

int is_abspath(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

char **find_path(char **cmds, t_list *env)
{
    char **paths;

    while (env)
    {
        if (ft_strncmp((char *)env->content, "PATH", 4) == 0)
            break ;
        env = env->next;
    }
    if (!env && !is_abspath(*cmds) && env)
       error(cmds[0]);
    if (env)
        paths = ft_split((char *)env->content, ':');
    return (paths);
}

void error(char *str)
{
    perror(str);
}

char **list_to_matriz(t_list *env)
{
    char **matriz;
    int i;

    i = 0;
    matriz = malloc(sizeof(char *) * ft_lstsize(env) + 1);
    while (env)
    {
        matriz[i] = ft_strdup((char *)env->content);
        env = env->next;
        i++;
    }
    return (matriz);
}