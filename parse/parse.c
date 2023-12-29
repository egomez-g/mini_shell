#include "../mini_shell.h"

static void init_struct(t_mini_shell *ms)
{
	int	i;

	i = 0;
	ms->cmds = NULL;
	while (i < ms->num_cmds)
	{
		new_list(ms);
		i++;
	}
}
static void	fill_struct(char *txt, t_mini_shell *ms)
{
	ms->infile = NULL;
	find_infile(txt, ms);
	/*
	encontrar infile
	encontrar cmd y flags
	encontrar outfile
	*/
}

static void	cmd_count(char *str, t_mini_shell *ms)
{
	ms->num_cmds = 1;
	if (!str)
		return (perror(""));
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
	init_struct(&ms);
	fill_struct(txt, &ms);
	/*
	haces las estructuras
	rellenas las estructuras
	se lo pasas al pipex
	*/
	printf("Infile: %s\n", ms.infile);
	exit (0);
}
