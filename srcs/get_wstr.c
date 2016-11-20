/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:01 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/20 09:09:02 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*get_wstr(int *istr)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	if (istr == NULL)
		return (ft_strdup("(null)"));
	while (istr[i])
	{
		if (ret)
			ret = ft_strjoin(ret, get_wchar(istr[i]));
		else
			ret = get_wchar(istr[i]);
		++i;
	}
	return (ret);
}
