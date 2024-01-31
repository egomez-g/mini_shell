#include "../mini_shell.h"

void	int_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n🤬minishell> ", 16);
		
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGILL)
		exit(0);
}

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
	exit(0);
}
