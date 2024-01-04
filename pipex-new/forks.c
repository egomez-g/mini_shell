#include "../mini_shell.h"

static void one_fork(t_mini_shell *ms)
{
	ms->childs[0] = fork();
	if (ms->childs[0] == -1)
		return ;
	if (ms->childs[0] == 0)
		do_one_child(ms);
}

int	do_forks(t_mini_shell *ms)
{
	ms->childs = malloc(sizeof(pid_t *) * ms->num_cmds);
	if (ms->childs == NULL)
		return (1);
	if (ms->num_cmds == 1)
		one_fork(ms);

	return (1);
}