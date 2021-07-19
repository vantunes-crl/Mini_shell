#include "mini_shell.h"

int	which_redirect(char *str)
{
	if (ft_strnstr(str, " >> ", ft_strlen(str)))
		return (2);
	else if (ft_strnstr(str, " > ", ft_strlen(str)))
		return (1);
	else if (ft_strnstr(str, "<<", ft_strlen(str)))
		return (4);
	else if (ft_strnstr(str, "<", ft_strlen(str)))
		return (3);
	return (0);
}
