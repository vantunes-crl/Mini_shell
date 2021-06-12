#include "mini_shell.h"

int take_line(char *str)
{
    char *buff;

    buff = readline("\033[3;32mMiniShell\e[0m\U0001F916:");
    if (ft_strlen(buff) != 0)
    {
        add_history(buff);
        strcpy(str, buff);
        return (0);
    }
    else
        return (1);
}