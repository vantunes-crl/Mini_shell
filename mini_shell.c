#include "mini_shell.h"

void error(char *str)
{
    perror(str);
}

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

static void handler_list_cmd(char **temp_cmds, t_list *envp)
{
    char **paths;

    has_exit(temp_cmds , &envp);
    paths = find_path(temp_cmds, envp);
    multiple_pipes(temp_cmds, &envp, paths);
    free_paths(temp_cmds);
}

int main(int argc, char **argv, char **env)
{
    char inputString[200];
    char **temp_cmds;
    t_list *envp;
    exit_status = 0;
    
    envp = init_env(env);
    signal(SIGINT, kill_handler);
    while (TRUE)
    {
        if (take_line(inputString))
            continue;
        else
        {
            temp_cmds = cmds_list(inputString);
            if (ft_strncmp(temp_cmds[0],"cd", 2) == 0)
                ft_cd(temp_cmds);
            else if (ft_strncmp(temp_cmds[0], "unset", 5) == 0)
                ft_unset(temp_cmds, envp);
            else if (ft_strncmp(temp_cmds[0], "export", 6) == 0)
                ft_export(temp_cmds, envp);
            else
                handler_list_cmd(temp_cmds, envp);
        }
    }
    return (0);
}
