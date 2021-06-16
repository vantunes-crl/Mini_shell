#include "mini_shell.h"

/* function make a copy on the first envirement variavables on the sistem */
t_list *init_env(char **env)
{
    t_list *elem;
    char **envp;

    elem = NULL;
    envp = env;
    while (*envp != NULL) /* cpy all env from the sistem to a linked list */
        ft_lstadd_back(&elem,ft_lstnew(*envp++));
    return (elem);
}