/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:43:52 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/27 15:48:32 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	go_out(t_pf *pf, unsigned int i)
{
	char	s[2];

	s[1] = 0;
	pf->status = STATUS_OUT;
	if (pf->index == PF_BUFFER)
	{
		write(1, pf->buffer, PF_BUFFER);
		pf->index = 0;
		++pf->number_buffer;
	}
	s[0] = pf->input[i];
	(!pf->f_minus) ? width(pf, s) : 0;
	pf->buffer[pf->index] = pf->input[i];
	++pf->index;
	(pf->f_minus) ? width(pf, s) : 0;
}

void	in_flag(t_pf *pf, unsigned int i)
{
	if (pf->input[i] == '+')
	{
		pf->f_plus = 1;
		pf->f_space = 0;
	}
	if (pf->input[i] == ' ' && pf->f_plus == 0)
		pf->f_space = 1;
	if (pf->input[i] == '-')
		pf->f_minus = 1;
	if (pf->input[i] == '0')
		pf->f_zero = 1;
	if (pf->input[i] == '#')
		pf->f_sharp = 1;
}
