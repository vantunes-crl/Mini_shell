#include "mini_shell.h"
#include <dirent.h>

int main(int argc, char **argv, char **env)
{
    struct dirent *pdirent;
    DIR *pdir;
    
    pdir = opendir(argv[1]);
    if (pdir == NULL)
    {
        printf ("Cannot open directory '%s'\n", argv[1]);
        return 1;
    }

    while ((pdirent = readdir(pdir)) != NULL) 
        printf ("[%s]\n", pdirent->d_name);
    

    closedir (pdir);
    return 0;
}
