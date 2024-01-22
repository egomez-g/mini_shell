#include "../mini_shell.h"

char	*remove_quotes(char *txt)
{
	int		i;
	char	*new_txt;
	char	**aux;
	
	i = 1;
	aux = ft_split(txt, '\"');
	new_txt = ft_strdup(aux[0]);
	while (aux[i])
	{
		new_txt = gnl_strjoin(new_txt, aux[i]);
		i++;
	}
	free_strs(aux);
	free(txt);
	return (new_txt);
}
