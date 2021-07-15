#include "mini_shell.h"

int cont_list(char **list)
{
	int i = 0;
	while(list[i++]);
	return (i);
}

char *heredoc_input(char **cmds)
{
	int i;
	char *str;
	char *temp_str;
	int count = 0;
	int flag = 0;
	i = 0;

	while (cmds[i])
	{
		if (which_redirect(cmds[i]) == 4)
		{
			if (flag == 1)
			{
				temp_str = str;
				str = ft_strjoin(str, child_readin(cmds[i]));
				free(temp_str);
			}
			else
			{
				str = child_readin(cmds[i]);
				flag == 1;
			}
		}
		else
			count++;
		i++;
	}
	if (count == i)
		return (NULL);
	return(str);
}

void take_off(char **cmds_list, int i)
{
	char *temp_str;

	temp_str = cmds_list[i];
	if (cmds_list[i][0] == '<')
		cmds_list[i] = take_off_begin(cmds_list[i]);
	else
		cmds_list[i] = take_off_middle(cmds_list[i]);
	free(temp_str);
}

void red_in_simple(char **cmds_list, int i)
{
	char *fn = find_filename(cmds_list[i]);
	char *new_cmd = cmds_list[i];
	cmds_list[i] = new_cmd_in(cmds_list[i]);
	free(new_cmd);
	int fd_in = open(fn, O_RDWR, 0777);
	if (fd_in < 0)
		error("minishell");
}