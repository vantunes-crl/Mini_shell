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

void owncmds(int cmd)
{
    char *str;

    str = getenv("USER");
    if (cmd == 0) // exit
    {
        printf("\033[0;31mGood  Bye\e[0m %s \U0001F97A\U0001F97A\U0001F97A\U0001F97A\n", str);
        exit(0);
    }
    else if (cmd == 1)
    {
        printf("--------------------------------------Help--------------------------------------\n");
        printf("exit == quit the program\n");
        printf("cd `dest` == change the directory\n");
        printf("--------------------------------------------------------------------------------\n");
    }
}