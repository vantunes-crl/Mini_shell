#include "mini_shell.h"

void	print_dir(void)
{
	char	str[1040];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
	exit(0);
}

void	print_env(t_list *envp)
{
	while (envp != NULL)
	{
		printf("%s\n", (char *)envp->content);
		envp = envp->next;
	}
	exit(0);
}

void	has_exit(char **cmds_list, t_list **env)
{
	char	*temp_str;

	while (*cmds_list)
	{
		temp_str = ft_strtrim(*cmds_list, " ");
		if (ft_strncmp(temp_str, "exit", 4) == 0)
		{
			ft_deletelist(env);
			free(temp_str);
			exit(0);
		}
		free(temp_str);
		cmds_list++;
	}
}

void	ft_unset(t_list *envp, char **temp_cmds)
{
	char	**temp_dir;

	temp_dir = ft_split(temp_cmds[0], ' ');
	del_elem_lst(&envp, temp_dir[1]);
	free_paths(temp_dir);
	free_paths(temp_cmds);
}

void	ft_export(t_list *envp, char **temp_cmds)
{
	char	**temp_dir;

	temp_dir = ft_split(temp_cmds[0], ' ');
	ft_lstadd_back(&envp, ft_lstnew(temp_dir[1]));
	free_paths(temp_cmds);
}
