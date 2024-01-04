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
}

void	pipex(t_mini_shell *ms)
{
	ms->childs = malloc(sizeof(pid_t *) * ms->num_cmds);
	if (ms->childs == NULL)
		exit (1);
	if (do_forks(ms) == 1)
		exit(1);

	close (ms->new_tubes[0]);
	close_parent(ms);

	free(ms->childs);
	exit(0);
}
