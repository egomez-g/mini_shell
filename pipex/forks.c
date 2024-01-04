#include "../mini_shell.h"

int	first_fork(t_mini_shell *ms)
{
	ms->childs[0] = fork();
	if (ms->childs[0] == -1)
		return (1);
	if (ms->childs[0] == 0)
		do_first_child(ms);
	return (0);
}

int	loop_fork(t_mini_shell *ms, int child_index)
{
	ms->old_tubes[0] = ms->new_tubes[0];
	ms->old_tubes[1] = ms->new_tubes[1];
	if (pipe(ms->new_tubes) == -1)
		return (1);
	ms->childs[child_index] = fork();
	if (ms->childs[child_index] == -1)
		return (1);
	if (ms->childs[child_index] == 0)
		do_middle_child(ms, child_index);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	return (0);
}

int	last_fork(t_mini_shell *ms, int child_index)
{
	ms->childs[child_index] = fork();
	if (ms->childs[child_index] == -1)
		return (1);
	if (ms->childs[child_index] == 0)
		do_last_child(ms, child_index);
	return (0);
}

int	do_forks(t_mini_shell *ms)
{
	int		child_index;

	if (ms->num_cmds > 1)
	{
		child_index = 1;
		if (pipe(ms->new_tubes) == -1)
			return (1);
		if (first_fork(ms) == 1)
			return (1);
		while (child_index <= ms->num_cmds - 2)
		{
			if (loop_fork(ms, child_index) == 1)
				return (1);
			++child_index;
		}
		if (last_fork(ms, child_index) == 1)
			return (1);
		close(ms->new_tubes[0]);
		close(ms->new_tubes[1]);
		//ms->childs[ms->argc - 3] = -1;??????????????????
		return (0);
	}
	else
	{
		//do only one cmd w middle??
		//lo siento, no hablo peruano
		printf("esta entrando en el de un solo cmd\n");
		return (0);
	}
}
