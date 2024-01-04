#include "../mini_shell.h"

void	do_one_child(t_mini_shell *ms)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (ms->cmds[0].infiles != NULL || ms->cmds[0].here_doc == 1)
	{
		fd_in = open_infiles(ms, 0);
		if (ms->cmds[0].here_doc == 1)
			fd_in = ms->cmds[0].tuvo[0];
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (ms->cmds[0].outfiles != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
		close(fd_out);
	}

	close(ms->cmds[0].tuvo[0]);
	close(ms->cmds[0].tuvo[1]);

	//si no lo encuentra pasarselo igualmente¿?
	find_path(ms, 0);

	//free split???
	execve(ms->cmds[0].path, ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}
