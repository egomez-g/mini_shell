/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil-moy <sgil-moy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:20:50 by sgil-moy          #+#    #+#             */
/*   Updated: 2023/09/26 16:27:06 by sgil-moy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int str, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (str > ft_strlen(s))
		len = 0;
	else if (len > (ft_strlen(s) - str))
		len = ft_strlen(s) - str;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (p);
	if (ft_strlen(s) <= str)
		len = 0;
	while (i < len && s[str + i] != '\0')
	{
		p[i] = s[str + i];
		++i;
	}
	p[i] = '\0';
	return (p);
}
