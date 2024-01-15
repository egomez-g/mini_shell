#include "../mini_shell.h"

static char	*get_infile(char *txt)
{
	int	i;
	int	end;
	char *infile;

	i = 0;
	end = 0;
	i++;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && ft_valid_name_char(txt[i + end]) == 1)
		end++;
	if (end > 0)
		infile = ft_substr(txt, i, i + end - 1);
	else
		infile = NULL;
	return (infile);
}
static char	*get_limit(char *txt)
{
	int	i;
	int	end;

	i = 0;
	end = 0;
	i++;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && ft_valid_name_char(txt[i + end]) == 1)
		end++;
	if (end > 0)
		return(ft_substr(txt, i, i + end - 1));
	else
		return(ft_substr(txt, 0, 0));
}

void	count_infiles(char *txt, t_mini_shell *ms)
{
	int	i;
	int	index;
	int count;

	count = 0;
	i = 0;
	index = 0;
	while	(txt[i])
	{
		if (txt[i] == '|' || txt[i] == ';')
		{
			ms->cmds[index].infiles = (char **)malloc(sizeof(char *) * (count + 1));
			if (!ms->cmds[index].infiles)
				return ;
			ms->cmds[index].infiles[count] = NULL;
			++index;
			count = 0;
		}
		else if (txt[i] == '<')
		{
			if (txt[i + 1] == '<')
				i++;
			else
				count++;
		}
		++i;
	}
	ms->cmds[index].infiles = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ms->cmds[index].infiles)
		return ;
	ms->cmds[index].infiles[count] = NULL;
}

void	find_infile(char *txt, t_mini_shell *ms)
{
	char	*limitador;
	int index;
	int	file_index;

	index = 0;
	file_index = 0;
	ms->cmds[index].here_doc = 0;
	ms->cmds[0].infiles = NULL;
	count_infiles(txt, ms);
	while (*txt)
	{
		if (*txt == '|' || *txt == ';')
		{
			file_index = 0;
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
				limitador = get_limit(txt);
				heredoc(limitador, ms, index);
				free(limitador);
				ms->cmds[index].here_doc = 1;
			}
			else
			{
				ms->cmds[index].infiles[file_index] = get_infile(txt);
				ms->cmds[index].here_doc = 0;
				file_index++;
			}
		}
		txt++;
	}
}

//con heredoc lo haces siempre pero no lo usas si luego hay otro infile


//hacer el heredoc aqui o en el pipex

