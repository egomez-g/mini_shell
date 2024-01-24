#include "../mini_shell.h"

int	ft_valid_name_char(int c)
{
	if ((c != '!' && c != '?' && c != '<' && c != '>' && \
	c != '(' && c != ')' && c != '&' && c <= 126 && c >= 33) || \
	c == -61 || c == -111 || c == -79)
		return (1);
	else
		return (0);
}

static void	quote_count(char *txt)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (txt[i])
	{
		if (txt[i] == '\"')
			double_quote++;
		else if (txt[i] == '\'')
			single_quote++;
		i++;
	}
	if (single_quote % 2 != 0 || double_quote % 2 != 0)
	{
		perror("Error");//que se quede pillado o algo
		exit (1);
	}
}

static void	fill_struct(char *txt, t_mini_shell *ms)
{
	int		i;
	int		j;
	char	*newtxt;

	i = 0;
	quote_count(txt);
	newtxt = expanad_variables(txt, ms);
	//new_txt = manage_quotes(txt);
	find_infile(newtxt, ms);
	find_outfile(newtxt, ms);
	find_cmd(newtxt, ms);
	while (i < ms->num_cmds)
	{
		j = 0;
		printf("CMD: %s\n", ms->cmds[i].cmd);
		while (ms->cmds[i].infiles[j])
		{
			printf("INFILE: %s\n", ms->cmds[i].infiles[j]);
			j++;
		}
		j = 0;
		while (ms->cmds[i].outfiles[j])
		{
			printf("OUTFILE: %s\n", ms->cmds[i].outfiles[j]);
			j++;
		}
		printf("______________________________\n\n");
		i++;
	}
}

static void	cmd_count(char *str, t_mini_shell *ms)
{
	ms->num_cmds = 1;
	if (!str)
		return (perror("Error"));
	while (*str)
	{
		if (*str == '|' || *str == ';')
			ms->num_cmds++;
		str++;
	}
}

void	parse(char *txt, t_mini_shell *ms)
{
	cmd_count(txt, ms);
	ms->cmds = malloc (sizeof(t_cmds) * ms->num_cmds);
	if (!ms->cmds)
		return ;
	fill_struct(txt, ms);
	pipex(ms);
	exit (ms->status);
}
