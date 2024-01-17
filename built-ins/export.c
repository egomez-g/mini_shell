#include "../mini_shell.h"

static void add_vars(char ***new_envp, int len, char **txt)
{
	int i;

	i = 0;
	while (txt[i])
	{
		if (ft_strchr(txt[i], '='))
		{
			(*new_envp)[len] = ft_strdup(txt[i]);
			len++;
		}
		i++;
	}
	(*new_envp)[len] = NULL;
}

static	char** malloc_vars(int count, char **txt, t_mini_shell *ms)
{
	int	len;
	char **new_envp;

	len = 0;
	while(ms->envp[len])
		len++;
	new_envp = (char**)malloc(sizeof(char*) * (len + count + 1));
	if (!new_envp)
		return (NULL);
	len = 0;
	while (ms->envp[len])
	{
		new_envp[len] = ft_strdup(ms->envp[len]);
		len++;
	}
	add_vars(&new_envp, len, txt);
	free_strs(ms->envp);
	return (new_envp);
}

void	do_export(char *txt, t_mini_shell *ms)
{
	char	**var_env;
	int		i;
	int		count;

	i = 0;
	count = 0;
	var_env = ft_split(txt, ' ');
	while (var_env[i])
	{
		if (ft_strchr(var_env[i], '='))
			count++;
		i++;
	}
	ms->envp = malloc_vars(count, var_env, ms);
	free_strs(var_env);
}
