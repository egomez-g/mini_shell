#include "../mini_shell.h"

int	do_builtins(char *txt, t_mini_shell *ms)
{
	char	**str;

	str = NULL;
	if (ft_strchr(txt, '|'))
		return (-1);
	str = ft_split(txt, ' ');
	if (!(ft_strcmp(str[0], "cd")))
		return (free_strs(str), do_cd(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "pwd")))
		return (free_strs(str), do_pwd(), 0);
	else if (!(ft_strcmp(str[0], "env")))
		return (free_strs(str), do_envp(ms), 0);
	else if (!(ft_strcmp(str[0], "export")))
		return (free_strs(str), do_export(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "unset")))
		return (free_strs(str), do_unset(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "echo")))
		return (free_strs(str), do_echo(txt, ms), 0);
	else if (!(ft_strcmp(str[0], "exit")))
		return (free_strs(str), do_exit(txt, ms), 0);
	free_strs(str);
	return (-1);
}
