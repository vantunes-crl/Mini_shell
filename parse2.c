#include "mini_shell.h"

char	**parse_cmds(char *str, t_list **env)
{
	char	**cmds;
	char	*temp_str;
	int		i;

	temp_str = ft_strtrim(str, WHITE_SPACE);
	i = 0;
	while (temp_str[i])
	{
		if (temp_str[i] == '$')
			temp_str = take_care_of_env(temp_str, *env);
		i++;
	}
	if (check_quotes(str) == 1)
		cmds = parse_quotes(temp_str);
	else
		cmds = ft_split(temp_str, ' ');
	free(temp_str);
	return (cmds);
}

char	**cmds_list(char *str)
{
	char	**cmds_lst;
	char	*temp_str;

	temp_str = ft_strjoin(str, " |");
	cmds_lst = ft_split(temp_str, '|');
	free(temp_str);
	return (cmds_lst);
}
