#include "mini_shell.h"

t_list	*case1(t_quotes *qt, char *str, t_list *list)
{
	char	*temp;

	qt->start++;
	qt->end = qt->start;
	while (str[qt->end] != 34 && str[qt->end] != '\0')
		qt->end++;
	temp = ft_substr(str, qt->start, qt->end - qt->start);
	ft_lstadd_back(&list, ft_lstnew((void *)temp));
	qt->end++;
	qt->start = qt->end;
	return (list);
}

static void	case2(t_quotes *qt, char *str, t_list *list)
{
	char	*temp;

	temp = NULL;
	qt->start++;
	qt->end = qt->start;
	while (str[qt->end] != 39 && str[qt->end] != '\0')
		qt->end++;
	temp = ft_substr(str, qt->start, qt->end - qt->start);
	ft_lstadd_back(&list, ft_lstnew(temp));
	qt->end++;
	qt->start = qt->end;
}

static	t_quotes	last_case(t_quotes qt, char *str, t_list *list, char *temp)
{
	temp = NULL;
	qt.end = qt.start;
	while (str[qt.end] != 32 && str[qt.end] != '\0')
		qt.end++;
	temp = ft_substr(str, qt.start, qt.end - qt.start);
	ft_lstadd_back(&list, ft_lstnew(temp));
	qt.end++;
	qt.start = qt.end;
	return (qt);
}

char	**parse_quotes(char *str)
{
	t_quotes	qt;
	t_list		*list;
	char		*temp;
	char		**cmds;

	list = NULL;
	qt.end = 0;
	qt.start = 0;
	temp = NULL;
	while (str[qt.start])
	{
		if (str[qt.start] == '"')
			list = case1(&qt, str, list);
		else if (str[qt.start] == '\'')
			case2(&qt, str, list);
		else if (str[qt.start] == ' ')
			qt.start++;
		else
		{
			qt.end = qt.start;
			while (str[qt.end] != 32 && str[qt.end] != '\0')
				qt.end++;
			temp = ft_substr(str, qt.start, qt.end - qt.start);
			ft_lstadd_back(&list, ft_lstnew(temp));
			qt.end++;
			qt.start = qt.end;
		}
	}
	cmds = list_to_matriz(list);
	return (cmds);
}
