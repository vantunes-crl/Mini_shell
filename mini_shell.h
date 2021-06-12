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
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/*exec_functions */
void	exce_arg(char **cmds);
void	exec_pipes(char *str);

/* parse function */
char	**parse_cmds(char *str);
int		has_pipes(char *str);
char	**cmds_list(char *str);

/* utils */
void error(char *str);
int take_line(char *str);

#endif