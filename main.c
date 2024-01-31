#include "mini_shell.h"

void	leaks(void)
{
	system("leaks -q mini_shell");
}

int	main(int argc, char **argv, char **envp)
{
	t_mini_shell	ms;
	char			*txt;

	argv = NULL;
	copy_envp(envp, &ms);
	ms.status = 0;
	//signal(SIGQUIT, int_handler);
	//signal(SIGINT, int_handler);
	if (argc > 1)
	{
		printf("🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬minishell> Too many arguments🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬\n");
		exit(1);
	}
	while (1)
	{
		txt = readline("🤬minishell> ");
		if (!txt)
			break;
		if (*txt != '\0')
		{
			add_history(txt);
			find_lines(txt, &ms);
		}
	}
	leaks();
	exit (0);
}
