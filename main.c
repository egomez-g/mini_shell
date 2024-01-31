/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:11:11 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:11:12 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	leaks(void)
{
	system("leaks -q mini_shell");
}

int	main(int argc, char **argv, char **envp)
{
	t_mini_shell	ms;
	char			*txt;

	argv = NULL;
	copy_envp(envp, &ms);
	ms.status = 0;
	signal(SIGINT, int_handler);
	if (argc > 1)
		return (printf("🤬minishell> Too many arguments\n"), 1);
	while (1)
	{
		txt = readline("🤬minishell> ");
		if (!txt)
			break ;
		if (*txt != '\0')
		{
			add_history(txt);
			find_lines(txt, &ms);
		}
		else
			free (txt);
	}
	exit (0);
}
