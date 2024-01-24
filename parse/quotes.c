#include "../mini_shell.h"

//static void	loop_quotes(char **txt)
//{

//}

static void count_quotes(char *txt, int *s_quot, int *d_quot)
{
	int	i;

	i = 0;
	while (txt[i])
	{
		if (txt[i] == '\"')
			(*d_quot)++;
		if (txt[i] == '\'')
			(*s_quot)++;
		++i;
	}
}

int	manage_quotes(char *txt)
{
	int		s_quot;
	int		d_quot;

	s_quot = 0;
	d_quot = 0;
	count_quotes(txt, &s_quot, &d_quot);

	if (s_quot % 2 != 0 || d_quot % 2 != 0)
	{
		printf("minishell> Error: incomplete quotes\n");
		return(1);
	}
	return (0);
}
