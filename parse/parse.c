#include "../mini_shell.h"

static void	quote_count(char *txt)
{
	int	single_quote;

	single_quote = 0;
	while(*txt)
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

	quote_count(txt);
	find_infile(txt, ms);
	find_outfile(txt, ms);
	parser_cmd(txt, ms);
	i = 0;
	while (i < ms->num_cmds)
	{
		printf("CMD: %s\n", ms->cmds[i].cmd);
		printf("INFILE: %s\n", ms->cmds[i].infile);
		printf("OUTFILE: %s\n", ms->cmds[i].outfile);
		i++;
	}
	//ls <infile wtf? el codigo funciona a veces si, a veces no. GOD
}

static void	cmd_count(char *str, t_mini_shell *ms)
{
	ms->num_cmds = 1;
	if (!str)
		return (perror("Error"));
	while (*str)
	{
		if (*str == '|')
			ms->num_cmds++;
		str++;
	}
}

void	parse(char* txt, char **envp)
{
	t_mini_shell ms;

	ms.envp = envp;
	cmd_count(txt, &ms);
	ms.cmds = malloc (sizeof(t_cmds) * ms.num_cmds);
	if (!ms.cmds)
		return ;
	fill_struct(txt, &ms);
	/*
	haces las estructuras
	rellenas las estructuras
	se lo pasas al pipex
	*/
//	pipex(int argc, char **argv, char **envp)
//	printf("Infile: %s\n", ms.infile);
	exit (0);
}
