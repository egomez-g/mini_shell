
#include "../mini_shell.h"


static int	strchr(char *str, int c)
{
	int i;

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

void find_lines(char *txt, char **envp)
{
	int start;
	int end;
	char *str;
	pid_t			child;

	start = 0;
	end = 0;
	while (strchr(txt + start, ';') != -1)
	{
		end = strchr(txt + start, ';');
		str = gnl_substr(txt, start, end);
		start += end + 1;
		child = fork();
		if (child == 0)
			parse(str, envp);
		free(str);
		waitpid(child, NULL, 0);
	}
	child = fork();
	if (child == 0)
		parse(txt + start, envp);
	waitpid(child, NULL, 0);
}