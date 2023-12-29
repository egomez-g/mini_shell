#include "../mini_shell.h"

void	new_list(t_mini_shell *ms)
{
	t_cmds	*new_cmd;
	t_cmds	*last_cmd;

	new_cmd = malloc (sizeof(t_cmds));
	if (!new_cmd)
		return ;
	new_cmd->outfile = NULL;
	new_cmd->next = NULL;
	if (!ms->cmds)
		ms->cmds = new_cmd;
	else
	{
		last_cmd = ms->cmds;
		while (last_cmd->next)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
	}
}
