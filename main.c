#include "mini_shell.h"

void	leaks(void)
{
	system("leaks -q mini_shell");
}

int	main(int argc, char **argv, char **envp)
{
	t_mini_shell	ms;
	char			*txt;

	argc = 0;
	argv = NULL;
	copy_envp(envp, &ms);
	atexit(leaks);
	ms.status = 0;
	if (argc > 1)
	{
		printf("minishell> Too many arguments\n");
		exit(1);
	}
	while (1)
	{
		txt = readline("minishell> ");
		signal(SIGINT, int_handler);
		if (txt && *txt != '\0')
		{
			add_history(txt);
			find_lines(txt, &ms);
			//free (txt);
		}
	}
}
