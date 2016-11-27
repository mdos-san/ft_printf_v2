/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:01 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/27 15:38:51 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char	*get_wstr(int *istr, unsigned int pre)
{
	char	*ret;
	char	*prev;
	int		i;

	i = 0;
	ret = NULL;
	if (istr == NULL)
		return (ft_strdup("(null)"));
	while (istr[i])
	{
		if (ret)
		{
			prev = ret;
			ret = ft_strjoin(ret, get_wchar(istr[i]));
			if (ft_strlen(ret) > pre && pre != 0)
				return (prev);
		}
		else
			ret = get_wchar(istr[i]);
		++i;
	}
	return (ret);
}
