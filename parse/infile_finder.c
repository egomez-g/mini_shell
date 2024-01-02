#include "../mini_shell.h"

static void	get_infile(char *txt, t_mini_shell *ms, int index)
{
	int	i;
	int	end;
	int	aux_fd;

	i = 0;
	end = 0;
	i++;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && ft_isalnum(txt[i + end]) == 1)
		end++;
	if (ms->cmds[index].infile != NULL)
	{
		aux_fd = open(ms->cmds[index].infile, O_RDONLY);
		if(aux_fd != -1)
			close(aux_fd);
		free(ms->cmds[index].infile);
	}
	if (end > 0)
		ms->cmds[index].infile = ft_substr(txt, i, i + end - 1);
	else
		ms->cmds[index].infile = NULL;
}
static char	*get_ilimit(char *txt)
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
	if (end > 0)
		return(ft_substr(txt, i, i + end - 1));
	else
		return(ft_substr(txt, 0, 0));
}

void	find_infile(char *txt, t_mini_shell *ms)
{
	char	*limitador;
	int index;

	index = 0;
	ms->cmds[index].here_doc = 0;
	while (*txt)
	{
		if (*txt == '|')
		{
			ms->cmds[index].here_doc = 0;
			index++;
		}
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
		if (*txt == '<')
		{
			if (*(txt + 1) == '<')
			{
				txt++;
				limitador = get_ilimit(txt);
				heredoc(limitador, ms, index);
				free(limitador);
				ms->cmds[index].here_doc = 1;
			}
			else
			{
				get_infile(txt, ms, index);
				if (ms->cmds[index].here_doc == 1)
					unlink("here_doc");
				ms->cmds[index].here_doc = 0;
			}
		}
		txt++;
	}
}

//con heredoc lo haces siempre pero no lo usas si luego hay otro infile