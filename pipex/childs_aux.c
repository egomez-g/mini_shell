#include "../mini_shell.h"

void	exit_child(t_mini_shell *ms)
{
	perror("error");
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	exit(127);
}
//close(pipex->fd_file_in);
//close(pipex->fd_file_out);

void	manage_fd_in(int *fd_in, t_mini_shell *ms, int child_index)
{
	*fd_in = open_infiles(ms, child_index);
	if (ms->cmds[child_index].here_doc == 1)
	{
		*fd_in = ms->cmds[child_index].tuvo[0];
		dup2(*fd_in, 0);
		close(ms->cmds[child_index].tuvo[0]);
		close(ms->cmds[child_index].tuvo[1]);
	}
	else
		dup2(*fd_in, 0);
	close(*fd_in);
}
