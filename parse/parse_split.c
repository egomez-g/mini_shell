#include "../mini_shell.h"

static int	strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	if (str[i] == (char)c)
		return (i);
	return (-1);
}

void	find_lines(char *txt, t_mini_shell *ms)
{
	int		start;
	int		end;
	char	*str;
	pid_t	child;

	start = 0;
	end = 0;
	if (manage_quotes(txt, ms) == 1)
		return ;
	while (strchr(txt + start, ';') != -1)
	{
		end = strchr(txt + start, ';');
		str = gnl_substr(txt, start, end);
		start += end + 1;
		if (do_builtins(str, ms) == -1)
		{
			child = fork();
			if (child == 0)
				parse(str, ms);
		}
		free(str);
		waitpid(child, &ms->status, 0);
		if (txt)
			free(txt);
	}
	if (do_builtins(txt + start, ms) == -1)
	{
		child = fork();
		if (child == 0)
			parse(txt + start, ms);
		free(txt);
		waitpid(child, &(ms->status), 0);
	}
}
