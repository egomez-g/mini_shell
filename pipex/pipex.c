#include "../mini_shell.h"

void	close_parent(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->childs[i] != -1)
	{
		waitpid(pipex->childs[i], NULL, 0);
		++i;
	}
	close(pipex->fd_file_in);
	close(pipex->fd_file_out);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.envp = envp;
	pipex.argc = argc;
	pipex.argv = argv;
//	if (manage_input(&pipex) == 1)		exit(1);
	if (do_forks(&pipex) == 1)
		exit(1);
	close (pipex.new_tubes[0]);
	close_parent(&pipex);
	if (pipex.here_doc == 1)
		unlink("here_doc");
	free(pipex.childs);
	exit(0);
}
