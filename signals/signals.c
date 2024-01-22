#include "../mini_shell.h"

void	signals(int sig)
{
	sig = 0;
	printf("asdasdasdasdasdasdasd\n");
}
//sigaction(SIGINT, const struct sigaction *restrict act,
//struct sigaction *restrict oldact);

/*
ctrl-c: sends SIGINT to interrupt them,
ctrl-\: sends SIGQUIT to kill them,
ctrl-z: sends SIGTSTP to suspend them.

Sometimes, all a handler has to do is set a flag 
and let the main program take care of processing 
the signal. The program will just have to periodically 
check the flag to know if any response is required.
*/
