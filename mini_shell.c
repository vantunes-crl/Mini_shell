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

void enter_main(char **temp_cmds, t_list *envp)
{
    char **paths;

    g_flag = 1;
    has_exit(temp_cmds , &envp);
    paths = find_path(temp_cmds, envp);
    main_process(temp_cmds, &envp, paths);
    free_paths(temp_cmds);
    if (paths)
        free_paths(paths);
}

int main(int argc, char **argv, char **env)
{
    char inputString[200];
    char **temp_cmds;

    t_list *envp;
    g_exit_status = 0;
    g_flag_env = 0;
    envp = init_env(env);
    g_flag = 0;

    signal(SIGINT, kill_handler);
    signal(SIGQUIT, kill_handler);

    while (TRUE)
    {
        if (take_line(inputString))
            continue;
        else
        {
            temp_cmds = list_cmds(inputString);
            if (ft_strncmp(temp_cmds[0],"cd", 2) == 0)
                ft_cd(temp_cmds);
            else if (ft_strncmp(temp_cmds[0], "unset", 5) == 0)
                ft_unset(envp, temp_cmds);
            else if (ft_strncmp(temp_cmds[0], "export", 6) == 0)
                ft_export(envp, temp_cmds);
            else
                enter_main(temp_cmds, envp);
        }
    }
    return (0);
}