#include "../mini_shell.h"

int	first_fork(t_mini_shell *ms, pid_t child)
{
	child = fork();
	if (child == -1)
		return (1);
	if (child == 0)
	{
		ms->childs[0] = child;
		do_first_child(ms);
	}
	return (0);
}

int	loop_fork(t_pipex *pipex, pid_t *child, char *argv, int *child_index)
{
	pipex->old_tubes[0] = pipex->new_tubes[0];
	pipex->old_tubes[1] = pipex->new_tubes[1];
	if (pipe(&pipex->new_tubes[2]) == -1)
		return (1);
	*child = fork();
	if (*child == -1)
		return (1);
	if (*child == 0)
	{
		pipex->childs[*child_index] = *child;
		do_middle_child(pipex, argv);
	}
	close(pipex->old_tubes[0]);
	close(pipex->old_tubes[1]);
	return (0);
}

int	last_fork(t_pipex *pipex, pid_t *child, int *child_index)
{
	*child = fork();
	if (*child == -1)
		return (1);
	if (*child == 0)
	{
		pipex->childs[*child_index] = *child;
		do_last_child(pipex);
	}
	return (0);
}

int	do_forks(t_mini_shell *ms)
{
	pid_t	child;
	int		child_index;

	if (ms->num_cmds > 1)
	{
		child_index = 1;
		if (pipe(ms->new_tubes) == -1)
			return (1);
		if (first_fork(ms, &child) == 1)
			return (1);
		while (child_index < ms->num_cmds - 2)
		{
			if (loop_fork(ms, &child, ms->argv[ms->arg_i], &child_index) == 1)
				return (1);
			ms->childs[child_index] = child;
			++child_index;
		}
		if (last_fork(ms, &child, &child_index) == 1)
			return (1);
		close(ms->new_tubes[0]);
		close(ms->new_tubes[1]);
		ms->childs[ms->argc - 3] = -1;
		return (0);
	}
	else
	{
		//do only one cmd w middle??
	}
}
