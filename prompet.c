#include "mini_shell.h"

/* function create a buffer from the stdout and cpy to a string and add_history*/
/* after add to history you can use the arrows up and down */
/* return 1 if has no words to read to keep the program on */
int take_line(char *str)
{
    char *buff;

    buff = readline("\033[3;32mMiniShell\e[0m\U0001F916:"); /* prompet mensage and get buff with function readline */
    if (ft_strlen(buff) != 0) /* if has something to read */
    {
        add_history(buff); /* cpy the buffer str to history , history can work with arrows down and up , and autocomplete with tabs */
        strcpy(str, buff); 
        free(buff); /* cpy the buff str to main str */
        return (0);
    }
    else
        return (1);
}

/* function for create own cmds */
void owncmds(int cmd, t_list **env)
{
    char *str;

    str = getenv("USER"); /* get the env var from sistem with user name*/
    if (cmd == 0) // exit
    {
        printf("\033[0;31mGood  Bye\e[0m %s \U0001F97A\U0001F97A\U0001F97A\U0001F97A\n", str);
        deleteList(env);
        exit(0);
    }
    else if (cmd == 1) /* help comand */
    {
        printf("--------------------------------------Help--------------------------------------\n");
        printf("exit == quit the program\n");
        printf("cd `dest` == change the directory\n");
        printf("--------------------------------------------------------------------------------\n");
    }
}
