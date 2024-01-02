#include "../mini_shell.h"

void	parser_cmd(char *txt, t_mini_shell *ms)
{
	int		i;
	int		index;
	char	**cmd_str;

	cmd_str = ft_split(txt, ' ');
	index = 0;
	i = 0;

	while (cmd_str[i])
	{
		if (ft_strncmp(cmd_str[i], "|", 1) == 0)
			index++;
		else if (ft_strncmp(cmd_str[i], "<", 1) == 0 || ft_strncmp(cmd_str[i], ">", 1) == 0)
		{
			if(ft_strlen(cmd_str[i]) == 1)
				i++;
		}
		else
			ms->cmds[index].cmd = gnl_strjoin(ms->cmds[index].cmd, cmd_str[i]);
		i++;
	}
	i = 0;
	while (cmd_str[i])
	{
		free(cmd_str[i]);
		i++;
	}
	free(cmd_str);
}
