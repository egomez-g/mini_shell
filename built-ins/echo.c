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

void	do_echo(char *txt, t_mini_shell *ms)
{
	int		i;
	int		nl;
	char	**str;

	i = 0;
	str = ft_split(txt, ' ');
	if (!str)
		return ;
	nl = check_nl(str[1]);
	skip_spaces(txt, &i);
	i += 4;
	skip_spaces(txt, &i);
	if (!nl)
	{
		i++;
		while (txt[i] == 'n')
			i++;
		skip_spaces(txt, &i);
	}
	print_echo(txt + i, ms);
	if (nl)
		printf("\n");
	free_strs(str);
}
