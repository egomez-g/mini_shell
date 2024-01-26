#include "../mini_shell.h"

static void	open_files(int *fd_in, t_mini_shell *ms)
{
	*fd_in = open_infiles(ms, 0);
	if (ms->cmds[0].here_doc == 1)
	{
		*fd_in = ms->cmds[0].tuvo[0];
		dup2(*fd_in, 0);
		close(ms->cmds[0].tuvo[0]);
		close(ms->cmds[0].tuvo[1]);
	}
	else
		dup2(*fd_in, 0);
	close(*fd_in);
}

void	do_one_child(t_mini_shell *ms)
{
	int		fd_in;
	int		fd_out;
	char	**aux;
	int		i;

	i = 0;
	fd_in = 0;
	fd_out = 0;
	find_path(ms, 0);
	if (ms->cmds[0].infiles[0] != NULL || ms->cmds[0].here_doc == 1)
		open_files(&fd_in, ms);
	if (ms->cmds[0].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
		close(fd_out);
	}
	if (ms->cmds[0].awk)
	{
		aux = ft_split(ms->cmds[0].cmd, '\'');
		skip_spaces(aux[0], &i);
		aux[0] = aux[0] + i;
		i = 0;
		skip_spaces(aux[2], &i);
		aux[2] = aux[2] + i;
		execve(ms->cmds[0].path, aux, ms->envp);
	}
	else
		execve(ms->cmds[0].path, ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}
