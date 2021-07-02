#ifndef MINI_SHELL
# define MINI_SHELL


#define TRUE 1
#define FALSE 0
#define WHITE_SPACE "\t "
#define CLEAN printf("\033[K\r\n")

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

int exit_status;

/*exec_functions */
void	exce_arg(char **cmds, t_list *env);
void	exec_pipe(char *str);
void    exec_cmd(char **cmds,t_list **env);
void    print_dir();
void    multiple_pipes(char **cmds_list,t_list **env);

/* parse function */
char	**parse_cmds(char *str);
int		has_pipes(char *str);
char	**cmds_list(char *str);
t_list *init_env(char **env);

/* utils */
void error(char *str);
int take_line(char *str);
void owncmds(int cmd, t_list **env);
void	free_paths(char **paths);
void deleteList(t_list **env);

/*builtings */

void print_echo(t_list **env, char **cmds);
void print_dir();
void print_env(t_list *envp);
void    handle_var_env(char *var_env, t_list *env, int flag, int n);
void has_exit(char **cmds_list);

/* redirct */
int which_redirect(char *str);
char *new_cmds(char *cmds);
int creat_file(int redirect, char *file_name);
t_list *file_name(char *cmds);
char *new_cmds_in(char *cmd);
char *redirect_input(int redirect, char *buff, int fd);
void exec_redin(char *cmd, t_list **env);
char *take_off(char *str);
char *get_delimiter(char *str);
char *invert_cmd(char *cmd);

#endif