#include "mini_shell.h"

void leaks()
{
	system("leaks -q mini_shell");
}

int	main(int argc, char **argv, char **envp)
{
	char			*txt;
	pid_t			child;

	argc = 0;
	argv = NULL;
	//atexit(leaks);
	while (1)
	{
		//reset_args(&ms, envp);
		txt = readline("minishell>");
		if (txt)
		{
			if (ft_strncmp(txt, "exit\0", ft_strlen(txt)) == 0)
			{
				//habra que hacer un free de lo que haga falta xdxd no tiene gracia
				exit (1);
			}
			child = fork();
			if (child == 0)
				parse(txt, envp);
		}
		free (txt);
		waitpid(child, NULL, 0);
		//if (!pipex(&ms))
			//printf("ha salio mal\n");
	}
}