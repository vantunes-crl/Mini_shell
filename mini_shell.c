#include "mini_shell.h"

/* function to hold all error events in the program */
void error(char *str)
{
    perror(str); /* function the returns the sistem error + string */
    exit(0);
}

void    kill_handler(int sig)
{/*
    struct termios conf;
    struct termios oldconf;
    ioctl(ttyslot(), TIOCGETA, &conf);
    ioctl(ttyslot(), TIOCGETA, &oldconf);
    //printf("old: %lu\n", conf.c_lflag);
    conf.c_lflag &= ~(ECHO);
    conf.c_lflag &= ~(ICANON);
    //printf("new: %lu\n", conf.c_lflag);
    ioctl(ttyslot(), TIOCSETA, &conf);
    //conf.c_lflag ^= (ECHOCTL);
    //printf("new back to old:%lu\n", conf.c_lflag);
    write(1, "\n\033[3;32mMiniShell\e[0m\U0001F916:", 26);
    ioctl(ttyslot(), TIOCSETA, &oldconf);
   */ return ;
}

/* main prompet its a loop then hold all program and wait for next cmds*/
int main(int argc, char **argv, char **env)
{
    char inputString[200];
    char **temp_cmds;
    char **temp_dir;
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
            {
                temp_dir = ft_split(temp_cmds[0], ' ');
                chdir(temp_dir[1]);
                free_paths(temp_dir);
            }
            else if (ft_strncmp(temp_cmds[0], "unset", 5) == 0)
            {
                temp_dir = ft_split(temp_cmds[0], ' ');
                del_elem_lst(&envp, temp_dir[1]);
                free_paths(temp_dir);
            }
            else if (ft_strncmp(temp_cmds[0], "export", 6) == 0)
            {
                temp_dir = ft_split(temp_cmds[0], ' ');
                ft_lstadd_back(&envp, ft_lstnew(temp_dir[1]));
                free_paths(temp_dir);
            }
            else
            {
                has_exit(temp_cmds);
                multiple_pipes(temp_cmds, &envp);
                free_paths(temp_cmds);
           }
        }
    }
    return (0);
}



// BUG FOR TABS! 
// BUG NO HISTORICO! (echo with argument)
// BUG echo $?
// Little bug with expr $? + $
// ctrl + / should quit minishell when there is something written in it
// blocking command like cat with no arguments + ctrl+c repeats the prompt
// echo "catlol.c | cat > lol.c"
// DO SIMPLES QUOTES AND DOUBLE QUOTES
// cd . and cd .. is not working (I THING cd IS NOT WORKING AT ALL)


