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
    char inputString[200]; /* small buffer for input string from stdin */
    char **temp_cmds;
    t_list *envp;
    exit_status = 0;

    envp = init_env(env); /* create a cpy of env variavables */
    signal(SIGINT, kill_handler);

    while (TRUE)
    {
        if (take_line(inputString)) /* keep going while dont have inputs */
            continue;
        else
        {
            temp_cmds = cmds_list(inputString);
            has_exit(temp_cmds);
            multiple_pipes(temp_cmds, &envp); /* exec multiple pipes */
            free_paths(temp_cmds);
        }
    }
    return (0);
}