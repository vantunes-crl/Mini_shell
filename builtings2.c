#include "mini_shell.h"

void	print_dir(void)
{
	char	str[1040];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
}

void	print_env(t_list *envp)
{
	while (envp != NULL)
	{
		printf("%s\n", (char *)envp->content);
		envp = envp->next;
	}
}

void	has_exit(char **cmds_list, t_list **env)
{
	while (*cmds_list)
	{
		if (ft_strncmp(*cmds_list, "exit", 4) == 0)
		{
			deleteList(env);
			free_paths(cmds_list);
			exit(0);
		}
		cmds_list++;
	}
}
