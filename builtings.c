#include "mini_shell.h"

void print_echo(char **cmds)
{
    int n;

    n = 0;
    cmds++;
    if (ft_strncmp(*cmds, "-n", 2) == 0)
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

void print_dir()
{
    char str[1040];

    getcwd(str, sizeof(str));
    printf("%s\n",str);
}


void print_env(char **envp)
{
    char **env;
    env = envp;
    while (*env != NULL)
        printf("%s\n", *env++);
}