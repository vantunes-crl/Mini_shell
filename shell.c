#include "mini_shell.h"

int take_line(char *str)
{
    char *buff;

    buff = readline("\033[3;32mMiniShell:");
    if (strlen(buff) != 0)
    {
        add_history(buff);
        strcpy(str, buff);
        return (0);
    }
    else
        return (1);
}

int main()
{
    char inputString[200];

    while(1)
    {
        if (take_line(inputString))
            continue ;
        
    }
}