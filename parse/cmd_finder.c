#include "../mini_shell.h"

void	get_cmd(char *txt, t_mini_shell *ms, int index, int *i)
{
	int		end;
	char	*aux;

	end = 0;
	while (txt[*i + end] && (ft_valid_name_char(txt[*i + end]) || \
	txt[*i + end] == '-'))
		++end;
	if (ms->cmds[index].cmd != NULL)
		ms->cmds[index].cmd = gnl_strjoin(ms->cmds[index].cmd, " ");
	aux = gnl_substr(txt, *i, end);
	ms->cmds[index].cmd = gnl_strjoin(ms->cmds[index].cmd, aux);
	free(aux);
	*i += end;
}

void	skip_spaces(char *txt, int *i)
{
	while (txt[*i] && (txt[*i] == ' ' || (txt[*i] <= 13 && txt[*i] >= 9)))
		*i += 1;
}

void	skip_word(char *txt, int *i)
{
	while (txt[*i] && (txt[*i] != ' ' && !(txt[*i] <= 13 && txt[*i] >= 9)))
		*i += 1;
}

void	skip_file(char *txt, int *i)
{
	*i += 1;
	if (txt[*i] && ft_valid_name_char(txt[*i]))
	{
		while (ft_valid_name_char(txt[*i]))
			*i += 1;
		return ;
	}
	else if (txt[*i] && (txt[*i] == ' ' || (txt[*i] <= 13 && txt[*i] >= 9)))
	{
		skip_spaces(txt, i);
		while (ft_valid_name_char(txt[*i]))
			*i += 1;
	}
}

void	find_cmd(char *txt, t_mini_shell *ms)
{
	int	index;
	int	i;

	i = 0;
	index = 0;
	while (i < ms->num_cmds)
	{
		ms->cmds[i].cmd = NULL;
		i++;
	}
	i = 0;
	while (txt[i])
	{
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
		if (txt[i] == '|' || txt[i] == ';')
		{
			index++;
			i++;
		}
		else if (txt[i] == '<' || txt[i] == '>')
			skip_file(txt, &i);
		else if (ft_valid_name_char(txt[i]) || txt[i] == '-')
			get_cmd(txt, ms, index, &i);
		else if (txt[i] == ' ' || (txt[i] <= 13 && txt[i] >= 9))
			skip_spaces(txt, &i);
		else
		{
			skip_word(txt, &i);
			txt++;
		}
	}
}
