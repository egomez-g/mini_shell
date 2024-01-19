#include "../mini_shell.h"

void	do_exit(char *txt, t_mini_shell *ms)
{
	int		i;
	char	**str;

	i = 0;
	str = ft_split(txt, ' ');
	while (str[i])
		i++;
	if (i > 2)
	{
		printf("mini_shell> exit: too many arguments\n");
		return (free_strs(str));
	}
	if (!str[1])
		exit(ms->status);
	i = 0;
	while (str[1][i])
	{
		if (!(str[1][i] >= '0' && str[1][i] <= '9'))
		{
			printf("exit: %s: numeric argument required\n", str[1]);
			exit (255);
		}
		i++;
	}
	exit (ft_atoi(str[1]));
}
