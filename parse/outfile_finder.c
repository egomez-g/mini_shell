#include "../mini_shell.h"

static char	*get_outfile(char *txt, int start, t_mini_shell *ms)
{
	int		i;
	int		end;
	char	*outfile;

	i = start + 1;
	end = 0;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && txt[i + end] != ' ')
	{
		if (txt[i + end] == '\'' || txt[i + end] == '\"')
			end += skip_quotes(txt + i + end, txt[i + end]);
		end++;
	}
	if (end > 0)
		outfile = ft_substr(txt, i, end);
	else
		outfile = NULL;
	return (clean_quotes(outfile, ms));
}

void	count_outfiles(char *txt, t_mini_shell *ms)
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
			ms->cmds[index].outfiles = (char **)malloc(sizeof(char *) * \
			(count + 1));
			if (!ms->cmds[index].outfiles)
				return ;
			ms->cmds[index].outfiles[count] = NULL;
			++index;
			count = 0;
		}
		else if (txt[i] == '>')
		{
			if (txt[i + 1] == '>')
				i++;
			else
				count++;
		}
		++i;
	}
	ms->cmds[index].outfiles = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ms->cmds[index].outfiles)
		return ;
	ms->cmds[index].outfiles[count] = NULL;
}

void	find_outfile(char *txt, t_mini_shell *ms)
{
	int		i;
	int		index;
	int		file_index;

	i = 0;
	index = 0;
	file_index = 0;
	ms->cmds[0].outfiles = NULL;
	count_outfiles(txt, ms);
	while (txt[i])
	{
		if (txt[i] == '|' || txt[i] == ';')
		{
			file_index = 0;
			index++;
		}
		if (txt[i] == '>')
		{
			ms->cmds->trunc = 1;
			if (txt[i + 1] == '>')
			{
				i++;
				ms->cmds->trunc = 0;
			}
			ms->cmds[index].outfiles[file_index] = get_outfile(txt, i, ms);
			file_index++;
		}
		i++;
	}
}
