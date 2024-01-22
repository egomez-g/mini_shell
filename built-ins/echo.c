#include "../mini_shell.h"

static int	check_nl(char *txt)
{
	int	i;

	i = 0;
	if (txt[i] != '-')
		return (1);
	i++;
	while (txt[i])
	{
		if (txt[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static void	print_echo(char *txt, t_mini_shell *ms)
{
	int	i;

	i = ms->num_cmds;
	i = 0;
	while (txt[i])
	{
		if (txt[i] == '$' && txt[i + 1] && txt[i + 1] == '?')
		{
			printf("%d", WEXITSTATUS(ms->status));
			i += 2;
		}
		else
			printf("%c", txt[i]);
		i++;
	}
}


static void	skip_word(char *txt, int *i)
{
	while (txt[*i] && (txt[*i] != ' ' && !(txt[*i] <= 13 && txt[*i] >= 9)))
		*i += 1;
}

void	do_echo(char *txt, t_mini_shell *ms)
{
	int		i;
	int		nl;
	int		nl_bool;
	char	**str;

	i = 0;
	str = ft_split(txt, ' ');
	if (!str)
		return ;

	nl_bool = 0;
	nl = 0;
	while (check_nl(str[i]))
	{
		i++;
		nl++;
	}
	if(nl > 0)
		nl_bool = 1;
	i = 0;

	skip_spaces(txt, &i);
	i += 4;
	skip_spaces(txt, &i);

	while (nl >= 0)
	{
		skip_word(txt, &i);
		skip_spaces(txt, &i);
		nl--;
	}
	print_echo(txt + i, ms);
	if (nl_bool)
		printf("\n");
	free_strs(str);
}
