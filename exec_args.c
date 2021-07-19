#include "mini_shell.h"

void	execve_exec(char **paths, char **cmds, char **env_matriz)
{
	char	*temp_path;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!paths)
		printf("bash: %s: No such file or directory\n", cmds[0]);
	while (paths[i])
	{
		temp_path = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(temp_path);
		temp_path = paths[i];
		paths[i] = ft_strjoin(paths[i], cmds[0]);
		free(temp_path);
		ret = execve(paths[i], cmds, NULL);
		i++;
	}
	if (ret <= 0)
	{
		g_exit_status = 127;
		error(cmds[0]);
	}
}

void	exce_arg(char **cmds, t_list *env, char **paths)
{
	int		abs_path;
	char	**env_matriz;

	env_matriz = list_to_matriz(env);
	abs_path = is_abspath(cmds[0]);
	if (abs_path)
	{
		abs_path = execve(cmds[0], cmds, env_matriz);
		if (abs_path < 0)
		{
			g_exit_status = 127;
			error(cmds[0]);
		}
	}
	else
		execve_exec(paths, cmds, env_matriz);
}

void	exec_cmd(char **cmds, t_list **env, char **paths)
{
	char	*temp;

	if (ft_strncmp(cmds[0], "env", 3) == 0)
		print_env(*env);
	else if (ft_strncmp(cmds[0], "pwd", 3) == 0)
		print_dir();
	else if (ft_strncmp(cmds[0], "echo", 4) == 0)
		print_echo(env, cmds);
	else if (ft_strncmp(cmds[0], "$?", 2) == 0)
	{
		printf("%d\n", g_exit_status);
		g_exit_status = 0;
		exit(0);
	}
	else if (ft_strncmp(cmds[0], "$", 1) == 0 && g_flag_env == 0)
	{
		temp = ft_strtrim(*cmds, "$");
		handle_var_env(temp, *env, 1, 1);
		exit(0);
	}
	else
		exce_arg(cmds, *env, paths);
	exit(127);
}
