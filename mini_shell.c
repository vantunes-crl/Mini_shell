#include "mini_shell.h"

t_list	*init_env(char **env)
{
	t_list	*elem;
	char	**envp;

	elem = NULL;
	envp = env;
	while (*envp != NULL)
		ft_lstadd_back(&elem, ft_lstnew(*envp++));
	return (elem);
}

void	ft_cd(char **temp_dir, char **temp_cmds)
{
	temp_dir = ft_split(temp_cmds[0], ' ');
	chdir(temp_dir[1]);
	free_paths(temp_dir);
	free_paths(temp_cmds);
}

void	ft_unset(char **temp_dir, t_list *envp, char **temp_cmds)
{
	temp_dir = ft_split(temp_cmds[0], ' ');
	del_elem_lst(&envp, temp_dir[1]);
	free_paths(temp_dir);
	free_paths(temp_cmds);
}

void	main_loop(char **temp_cmds, t_list *envp)
{
	char	**temp_dir;
	char	**paths;

	if (ft_strncmp(temp_cmds[0], "cd", 2) == 0)
		ft_cd(temp_dir, temp_cmds);
	else if (ft_strncmp(temp_cmds[0], "unset", 5) == 0)
		ft_unset(temp_dir, envp, temp_cmds);
	else if (ft_strncmp(temp_cmds[0], "export", 6) == 0)
	{
		temp_dir = ft_split(temp_cmds[0], ' ');
		ft_lstadd_back(&envp, ft_lstnew(temp_dir[1]));
		free_paths(temp_cmds);
	}
	else
	{
		has_exit(temp_cmds, &envp);
		paths = find_path(temp_cmds, envp);
		main_process(temp_cmds, &envp, paths);
		free_paths(temp_cmds);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	inputString[200];
	char	**temp_cmds;
	t_list	*envp;

	exit_status = 0;
	envp = init_env(env);
	signal(SIGINT, kill_handler);
	while (TRUE)
	{
		if (take_line(inputString))
			continue ;
		else
		{
			temp_cmds = cmds_list(inputString);
			main_loop(temp_cmds, envp);
		}
	}
	return (0);
}
