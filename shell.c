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

char **parse_cmds(char *str)
{
    char **cmds;

    str = ft_strtrim(str, "\t");
    cmds = ft_split(str, ' ');
    return (cmds);
}

int main()
{
    char inputString[200];
    char **cmds;

    take_line(inputString);       
    cmds = parse_cmds(inputString);
    printf("%s\n",cmds[2]);
}