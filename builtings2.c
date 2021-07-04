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
