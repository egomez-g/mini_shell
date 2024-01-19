#include "../mini_shell.h"

void	do_pwd(void)
{
	char	*rute;

	rute = getcwd(NULL, 0);
	printf("%s\n", rute);
	free (rute);
}
