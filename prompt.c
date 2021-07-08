#include "mini_shell.h"

void    kill_handler(int sig)
{
    // struct termios conf;
    // struct termios oldconf;
    // ioctl(ttyslot(), TIOCGETA, &conf);
    // ioctl(ttyslot(), TIOCGETA, &oldconf);
    // conf.c_lflag &= ~(ECHO);
    // conf.c_lflag &= ~(ICANON);
    // ioctl(ttyslot(), TIOCSETA, &conf);
    // conf.c_lflag ^= (ECHO);
    write(1, "\r\n\033[3;32mMiniShell\e[0m\U0001F916:", 28);
    //ioctl(ttyslot(), TIOCSETA, &oldconf);
     return ;
}

int take_line(char *str)
{
    char *buff;

    buff = readline("\r\033[3;32mMiniShell\e[0m\U0001F916:");
    if (!buff) 
    {
        printf("\r");
        exit(0);
    }
    if (ft_strlen(buff) != 0)
    {
        add_history(buff);
        ft_strlcpy(str, buff, ft_strlen(buff) + 1);
        free(buff);
        return (0);
    }
    else
        return (1);
}