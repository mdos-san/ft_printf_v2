/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:25 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/27 15:03:26 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	out(t_pf *pf, unsigned int i)
{
	if (pf->input[i] == '%')
		pf->status = STATUS_IN;
	else
	{
		pf->buffer[pf->index] = pf->input[i];
		++pf->index;
		if (pf->index == PF_BUFFER)
		{
			write(1, pf->buffer, PF_BUFFER);
			pf->index = 0;
			++pf->number_buffer;
		}
	}
}

static void	flag_init(t_pf *pf)
{
	pf->p_given = 0;
	pf->f_plus = 0;
	pf->f_space = 0;
	pf->f_minus = 0;
	pf->f_sharp = 0;
	pf->f_zero = 0;
	pf->mod_l = 0;
	pf->mod_h = 0;
	pf->mod_j = 0;
	pf->mod_z = 0;
}

void		pf_start(t_pf *pf)
{
	unsigned int	i;

	i = 0;
	flag_init(pf);
	while (pf->input[i])
	{
		if (pf->status == STATUS_OUT)
			out(pf, i);
		else if (pf->status > 0)
		{
			parse(pf, i);
			(pf->status == STATUS_OUT) ? flag_init(pf) : 0;
		}
		++i;
	}
}
