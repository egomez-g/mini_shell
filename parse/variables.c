#include "../mini_shell.h"

static char	*find_var(char *str, t_mini_shell *ms)
{
	int		i;
	char	**aux;
	char	*var;

	i = 0;
	var = NULL;
	while (ms->envp[i])
	{
		if (!ft_strncmp(str, ms->envp[i], ft_strlen(str) - 1))
		{
			aux = ft_split(ms->envp[i], '=');
			var = ft_strdup(aux[1]);
			free_strs(aux);
		}
		i++;
	}
	return (var);
}

static char	*sust_var(char *txt, int i, char *var)
{
	char	*before;
	char	*after;
	int		len;
	char	*result;

	len = 0;
	before = gnl_substr(txt, 0, i);
	while (txt[i + len] && !(txt[i + len] == ' ' || \
	(txt[i + len] <= 13 && txt[i + len] >= 9)))
		len++;
	after = gnl_substr(txt, i + len, ft_strlen(txt));
	result = ft_strdup(before);
	result = gnl_strjoin(result, var);
	result = gnl_strjoin(result, after);
	free(before);
	free(after);
	return (result);
}

char	*expanad_variables(char *txt, t_mini_shell *ms)
{
	int		i;
	int		end;
	char	*substr;
	char	*var;
	char	*new_txt;

	i = 0;
	new_txt = txt;
	while (txt[i])
	{
		if (txt[i] == '$' && !(txt[i + 1] && txt[i + 1] == '?'))//esto esta raro creo????
		{
			end = 0;
			while (txt[i + end] && !(txt[i + end] == ' ' || \
			(txt[i + end] <= 13 && txt[i + end] >= 9)))
				end++;
			substr = ft_substr(txt, i + 1, end);
			var = find_var(substr, ms);
			free(substr);
			if (var)
				new_txt = sust_var(txt, i, var);
		}
		i++;
	}
	return (new_txt);
}
