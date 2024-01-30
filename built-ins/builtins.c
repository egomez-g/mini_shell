#include "../mini_shell.h"

int	do_builtins(char *txt, t_mini_shell *ms)
{
	char	**str;
	char	*aux;
	
	aux = expand_variables(txt, ms);
	aux = clean_quotes(aux, ms);
	str = ft_split(aux, ' ');
	if (!str[0] || ft_strchr(aux, '|'))
		return (free_strs(str), -1);
	if (!(ft_strcmp(str[0], "cd")))
		return (free_strs(str), do_cd(aux, ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "pwd")))
		return (free_strs(str), do_pwd(), free(aux), 0);
	else if (!(ft_strcmp(str[0], "env")))
		return (free_strs(str), do_envp(ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "export")))
		return (free_strs(str), do_export(aux, ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "unset")))
		return (free_strs(str), do_unset(aux, ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "echo")))
		return (free_strs(str), do_echo(aux, ms), free(aux), 0);
	else if (!(ft_strcmp(str[0], "exit")))
		return (free_strs(str), do_exit(aux, ms), free(aux), 0);
	return (free_strs(str), -1);
}
