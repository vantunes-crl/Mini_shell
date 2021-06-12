#include "mini_shell.h"

// void exce_arg(char **cmds)
// {
//     char **paths;
//     int i = 0;

//     paths = ft_split(getenv("PATH"), ':');
//     while (paths[i])
//     {
//         paths[i] = ft_strjoin(paths[i], "/");
//         paths[i] = ft_strjoin(paths[i], cmds[0]);
//         execve(paths[i], cmds,  NULL);
//         i++;
//     }
// }

// void exec_pipe(char *str)
// {
//     char **cmds_lst;
//     pid_t pid1;
//     pid_t pid2;
//     int fd[2];

//     cmds_lst = cmds_list(str);
//     if(pipe(fd) < 0)
//         error("pipe");
//     pid1 = fork();
//     if (pid1 < 0)
//         error("fork");

//     child process 1
//     if (pid1 == 0)
//     {
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         exce_arg(parse_cmds(cmds_lst[0]));
//     }

//     pid2 = fork();
//     if (pid2 < 0)
//         error("fork");

//     child process 2
//     if (pid2 == 0)
//     {
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         exce_arg(parse_cmds(cmds_lst[1]));
//     }
//     close(fd[0]);
//     close(fd[1]);
//     wait(NULL);
//     wait(NULL);
// }

// void exec_multiple_pipes(char *str , int pipes)
// {
//     int **fds;
//     int i = 0;

//     fds = ft_calloc(pipes, sizeof(int));
//     while (i < pipes)
//     {
//         fds[i] = ft_calloc(2, sizeof(int));
//         i++;
//     }
//     i = 0;
//     while (i < pipes)
//     {
//         if (pipe(fds[i]) < 0)
//             error("pipe");
//         i++;
//     }

//     pid_t pid1;
//     pid1 = fork();

//     if (pid1 == 0)
//     {
//         close(fds[0][0]);
//         close(fds[0][1]);
//         close(fds[1][0]);
//         close(fds[1][1]);
//         close(fds[2][0]);
//         close(fds[2][1]);
//         int x;
//         if (read(fds[0][0], &x, sizeof(int)) < 0)
//             return 3;
//         x += 5;
//         if (write(fds[1][1], &x, sizeof(int)) < 0)
//             return 4;
//         return (0);
//     }
// }
// 0 0
// 0 1
// 1 0
// 1 1
// 2 0
// 2 1
int main()
{
    int i = 0;
    int j;

    while (i <= 2)
    {
        j = 0;
        while (j < 2)
        {
            close(fds[i][j]);
            j++;
        }
        i++;
    }
    //exec_multiple_pipes("abc | abc | abc", has_pipes("abc | abc | abc"));
}