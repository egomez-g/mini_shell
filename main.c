#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*txt;
	t_mini_shell	ms;

	argc = 0;
	argv = NULL;
	while (1)
	{
		//reset_args(&ms, envp);
		txt = readline("minishell>");
		if (txt)
			if (ft_strncmp(txt, "exit\0", ft_strlen(txt)) == 0)
			{
				//habra que hacer un free de lo que haga falta xdxd no tiene gracia
				exit (1);
			}
		parse(txt, &ms);
		//if (!pipex(&ms))
			//printf("ha salio mal\n");
	}
}