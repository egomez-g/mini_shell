/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:13:25 by sgil-moy          #+#    #+#             */
/*   Updated: 2024/01/31 17:13:26 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	do_pwd(void)
{
	char	*rute;

	rute = getcwd(NULL, 0);
	printf("%s\n", rute);
	free (rute);
}
