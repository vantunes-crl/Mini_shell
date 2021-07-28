#include "mini_shell.h"

void	kill_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_flag == 0)
		{
			write(1, "\n", 1);
			rl_redisplay();
			rl_on_new_line();
		}
		else
		{
			write(1, "\n", 1);
			rl_redisplay();
			g_flag = 0;
		}
	}
	else if (sig == SIGQUIT)
	{
	}
	g_exit_status = 130;
	return ;
}

int	take_line(char *str)
{
	char	*buff;

	buff = readline("\033[3;32mMiniShell\e[0m\U0001F916:");
	if (!buff)
	{
		printf("\r");
		exit(0);
	}
	if (ft_strlen(buff) != 0)
	{
		add_history(buff);
		ft_strlcpy(str, buff, ft_strlen(buff) + 1);
		free(buff);
		return (0);
	}
	else
		return (1);
}
