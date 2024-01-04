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
void pipex (t_mini_shell *ms)
{
	if (do_forks(ms) == 1)
		exit(1);

	waitpid(-1, NULL, 0);
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	free(ms->childs);
	exit(0);
}