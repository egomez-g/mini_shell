#include "../mini_shell.h"

static void	get_outfile(char *txt, t_mini_shell *ms, int index)
{
	int		i;
	int		end;
	int		fd_aux;

	i = 0;
	end = 0;
	i++;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && ft_isalnum(txt[i + end]) == 1)
		end++;
	if (ms->cmds[index].outfile != NULL)
	{
		//append
		fd_aux = open(ms->cmds[index].outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd_aux != -1)
			close(fd_aux);
		free(ms->cmds[index].outfile);			
	}
	if (end > 0)
		ms->cmds[index].outfile = ft_substr(txt, i, i + end - 1);
	else
		ms->cmds[index].outfile = ft_substr(txt, 0, 0);
}

void	find_outfile(char *txt, t_mini_shell *ms)
{
	int		index;

	index = 0;
	ms->cmds[0].outfile = NULL;
	while (*txt)
	{
		if (*txt == '|')
			index++;
		if (*txt == '\"')
		{
			txt++;
			while (*txt != '\"')
				txt++;
		}
		if (*txt == '\'')
		{
			txt++;
			while (*txt != '\'')
				txt++;
		}
		if (*txt == '>')
		{
			ms->cmds->trunc = 1;
			if (*(txt + 1) == '>')
			{
				txt++;
				ms->cmds->trunc = 0;
			}
			get_outfile(txt, ms, index);
		}
		txt++;
	}
}
//cambiar la flag de trunc a donde toca
//rollo esta en la estructura pero es por cada outfile

//las comillas las ignora 💀
/*
c3r12s3:git-minishell sgil-moy$ <Makefile wc -w
      81
c3r12s3:git-minishell sgil-moy$ <"Makefil"e wc -w
      81
c3r12s3:git-minishell sgil-moy$ <"Make"file wc -w
      81
*/
//si el ultimo no tiene outfile lo saca por consola
//si hay varios coge el ultimo antes del |
//si no hay ninguno duplica y se lo pasa al siguiente