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
	char *temp_str;

	while (*cmds_list)
	{
		temp_str = ft_strtrim(*cmds_list, " ");
		if (ft_strncmp(temp_str, "exit", 4) == 0)
		{
			deleteList(env);
			free(temp_str);
			exit(0);
		}
		free(temp_str);
		cmds_list++;
	}
}
