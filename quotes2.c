#include "mini_shell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	choose_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			return (1);
		else if (str[i] == 39)
			return (2);
		i++;
	}
	return (0);
}

int	handle_cif_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '$' && str[i - 1] == '\'')
		return (1);
	else
		return (0);
}
