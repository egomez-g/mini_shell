#include "../mini_shell.h"

void	skip_spaces(char *txt, int *i)
{
	while (txt[*i] && (txt[*i] == ' ' || (txt[*i] <= 13 && txt[*i] >= 9)))
		*i += 1;
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		++i;
	}
	free(strs);
}
