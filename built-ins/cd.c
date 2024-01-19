#include "../mini_shell.h"

static void	reset_pwd(char **var, char *new_pwd, char *old_pwd)
{
	if (ft_strncmp(*var, "PWD=", 4) == 0)
	{
		free(*var);
		*var = ft_strjoin("PWD=", new_pwd);
	}
	if (ft_strncmp(*var, "OLDPWD=", 7) == 0)
	{
		free(*var);
		*var = ft_strjoin("OLDPWD=", old_pwd);
	}
}

static void	change_pwd(t_mini_shell *ms, char *new_pwd)
{
	int		i;
	char	*old_pwd;

	i = 0;
	old_pwd = NULL;
	while (ms->envp[i])
	{
		if (old_pwd == NULL)
		{
			if (ft_strncmp(ms->envp[i], "PWD=", 4) == 0)
			{
				old_pwd = ft_substr(ms->envp[i], 4, ft_strlen(ms->envp[i]));
				i = 0;
			}
		}
		else
			reset_pwd(&ms->envp[i], new_pwd, old_pwd);
		++i;
	}
	free (old_pwd);
}

char	*get_home(char **envp)
{
	int		i;
	char	*home;

	i = 0;
	home = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			home = envp[i];
		++i;
	}
	return (home);
}

static char	*chdir_rute(char *rute)
{
	char	**steps1;
	char	*sol;

	steps1 = ft_split(rute, ' ');
	if (!steps1[1])
	{
		free_strs(steps1);
		return (NULL);
	}
	sol = gnl_substr(steps1[1], 0, ft_strlen(steps1[1]));
	free_strs(steps1);
	return (sol);
}

void	do_cd(char *txt, t_mini_shell *ms)
{
	char	*rute;

	rute = chdir_rute(txt);
	if (!rute)
	{
		rute = get_home(ms->envp);
		if (!rute)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		rute = ft_substr(rute, 5, ft_strlen(rute));
	}
	if (chdir(rute) != 0)
		perror("Error");
	else
	{
		free (rute);
		rute = getcwd(NULL, 0);
		printf("RUTE1 = %s\n", rute);
		change_pwd(ms, rute);
	}
	free (rute);
}
