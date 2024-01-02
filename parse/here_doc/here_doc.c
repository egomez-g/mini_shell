#include "../../mini_shell.h"

void	heredoc(char *limitador, t_mini_shell *ms, int index)
{
	char	*buff;

	pipe(ms->cmds[index].tuvo);
	close(ms->cmds[index].tuvo[0]);
	while (1)
	{
		buff = readline("here_doc>");
		if (buff == NULL || !ft_strncmp(limitador, buff, ft_strlen(limitador)))
			break ;
		write(ms->cmds[index].tuvo[1], buff, ft_strlen(buff));
		free(buff);
	}
	free(buff);
	close(ms->cmds[index].tuvo[1]);
	ms->cmds[index].fd_in = open("here_doc", O_RDONLY);
}
