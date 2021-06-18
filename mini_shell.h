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
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>


int flag;

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

void print_echo(char **cmds);
void print_dir();
void print_env(t_list *envp);

#endif