#ifndef MINI_SHELL
# define MINI_SHELL

#define TRUE 1
#define FALSE 0
#define WHITE_SPACE "\t "

#include "ft_libft/libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <termios.h>

int g_exit_status;
int g_flag_env;

typedef struct s_fds
{
	int fdd;
	int fd[2];
	int i;
	pid_t pid;
	int		temp_exit;
	char	*heredoc_buff;

} t_fds;

typedef struct s_vars
{
	int i;
	int count;
	int flag;
	char	**temp_str;
	pid_t	pid;
	int		fd_red;
	char	*new_cmd_list;
}			t_vars;

typedef struct s_quotes
{
	int start;
	int end;
	char		*temp;
}           t_quotes;

/*exec_functions */
void	exce_arg(char **cmds, t_list *env, char **paths);
void	exec_pipe(char *str);
void    exec_cmd(char **cmds, t_list **env, char **paths);
void    execve_exec(char **paths, char **cmds, char **env_matriz);
void	main_process(char **cmds_list, t_list **env, char **paths);

/* parse function */
char	**parse_cmds(char *str, t_list **env);
char	**cmds_list(char *str);
t_list	*init_env(char **env);

/* utils */
void	error(char *str);
int     take_line(char *str);
void	free_paths(char **paths);
void    deleteList(t_list **env);
char    **list_to_matriz(t_list *env);
int		is_abspath(char *str);
int		cont_list(char **list);

/*builtings */
void    print_echo(t_list **env, char **cmds);
void    print_dir();
void    print_env(t_list *envp);
void    handle_var_env(char *var_env, t_list *env, int flag, int n);
void    has_exit(char **cmds_list, t_list **env);
void    print_dir();
void	ft_cd(char **temp_cmds);
void	ft_unset(t_list *envp, char **temp_cmds);
void	ft_export(t_list *envp, char **temp_cmds);

/* redirct out*/
int		which_redirect(char *str);
char	*new_cmds(char *cmds);
int		creat_file(int redirect, char *file_name);
t_list	*file_name(char *cmds);
char	*new_cmds_in(char *cmd);
char	*redirect_input(int redirect, char *buff, int fd);
char	*get_delimiter(char *str);
char	**find_path(char **cmds, t_list *env);
void    kill_handler(int sig);
char	*find_filename(char *cmd);
char	*new_cmd_in(char *cmd);
char	*take_off_middle(char *str);
char	*take_off_begin(char *str);
char	*get_delimiter(char *str);
char    **parse_quotes(char *str);
int     choose_quote(char *str);
int     check_quotes(char *str);
char	*take_care_of_env(char *str, t_list *env);
int     cont_list(char **cmds_list);
void    multiple_redirect(int has_redirect, char *cmds_list, t_list **env, char **paths);

/* redirect in */
char	*heredoc_input(char **cmds);
char	*child_readin(char *cmd);
void	take_off(char **cmds_list, int i);
void	red_in_simple(char **cmds_list, int i);
void	write_heredoc(char *heredoc_buff,int fd);

#endif