#include "mini_shell.h"
#include <dirent.h>
#include <string.h>

char *get_delimiter(char *str)
{
    char **list;
    char *temp;
    int i;

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

char *take_off_begin(char *str)
{
    int i;
    i = 0;

    while (str[i] == '<')
        i++;
    while (ft_iswhitespace_bonus(str[i]))
        i++;
    while (!ft_iswhitespace_bonus(str[i]))
        i++;
    return (ft_substr(str,i, ft_strlen(str) - i));
}

char *take_off_middle(char *str)
{
    int i;
    char *new_str;
    int j;

    j = 0;
    i = 0;

    new_str = malloc(sizeof(char *) * ft_strlen(str) - 1);
    while (str[i])
    {
        if (str[i] == '<')
            break;
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

char	*child_readin(char *cmd)
{
	char	*line;
	char	*final_buff;
	char	*buff;
	char	*temp;
	char	*delimiter;

	final_buff = ft_strdup("");
    delimiter = get_delimiter(cmd);
	final_buff = ft_strdup("");
	while (1)
	{
		buff = readline(">>");
		if (ft_strncmp(buff, delimiter, ft_strlen(buff)) == 0)
			break ;
		temp = final_buff;
		final_buff = ft_strjoin(final_buff, buff);
		free(temp);
		line = ft_strdup("\n");
		final_buff = ft_strjoin(final_buff, line);
		free(line);
        free(buff);
	}
	free(delimiter);
	return (final_buff);
}


char *exec_redin(char *cmd, t_list **env, char **paths, int fd)
{
    pid_t pid;
    char *buff;
    char **str;
    char *str2;
    char *final_buff;
    char *temp;
    char *delimiter;
    char *line;

    final_buff = ft_strdup("");
    delimiter = get_delimiter(cmd);
    if (cmd[0] == '<')
        str2 = take_off_begin(cmd);
    else
        str2 = take_off_middle(cmd);
    return (str2);
}