#include "mini_shell.h"

void leaks()
{
	system("leaks -q mini_shell");
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while(strs[i])
	{
		free(strs[i]);
		++i;
	}
	free(strs);
}

static void	set_basics(t_mini_shell *ms)
{
	int i = 0;
	int pwd = 0;
	int shlvl = 0;
	int user = 0;

	while (ms->envp[i])
	{
		if (!ft_strncmp(ms->envp[i], "PWD=", 4))
			pwd = 1;
		if (!ft_strncmp(ms->envp[i], "SHLVL=", 6))
			shlvl = 1;
		if (!ft_strncmp(ms->envp[i], "_=", 2))
			user = 1;
		i++;
	}
	if (pwd == 0)
		do_export("PWD=/Users/sgil-moy/Desktop/git-minishell", ms);
	if (shlvl == 0)
		do_export("SHLVL=1", ms);
	if (user == 0)
		do_export("_=/usr/bin/env", ms);
}

static char *do_shell_lvl(char *line)
{
	char	**strs;
	int		num;
	char	*sol;
	char	*aux;

	strs = ft_split(line, '=');
	if (strs[2])
		return(ft_strdup("SHLVL=1"));
	num = 0;
	while (strs[1][num])
	{
		if (!ft_isdigit(strs[1][num]))
			return(ft_strdup("SHLVL=1"));
		num++;
	}
	num = ft_atoi(strs[1]);
	num++;
	aux = ft_itoa(num);
	sol = ft_strjoin("SHLVL=", aux);
	free(aux);
	free_strs(strs);
	return(sol);
}

static void	copy_envp(char **envp, t_mini_shell *ms)
{
	int	len;

	len = 0;
	while(envp[len])
		len++;
	ms->envp = (char**)malloc(sizeof(char*) * (len + 1));
	if (!ms->envp)
		return ;
	len = 0;
	while (envp[len])
	{
		if (!(ft_strncmp(envp[len], "SHLVL=", 6)))
			ms->envp[len] = do_shell_lvl(envp[len]);
		else
			ms->envp[len] = ft_strdup(envp[len]);
		len++;
	}
	set_basics(ms);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini_shell	ms;
	char			*txt;

	argc = 0;
	argv = NULL;
	copy_envp(envp, &ms);
	ms.status = 0;
	if (argc > 1)
	{
		printf("minishell> Too many arguments\n");
		exit(1);
	}
	while (1)
	{
		txt = readline("minishell>");
		if (txt && *txt != '\0')
		{
			add_history(txt);
			find_lines(txt, &ms);
			free (txt);
		}
	}
}
