#include "mini_shell.h"

static	void	handler_part(char *content, int flag, int n)
{
	char	*var_env;
	char	*temp;
	int		i;

	var_env = ft_strdup(content);
	temp = var_env;
	i = 0;
	while (temp[i] != '=')
		i++;
	var_env = ft_substr(temp, i + 1, ft_strlen(temp));
	free(temp);
	if (flag == 1)
		printf("minishell: command not found: ");
	printf("%s", var_env);
	if (n == 1)
		printf("\n");
	free(var_env);
}

void	handle_var_env(char *var_env, t_list *env, int flag, int n)
{
	while (env)
	{
		if (ft_strncmp((char *)env->content, var_env, 4) == 0)
			break ;
		env = env->next;
	}
	if (!env)
	{
		if (flag == 0)
			printf("\n");
		free(var_env);
		return ;
	}
	free(var_env);
	handler_part((char *)env->content, flag, n);
}

void	is_sifrao(char *cmds, t_list **env, int n)
{
	char	*var_env;
	char	*temp;

	var_env = ft_strdup(cmds);
	temp = var_env;
	var_env = ft_strtrim(temp, "$");
	free(temp);
	if (n)
		handle_var_env(var_env, *env, 0, 0);
	else
		handle_var_env(var_env, *env, 0, 1);
}

void	ft_echo(char ***cmds, int n)
{
	while (**cmds)
	{
		write(1, **cmds, ft_strlen(**cmds));
		if (**(cmds + 1) != NULL)
			write(1, " ", 1);
		(*cmds)++;
	}
	if (!n)
		write(1, "\n", 1);
}

void	print_echo(t_list **env, char **cmds)
{
	int	n;

	n = 0;
	if (!cmds[1])
	{
		printf("\n");
		return ;
	}
	cmds++;
	if (ft_strncmp(*cmds, "-n", 2) == 0)
	{
		n = 1;
		cmds++;
	}
	if (ft_strncmp(*cmds, "$", 1) == 0)
	{
		is_sifrao(*cmds, env, n);
		return ;
	}
	else
		ft_echo(&cmds, n);
}
