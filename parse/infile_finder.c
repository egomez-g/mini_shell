#include "../mini_shell.h"

static char	*get_infile(char *txt, int start, t_mini_shell *ms)
{
	int		i;
	int		end;
	char	*infile;

	i = start + 1;
	end = 0;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;	
	if (txt[i] == '\'' || txt[i] == '\"')
		return (get_literal(txt, &i));
	while (txt[i + end] && ft_valid_name_char(txt[i + end]) == 1)
		end++;
	if (end > 0)
		infile = ft_substr(txt, i, end);
	else
		infile = NULL;
	return (clean_quotes(infile, ms));
}

static char	*get_limit(char *txt, int start, t_mini_shell *ms)
{
	int	i;
	int	end;

	i = start + 1;
	end = 0;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && txt[i] >= 9)))
		i++;
	if (txt[i] == '\'' || txt[i] == '\"')
		return (get_literal(txt, &i));
	while (txt[i + end] && ft_valid_name_char(txt[i + end]) == 1)
		end++;
	if (end > 0)
		return (clean_quotes(ft_substr(txt, i, end), ms));
	else
		return (clean_quotes(ft_substr(txt, 0, 0), ms));
}

void	count_infiles(char *txt, t_mini_shell *ms)
{
	int	i;
	int	index;
	int	count;

	count = 0;
	i = 0;
	index = 0;
	while (txt[i])
	{
		if (txt[i] == '|' || txt[i] == ';')
		{
			ms->cmds[index].infiles = (char **)malloc(sizeof(char *) * \
			(count + 1));
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
	int		i;
	int		index;
	int		file_index;

	i = 0;
	index = 0;
	file_index = 0;
	ms->cmds[index].here_doc = 0;
	ms->cmds[0].infiles = NULL;
	count_infiles(txt, ms);
	while (txt[i])
	{
		if (txt[i] == '|' || txt[i] == ';')
		{
			file_index = 0;
			ms->cmds[index].here_doc = 0;
			index++;
		}
		if (txt[i] == '<')
		{
			if (txt[i + 1] == '<')
			{
				i++;
				limitador = get_limit(txt, i, ms);
				heredoc(limitador, ms, index);
				free(limitador);
				ms->cmds[index].here_doc = 1;
			}
			else
			{
				ms->cmds[index].infiles[file_index] = get_infile(txt, i, ms);
				ms->cmds[index].here_doc = 0;
				file_index++;
			}
		}
		i++;
	}
}
