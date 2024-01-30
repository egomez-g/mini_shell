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
		if (!ft_strncmp(str, ms->envp[i], ft_strlen(str) - 1) && \
		(ft_strlen(str) - 1 > 0))
		{
			aux = ft_split(ms->envp[i], '=');
			var = ft_strdup(aux[1]);
			free_strs(aux);
			return (var);
		}
		i++;
	}
	return (ft_strdup(""));
}

static char	*sust_var(char *txt, int i, char *var)
{
	char	*before;
	char	*after;
	int		len;
	char	*result;

	len = 0;
	before = ft_substr(txt, 0, i);
	while (txt[i + len] && !(txt[i + len] == ' ' || \
	(txt[i + len] <= 13 && txt[i + len] >= 9) || \
	txt[i + len] == '\'' || txt[i + len] == '\"'))
		len++;
	after = ft_substr(txt, i + len, ft_strlen(txt));
	result = ft_strdup(before);
	result = gnl_strjoin(result, var);
	result = gnl_strjoin(result, after);
	free(before);
	free(after);
	return (result);
}

char	*expand_variables(char *txt, t_mini_shell *ms)
{
	int		i;
	int		end;
	char	*substr;
	char	*var;

	i = 0;
	while (txt[i])
	{
		if (txt[i] == '\'' || txt[i] == '\"')
			i += skip_quotes(txt + i, txt[i]);
		if (txt[i] == '$' && !(txt[i + 1] && txt[i + 1] == '?'))
		{
			if ((txt[i + 1] && txt[i + 1] == '$'))
				i++;
			else
			{
				end = 0;
				while (txt[i + end] && !(txt[i + end] == ' ' || \
				(txt[i + end] <= 13 && txt[i + end] >= 9) || \
				txt[i + end] == '\'' || txt[i + end] == '\"'))
					end++;
				substr = gnl_substr(txt, i + 1, end);
				var = find_var(substr, ms);
				free(substr);
				txt = sust_var(txt, i, var);
			}
		}
		i++;
	}
	return (txt);
}
