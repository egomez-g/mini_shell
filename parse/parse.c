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
	int	single_quote;

	single_quote = 0;
	while (*txt)
	{
		if (*txt == '\'' || *txt == '\"')
			single_quote++;
		txt++;
	}
	if (single_quote % 2 != 0)
	{
		perror("Error");
		exit (1);
	}
}

static void	fill_struct(char *txt, t_mini_shell *ms)
{
	int	i;
	int	j;

	quote_count(txt);
	find_infile(txt, ms);
	find_outfile(txt, ms);
	find_cmd(txt, ms);
	i = 0;
	while (i < ms->num_cmds)
	{
		printf("CMD: %s\n", ms->cmds[i].cmd);
		j = 0;
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
//wc Makefile
//	46	94	729 Makefile
//wc<Makefile
//	46	94	729

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
	//if (!ft_strncmp(txt, "cd", 2) && ms->num_cmds < 2)
	//	exit(0);
	pipex(ms);
	exit (ms->status);
}
//checkea el heredoc para los tuboss