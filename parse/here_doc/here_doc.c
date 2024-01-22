#include "../../mini_shell.h"

void	heredoc(char *limitador, t_mini_shell *ms, int index)
{
	char	*buff;

	pipe(ms->cmds[index].tuvo);
	while (1)
	{
		buff = readline("here_doc>");
		if (buff == NULL || (!ft_strncmp(limitador, buff, ft_strlen(buff)) && \
		!ft_strncmp(limitador, buff, ft_strlen(limitador))))
			break ;
		write(ms->cmds[index].tuvo[1], buff, ft_strlen(buff));
		write(ms->cmds[index].tuvo[1], "\n", 1);
		free(buff);
	}
	free(buff);
	close(ms->cmds[index].tuvo[1]);
}
