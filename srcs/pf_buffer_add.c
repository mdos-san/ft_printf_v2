/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_buffer_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:06 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/20 09:09:07 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	pf_buffer_add(t_pf *pf, char *str)
{
	if (str != NULL && str[0] != '\0')
	{
		if (pf->index == PF_BUFFER)
		{
			write(1, pf->buffer, PF_BUFFER);
			pf->index = 0;
			++pf->number_buffer;
		}
		if (ft_strlen(str) + pf->index <= PF_BUFFER)
		{
			ft_strcpy(pf->buffer + pf->index, str);
			pf->index += ft_strlen(str);
		}
		else
		{
			pf->buffer[pf->index] = str[0];
			++pf->index;
			pf_buffer_add(pf, str + 1);
		}
	}
}

void	pf_buffer_add_null(t_pf *pf)
{
	if (pf->index == PF_BUFFER)
	{
		write(1, pf->buffer, PF_BUFFER);
		pf->index = 0;
		++pf->number_buffer;
	}
	if (1 + pf->index <= PF_BUFFER)
	{
		ft_strcpy(pf->buffer + pf->index, "\0");
		pf->index += 1;
	}
	else
	{
		pf->buffer[pf->index] = '\0';
		++pf->index;
	}
}

void	pf_buffer_nadd(t_pf *pf, char *str, int n)
{
	static int	index = 0;

	if (index < n)
	{
		if (pf->index == PF_BUFFER)
		{
			write(1, pf->buffer, PF_BUFFER);
			pf->index = 0;
			++pf->number_buffer;
			pf_buffer_nadd(pf, str, n);
		}
		else
		{
			pf->buffer[pf->index] = str[index];
			++pf->index;
			++index;
			pf_buffer_nadd(pf, str, n);
		}
	}
	if (index == 0 && n == 0)
		pf_buffer_add_null(pf);
	else
		index = 0;
}
