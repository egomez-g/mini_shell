
#include "../mini_shell.h"

int	open_infiles(t_mini_shell *ms, int index)
{
	int	i;
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
	return (fd);
}

int	open_outfiles(t_mini_shell *ms, int index)
{
	int	i;
	int	fd;

	i = 0;
	while (ms->cmds[index].outfiles[i])
	{
		fd = open(ms->cmds[index].outfiles[i], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			exit_child(ms);
		close(fd);
		i++;
	}
	if (ms->cmds[index].trunc == 1)
	{
		fd = open(ms->cmds[index].outfiles[i - 1], \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else
		fd = open(ms->cmds[index].outfiles[i - 1], \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	return (fd);
}

void	do_first_child(t_mini_shell *ms)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (ms->cmds[0].infiles[0] != NULL || ms->cmds[0].here_doc == 1)
		manage_fd_in(&fd_in, ms, 0);
	if (ms->cmds[0].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
		close(fd_out);
	}
	else
		dup2(ms->new_tubes[1], 1);
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	find_path(ms, 0);
	execve(ms->cmds[0].path, ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}

void	do_middle_child(t_mini_shell *ms, int child_index)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (ms->cmds[child_index].infiles[0] || ms->cmds[child_index].here_doc)
		manage_fd_in(&fd_in, ms, child_index);
	else
		dup2(ms->old_tubes[0], 0);
	if (ms->cmds[child_index].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, child_index);
		dup2(fd_out, 1);
		close(fd_out);
	}
	else
		dup2(ms->new_tubes[1], 1);
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	close(ms->old_tubes[0]);
	close(ms->old_tubes[1]);
	find_path(ms, child_index);
	execve(ms->cmds[child_index].path, ft_split(ms->cmds[child_index].cmd, ' '), \
	ms->envp);
	exit_child(ms);
}

void	do_last_child(t_mini_shell *ms, int child_index)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 0;
	if (ms->cmds[child_index].infiles[0] != NULL || \
	ms->cmds[child_index].here_doc == 1)
		manage_fd_in(&fd_in, ms, child_index);
	else
		dup2(ms->new_tubes[0], 0);
	if (ms->cmds[child_index].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, child_index);
		dup2(fd_out, 1);
		close(fd_out);
	}
	close(ms->new_tubes[0]);
	close(ms->new_tubes[1]);
	find_path(ms, child_index);
	execve(ms->cmds[child_index].path, ft_split(ms->cmds[child_index].cmd, ' '), \
	ms->envp);
	exit_child(ms);
}
