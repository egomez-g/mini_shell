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
		txt = readline("minishell>");
		if (txt)
		{
			if (ft_strncmp(txt, "exit\0", 5) == 0)
			{
				exit (1);
			}
			child = fork();
			if (child == 0)
				parse(txt, envp);
			free (txt);
		}
		waitpid(child, NULL, 0);
	}
}