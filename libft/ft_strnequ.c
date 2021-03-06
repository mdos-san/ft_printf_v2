/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:38:06 by mdos-san          #+#    #+#             */
/*   Updated: 2015/12/03 13:14:48 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (*(s1 + i) == 0 || *(s2 + i) == 0)
			return (1);
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}
