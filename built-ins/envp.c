#include "../mini_shell.h"

void	do_envp(t_mini_shell *ms)
{
	int i;

	i = 0;
	while (ms->envp[i])
	{
		printf("%s\n",ms->envp[i]);
		++i;
	}
}