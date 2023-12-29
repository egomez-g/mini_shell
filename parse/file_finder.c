#include "../mini_shell.h"

static void get_infile(char *txt, t_mini_shell *ms)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	i++;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && ft_isalnum(txt[i + end]) == 1)
		end++;
	if (ms->infile != NULL)
		free(ms->infile);
	if (end > 0)
		ms->infile = ft_substr(txt, i, i + end -1 );
	else
		ms->infile = NULL;
}

void find_infile(char *txt, t_mini_shell *ms)
{

	ms->here_doc = 0;
	while (*txt)
	{
		if (*txt == '<')
		{
			if (*(txt + 1) == '<')
			{
				txt++;
				ms->here_doc = 1;
			}
			get_infile (txt, ms);	
		}
		txt++;
	}
}
