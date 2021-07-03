#include "mini_shell.h"

/* function create a buffer from the stdout and cpy to a string and add_history*/
/* after add to history you can use the arrows up and down */
/* return 1 if has no words to read to keep the program on */

// static void int_handler(int sig_num)
// {
//     printf("\n"); // Move to a new line
//     rl_on_new_line(); // Regenerate the prompt on a newline
//     rl_replace_line(); // Clear the previous text
//     rl_redisplay();
// }

int take_line(char *str)
{
    char *buff;

    buff = readline("\033[3;32mMiniShell\e[0m\U0001F916:");
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