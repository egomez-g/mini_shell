#include "../mini_shell.h"

static void	open_files(int *fd_in, t_mini_shell *ms)
{
	*fd_in = open_infiles(ms, 0);
	if (ms->cmds[0].here_doc == 1)
	{
		*fd_in = ms->cmds[0].tuvo[0];
		dup2(*fd_in, 0);
		close(ms->cmds[0].tuvo[0]);
		close(ms->cmds[0].tuvo[1]);
	}
	else
		dup2(*fd_in, 0);
	close(*fd_in);
}

char	**splited_cmd(char *txt)
{
	char **result;

	result = (char **)malloc(3 * sizeof(char**));
	if (!result)
		return (NULL);
	result[0] = ft_strdup("awk");
	result[1] = ft_substr(txt, 3, ft_strlen(txt));
	result[2] = NULL;
	return (result);
}

void	do_one_child(t_mini_shell *ms)
{
	int		fd_in;
	int		fd_out;
	//char	**aux;
	int		i;

	i = 0;
	fd_in = 0;
	fd_out = 0;
	find_path(ms, 0);
	if (ms->cmds[0].infiles[0] != NULL || ms->cmds[0].here_doc == 1)
		open_files(&fd_in, ms);
	if (ms->cmds[0].outfiles[0] != NULL)
	{
		fd_out = open_outfiles(ms, 0);
		dup2(fd_out, 1);
		close(fd_out);
	}
	//dprintf(1, "cmd[0] = %s\n", ms->cmds[0].cmd);
	//if (ft_strchr(ms->cmds[0].cmd, '\'') || ft_strchr(ms->cmds[0].cmd, '\"'))
	//{
	//	dprintf(1, "kekekekekekekekekek\n");
	//	aux = ft_split(ms->cmds[0].cmd, '\'');
	//	skip_spaces(aux[0], &i);
	//	aux[0] = aux[0] + i;
	//	i = 0;
	//	skip_spaces(aux[2], &i);
	//	aux[2] = aux[2] + i;
	//	execve(ms->cmds[0].path, aux, ms->envp);
	//}
	//else
		execve(ms->cmds[0].path, ft_split(ms->cmds[0].cmd, ' '), ms->envp);
	exit_child(ms);
}

