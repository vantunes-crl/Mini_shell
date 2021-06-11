#include "mini_shell.h"

void error(char *str)
{
    perror(str);
    exit(0);
}

int exce_arg(char **cmds)
{
    pid_t pid;
    char **paths;
    int i = 0;
    int j = 0;

    paths = ft_split(getenv("PATH"), ':');
    pid = fork();
    if (pid == -1)
        perror("fork");
    else if (pid == 0)
    {
        while (paths[i])
        {
            paths[i] = ft_strjoin(paths[i], "/");
            paths[i] = ft_strjoin(paths[i], cmds[0]);
            execve(paths[i], cmds,  NULL);
            i++;
        }
        exit(0);
    }
    wait(NULL);
}

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

char **parse_cmds(char *str)
{
    char **cmds;
    int i = 0;

    cmds = ft_split(str, ' ');
    while (cmds[i] != NULL)
    {
        cmds[i] = ft_strtrim(cmds[i], "\t ");
        i++;
    }
    return (cmds);
}

int has_pipes(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '|')
            return (TRUE);
        i++;
    }
    return (FALSE);
}

/* return a cmd list */
char **cmds_list(char *str)
{
    char **cmds_lst;
    int i = 0;

    cmds_lst = ft_split(str, '|');
    while (cmds_lst[i] != NULL)
    {
        cmds_lst[i] = ft_strtrim(cmds_lst[i], WHITE_SPACE);
        i++;
    }
    return(cmds_lst);
}

void exec_pipes(char *str)
{
    char **cmds_lst;
    int fd[2];
    pid_t pid;

    cmds_lst = cmds_list(str);
    if (pipe(fd) < 0)
        error("pipe");
    pid = fork();
    if (pid < 0)
        error("fork");
    if (pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
	    close(fd[0]);
	    close(fd[1]);
        exce_arg(parse_cmds(cmds_lst[0]));
    }
    else
    {
        dup2(fd[0], STDIN_FILENO);
	    close(fd[0]);
	    close(fd[1]);
        exce_arg(parse_cmds(cmds_lst[1]));
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, NULL, 0);
}

int main()
{
    char inputString[200];
    char **cmds;
    char **pipes;
    int i = 0; 

    while (TRUE)
    {
        if (take_line(inputString))
            continue ;
        if (has_pipes(inputString))
            exec_pipes(inputString);
        else
        {
            cmds = parse_cmds(inputString);
            if (ft_strncmp(cmds[0],"cd", 2) == 0)
                chdir(cmds[1]);
            else if (ft_strncmp(cmds[0],"exit", 4) == 0)
                exit(0);
            else
                exce_arg(cmds);
        }
    }
}