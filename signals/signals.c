#include "../mini_shell.h"

void  INThandler(int sig)
{
	signal(sig, SIG_IGN);
		exit(0);
}

//sigaction(SIGINT, const struct sigaction *restrict act,
//struct sigaction *restrict oldact);

/*
ctrl-c: sends SIGINT to interrupt them,
ctrl-\: sends SIGQUIT to kill them, -> no hacer nada
ctrl-z: sends SIGTSTP to suspend them.

Sometimes, all a handler has to do is set a flag 
and let the main program take care of processing 
the signal. The program will just have to periodically 
check the flag to know if any response is required.
*/
