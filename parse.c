#include "mini_shell.h"

char	**parse_cmds(char *str)
{
	char	**cmds;
	char	*temp_str;

	temp_str = ft_strtrim(str, WHITE_SPACE);
	cmds = ft_split(temp_str, ' ');
	free(temp_str);
	return (cmds);
}

int	has_pipes(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
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
