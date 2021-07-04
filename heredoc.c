#include "mini_shell.h"

char	*get_delimiter(char *str)
{
	char	**list;
	char	*temp;
	int		i;

	i = 0;
	list = ft_split(str, ' ');
	while (ft_strncmp(*list, "<<", 2))
		list++;
	list++;
	temp = ft_strdup(*list);
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	return (temp);
}

char	*take_off_begin(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '<')
		i++;
	while (ft_iswhitespace_bonus(str[i]))
		i++;
	while (!ft_iswhitespace_bonus(str[i]))
		i++;
	return (ft_substr(str, i, ft_strlen(str) - i));
}

char	*take_off_middle(char *str)
{
	int		i;
	char	*new_str;
	int		j;

	j = 0;
	i = 0;
	new_str = malloc(sizeof(char *) * ft_strlen(str) - 1);
	while (str[i])
	{
		if (str[i] == '<')
			break ;
		else
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	exec_redin(char *cmd, t_list **env, char **paths)
{
	pid_t	pid;
	int		fd[2];
	char	*buff;
	char	**str;
	char	*str2;
	char	*final_buff;
	char	*temp;
	char	*delimiter;
	char	*line;

	final_buff = ft_strdup("");
	delimiter = get_delimiter(cmd);
	if (cmd[0] == '<')
		str2 = take_off_begin(cmd);
	else
		str2 = take_off_middle(cmd);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			buff = readline(">");
			if (ft_strncmp(buff, delimiter, ft_strlen(buff)) == 0)
				break ;
			temp = final_buff;
			final_buff = ft_strjoin(final_buff, buff);
			free(temp);
			line = ft_strdup("\n");
			final_buff = ft_strjoin(final_buff, line);
			free(buff);
			free(line);
		}
		free(delimiter);
		write(fd[1], final_buff, ft_strlen(final_buff));
		free(final_buff);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		wait(NULL);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		str = parse_cmds(str2);
		free(str2);
		exec_cmd(str, env, paths);
		exit(0);
	}
	free_paths(str);
}
