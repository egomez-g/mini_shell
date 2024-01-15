#include "mini_shell.h"

void leaks()
{
	system("leaks -q mini_shell");
}

int	main(int argc, char **argv, char **envp)
{
	char			*txt;

	argc = 0;
	argv = NULL;
	//atexit(leaks);
	while (1)
	{
		txt = readline("minishell>");
		if (txt)
		{
			if (ft_strncmp(txt, "exit\0", 5) == 0)
				exit (1);
			add_history(txt);
			find_lines(txt, envp);
			free (txt);
		}
	}
}