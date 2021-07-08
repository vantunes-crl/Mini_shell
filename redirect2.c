#include "mini_shell.h"

void	loop_file_list(t_process *files, char *content,
	t_list **env, char **paths)
{
	pid_t	pid;
	int		fd_red;

	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		fd_red = creat_file(files->has_redirect, content);
		dup2(fd_red, 1);
		close(fd_red);
		exec_cmd(files->temp_str, env, paths);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(fd_red);
	}
}

void	multiple_redirect(int has_redirect, char *cmds_list,
	t_list **env, char **paths)
{
	t_list		*file_list;
	char		*new_cmd_list;
	t_process	files;
	pid_t pid;
	int fd_red;

	files.has_redirect = has_redirect;
	file_list = NULL;
	file_list = file_name(cmds_list);
	new_cmd_list = new_cmds(cmds_list);
	files.temp_str = parse_cmds(new_cmd_list);
	while (file_list != NULL)
	{
		pid = fork();
        if (pid == 0)
        {
            fd_red = creat_file(has_redirect, (char *)file_list->content);
            dup2(fd_red, 1);
            close(fd_red);
            exec_cmd(files.temp_str, env, paths);
            exit(0);
        }
        else
        {
            wait(NULL);
            close(fd_red);
        }
		file_list = file_list->next;
	}
	free(new_cmd_list);
	free_paths(files.temp_str);
	deleteList(&file_list);
	exit(0);
}
