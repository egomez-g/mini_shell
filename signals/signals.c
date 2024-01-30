#include "../mini_shell.h"


void	int_handler(int sig)
{
	printf("SIG: %d\n", sig);
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
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

// void	quit_handler(int sig)
// {
// 	(void)sig;
// 	//rl_replace_line("", 0);
// }


//sigaction(SIGINT, const struct sigaction *restrict act,
//struct sigaction *restrict oldact);

/*
ctrl-c: sends SIGINT to interrupt them,
ctrl-\: sends SIGQUIT to kill them, -> no hacer nada
ctrl-d: sends SIGTSTP to suspend them.

Sometimes, all a handler has to do is set a flag 
and let the main program take care of processing 
the signal. The program will just have to periodically 
check the flag to know if any response is required.
*/
