#include "../mini_shell.h"

void	exit_child(t_mini_shell *ms)
{
	perror("error");
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	//close(pipex->fd_file_in);
	//close(pipex->fd_file_out);
	exit(1);
}

static int open_infiles(t_mini_shell *ms, int index)
{
	int i;
	int	fd;

	i = 0;
	while (ms->cmds[index].infiles[i])
	{
		fd = open(ms->cmds[index].infiles[i], O_RDONLY);
		if (fd == -1)
			exit_child(ms);
		close(fd);
		i++;
	}
	if (ms->cmds[index].here_doc == 0)
		fd = open(ms->cmds[index].infiles[i - 1], O_RDONLY);
	return(fd);	
}

static int open_outfiles(t_mini_shell *ms, int index)
{
	int i;
	int	fd;

	i = 0;
	while (ms->cmds[index].outfiles[i])
	{
		fd = open(ms->cmds[index].outfiles[i], O_RDONLY);
		if (fd == -1)
			exit_child(ms);
		close(fd);
		i++;
	}
	if (ms->cmds[index].trunc == 1)
		fd = open(ms->cmds[index].infiles[i - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(ms->cmds[index].infiles[i - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	return(fd);	
}

void	do_first_child(t_mini_shell *ms)
{
	int	fd_in = 0;
	int	fd_out = 0;

	if (ms->cmds[0].infiles != NULL || ms->cmds[0].here_doc == 1)
	{
		fd_in = open_infiles(ms, 0);
		if (ms->cmds[0].here_doc == 1)
			fd_in = ms->cmds[0].tuvo[0];
		dup2(fd_in, 0);
	}
	if (ms->cmds[0].outfiles != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
	}
	else
		dup2(ms->new_tubes[1], 1);
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(fd_in);
	close(fd_out);
	close(ms->cmds[0].tuvo[0]);
	close(ms->cmds[0].tuvo[1]);
	execve("/bin/ls", ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}

void	do_middle_child(t_mini_shell *ms, int child_index)
{
	int	fd_in = 0;
	int	fd_out = 0;

	if (ms->cmds[child_index].infiles != NULL || ms->cmds[child_index].here_doc == 1)
	{
		fd_in = open_infiles(ms, child_index);
		if (ms->cmds[child_index].here_doc == 1)
			fd_in = ms->cmds[child_index].tuvo[0];
		dup2(fd_in, 0);
	}
	else
		dup2(ms->old_tubes[0], 0);
	if (ms->cmds[child_index].outfiles != NULL)
	{
		fd_out = open_outfiles(ms, child_index);
		dup2(fd_out, 1);
	}
	else
		dup2(ms->new_tubes[1], 1);
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	close(ms->cmds[child_index].tuvo[0]);
	close(ms->cmds[child_index].tuvo[1]);
	close(fd_in);
	close(fd_out);
	execve("/bin/ls", ft_split(ms->cmds[child_index].cmd, ' '), ms->envp);
	exit_child(ms);
}

void	do_last_child(t_mini_shell *ms, int child_index)
{
	int	fd_in = 0;
	int	fd_out = 0;

	if (ms->cmds[child_index].infiles != NULL || ms->cmds[child_index].here_doc == 1)
	{
		fd_in = open_infiles(ms, child_index);
		if (ms->cmds[child_index].here_doc == 1)
			fd_in = ms->cmds[child_index].tuvo[0];
		dup2(fd_in, 0);
	}
	else
		dup2(ms->new_tubes[0], 0);
	if (ms->cmds[child_index].outfiles != NULL)
	{
		fd_out = open_outfiles(ms, child_index);
		dup2(fd_out, 1);
		close(fd_out);
	}
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->cmds[child_index].tuvo[0]);
	close(ms->cmds[child_index].tuvo[1]);
	close(fd_in);
	execve("/bin/ls", ft_split(ms->cmds[child_index].cmd, ' '), ms->envp);
	exit_child(ms);
//	if (create_file(pipex->argv[pipex->argc - 1], pipex) == 1)		exit_child(pipex);
//	if (get_vals(pipex->argv[pipex->argc - 2], pipex) == 1)		exit_child(pipex);
}
