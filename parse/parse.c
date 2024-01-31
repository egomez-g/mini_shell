#include "../mini_shell.h"

int	ft_valid_name_char(int c)//esto dentro del awk
{
	if ((c != '<' && c != '>' && \
	c != '(' && c != ')' && c != '&' && c <= 126 && c >= 33) || \
	c == -61 || c == -111 || c == -79)
		return (1);
	else
		return (0);
}

static void	fill_struct(char *txt, t_mini_shell *ms)
{
	char	*newtxt;

	newtxt = expand_variables(txt, ms);
	find_infile(newtxt, ms);
	find_outfile(newtxt, ms);
	find_cmd(newtxt, ms);
	//free(newtxt);
}

static void	cmd_count(char *str, t_mini_shell *ms)
{
	ms->num_cmds = 1;
	if (!str)
		return (perror("Error"));
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			str += skip_quotes(str, *str);
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
