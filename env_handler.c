#include "mini_shell.h"

t_list *init_env(char **env)
{
    t_list *elem;
    char **envp;

    elem = NULL;
    envp = env;
    while (*envp != NULL)
        ft_lstadd_back(&elem,ft_lstnew(*envp++));
    return (elem);
}