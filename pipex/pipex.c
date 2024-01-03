#include "../mini_shell.h"

void	close_parent(t_mini_shell *ms)
{
	int	i;

	i = 0;
	while (ms->childs[i] != -1)
	{
		waitpid(ms->childs[i], NULL, 0);
		++i;
	}
	//close(ms->fd_file_in);
	//close(ms->fd_file_out);
}

int	pipex(t_mini_shell *ms)
{
	if (do_forks(ms) == 1)
		exit(1);

	close (ms->new_tubes[0]);
	close_parent(ms);

	free(ms->childs);
	exit(0);
}
