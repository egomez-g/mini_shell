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

static void	skip_word(char *txt, int *i)
{
	while (txt[*i] && (txt[*i] != ' ' && !(txt[*i] <= 13 && txt[*i] >= 9)))
		*i += 1;
}

static void	print_echo(char *txt, t_mini_shell *ms)
{
	int	i;
	int j;

	i = ms->num_cmds;
	i = 0;
	while (txt[i])
	{
		j = 0;
		skip_spaces(txt + i, &j);
		if (!txt[i + j] || (txt[i + j] == ' ' || (txt[i + j] <= 13 && txt[i + j] >= 9)))
			break ;
		if((txt[i] == ' ' || (txt[i] <= 13 && txt[i] >= 9)))
		{
			printf("%c", txt[i]);
			skip_spaces(txt, &i);
			i--;
		}
		else if (txt[i] == '$' && txt[i + 1] && txt[i + 1] == '?')///////////se maneja antes
		{
			printf("%d", WEXITSTATUS(ms->status));
			i += 2;
		}
		else if (txt[i] == '$' && txt[i + 1] )///////////se maneja antes
		{
			skip_word(txt, &i);
			skip_spaces(txt, &i);
		}
		else
			printf("%c", txt[i]);
		i++;
	}
}


void	do_echo(char *txt, t_mini_shell *ms)
{
	int		i;
	int		nl;
	int		nl_bool;
	char	**str;

	str = ft_split(txt, ' ');
	if (!str)
		return ;
	i = 1;
	nl = 0;
	nl_bool = 0;
	while (str[i] && !check_nl(str[i]))
	{
		i++;
		nl++;
	}
	if (nl > 0)
		nl_bool = 1;
	i = 0;
	skip_spaces(txt, &i);
	i += 4;
	skip_spaces(txt, &i);
	while (nl > 0)
	{
		skip_word(txt, &i);
		skip_spaces(txt, &i);
		nl--;
	}
	print_echo(txt + i, ms);
	if (!nl_bool)
		printf("\n");
	free_strs(str);
}
