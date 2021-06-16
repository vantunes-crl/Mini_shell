#include "mini_shell.h"

/* builting function to simulate echo in shell */
void print_echo(char **cmds)
{
    int n;

    n = 0;
    cmds++;
    if (ft_strncmp(*cmds, "-n", 2) == 0) /* take of the line breaker */
    {    
        n = 1;
        cmds++;
    }
    while (*cmds)
    {
        if (*(cmds + 1) == NULL)
            printf("%s", *cmds);
        else
            printf("%s ", *cmds);
        cmds++;
    }
    if (!n)
        printf("\n");
}

/* builting function to simulate pwd in shell */
void print_dir()
{
    char str[1040];

    getcwd(str, sizeof(str)); /* function that get the actual Directory from the sistem */
    printf("%s\n",str);
}

/* builting function to simulate env in shell without parameters */
void print_env(t_list *envp)
{
    while (envp != NULL)
    {
        printf("%s\n",(char *)envp->content); /* print all env lst */
        envp = envp->next;
    }
}