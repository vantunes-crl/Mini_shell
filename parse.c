#include "mini_shell.h"

static char	*env_to_print(char *content, int i, int end, char *str)
{
	char	*temp_var;
	int		x;
	char	*def_var;
	char	*new;
	char	*temp;

	x = 0;
	while (content[x] != '=')
		x++;
	x++;
	temp_var = ft_strdup(content);
	def_var = ft_substr(temp_var, x, ft_strlen(temp_var) - x);
	free(temp_var);
	new = ft_substr(str, 0, i - 1);
	temp = ft_strjoin(new, def_var);
	free(new);
	new = ft_strjoin(temp, ft_substr(str, end, ft_strlen(str) - end));
	return (new);
}

char	*no_env(char *str, int i, int end)
{
	char	*new;
	char	*temp;

	new = ft_substr(str, 0, i - 2);
	temp = ft_strjoin(new, ft_substr(str, end, ft_strlen(str) - end));
	free(new);
	return (temp);
}

static	char	*is_env(int i, char *str, int end, t_list *env)
{
	char	*var;

	i++;
	if (str[i] == '?')
		return (str);
	end = i;
	while (str[end] >= 'A' && str[end] <= 'Z')
		end++;
	var = ft_substr(str, i, end - i);
	while (env)
	{
		if (ft_strncmp((char *)env->content, var, ft_strlen(var)) == 0)
			break ;
		env = env->next;
	}
	if (!env)
		return (no_env(str, i, end));
	else
		return (env_to_print((char *)env->content, i, end, str));
}

char	*take_care_of_env(char *str, t_list *env)
{
	int		i;
	int		quote;
	int		end;
	char	*temp_str;

	i = 0;
	quote = 0;
	end = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote++;
		if (str[i] == '$')
			break ;
		i++;
	}
	if (str[i] == '$' && quote == 0)
		return (temp_str = is_env(i, str, end, env));
	else
		return (str);
	return (NULL);
}
