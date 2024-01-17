#include "../mini_shell.h"

void do_pwd()
{
	char	*rute;

	rute = getcwd(NULL, 0);
	printf("%s\n", rute);
	free (rute);
}