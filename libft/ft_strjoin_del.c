/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:47:33 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/30 15:48:47 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strjoin_del(char *s1, char *s2, int del)
{
	int		len;
	char	*result;

	result = 0;
	len = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char*)malloc(len + 1);
	if (result == NULL)
		return (NULL);
	result[len] = 0;
	ft_bzero(result, len);
	ft_strcat(result, s1);
	ft_strcat(result, s2);
	(del == 1 || del == 3) ? ft_strdel(&s1) : 0;
	(del == 2 || del == 3) ? ft_strdel(&s2) : 0;
	return (result);
}
