#include "../mini_shell.h"

void	do_one_child(t_mini_shell *ms)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (ms->cmds[0].infiles[0] != NULL || ms->cmds[0].here_doc == 1)
	{
		fd_in = open_infiles(ms, 0);
		if (ms->cmds[0].here_doc == 1)
		{
			fd_in = ms->cmds[0].tuvo[0];
			close(ms->cmds[0].tuvo[0]);
			close(ms->cmds[0].tuvo[1]);
		}
		dup2(fd_in, 0);
	}
	if (ms->cmds[0].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
		close(fd_out);
	}
	find_path(ms, 0);
	execve(ms->cmds[0].path, ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}