#include "../mini_shell.h"

static char	*get_outfile(char *txt, int start)
{
	int		i;
	int		end;
	char	*outfile;

	i = start + 1;
	end = 0;
	while (txt[i] && (txt[i] == ' ' || (txt[i] <= 13 && *txt >= 9)))
		i++;
	while (txt[i + end] && ft_valid_name_char(txt[i + end]) == 1)
		end++;
	if (end > 0)
		outfile = ft_substr(txt, i, end);
	else
		outfile = NULL;
	return (outfile);
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
		//if (txt[i] == '\"')
		//{
		//	i++;
		//	while (txt[i] != '\"')
		//		i++;
		//}
		//if (txt[i] == '\'')
		//{
		//	i++;
		//	while (txt[i] != '\'')
		//		i++;
		//}
		if (txt[i] == '>')
		{
			ms->cmds->trunc = 1;
			if (txt[i + 1] == '>')
			{
				i++;
				ms->cmds->trunc = 0;
			}
			ms->cmds[index].outfiles[file_index] = get_outfile(txt, i);
			file_index++;
		}
		i++;
	}
}

//las comillas las ignora 💀
/*
c3r12s3:git-minishell sgil-moy$ <Makefile wc -w
      81
c3r12s3:git-minishell sgil-moy$ <"Makefil"e wc -w
      81
c3r12s3:git-minishell sgil-moy$ <"Make"file wc -w
      81
*/