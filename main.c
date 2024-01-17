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

static void 	set_basics( t_mini_shell *ms)
{
	int i = 0;
	int pwd = 0;
	int shlvl = 0;
	int user = 0;

	while (ms->envp[i])
	{
		if (ft_strcmp(ms->envp[i], "PWD="))
			pwd = 1;
		if (ft_strcmp(ms->envp[i], "SHLVL="))
			shlvl = 1;
		if (ft_strcmp(ms->envp[i], "_="))
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
	atexit(leaks);
	while (1)
	{
		txt = readline("minishell>");
		if (txt && *txt != '\0')
		{
			if (ft_strncmp(txt, "exit\0", 5) == 0)
				exit (1);
			add_history(txt);
			find_lines(txt, &ms);
			free (txt);
		}
	}
}