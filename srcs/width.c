/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:08:26 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/30 16:05:37 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	w_di(t_pf *pf, char *w)
{
	if (pf->p_given && pf->precision < pf->width)
		ft_memset(w, ' ', pf->width);
	else
	{
		if (pf->f_zero == 1 && pf->f_minus == 0)
			ft_memset(w, '0', pf->width);
		else
			ft_memset(w, ' ', pf->width);
	}
}

static void	w_ex(t_pf *pf, char *s)
{
	if (pf->f_space && pf->f_zero
			&& (pf->type == 'd' || pf->type == 'D') && s[0] == ' ')
		pf_buffer_add(pf, " ");
	if (pf->f_zero && pf->f_plus
			&& (pf->type == 'd' || pf->type == 'D') && s[0] == '+')
		pf_buffer_add(pf, "+");
	if (pf->f_zero && !pf->f_minus
			&& (pf->type == 'd' || pf->type == 'D') && s[0] == '-')
		pf_buffer_add(pf, "-");
	if (pf->f_zero && pf->type == 'p')
		pf_buffer_add(pf, "0x");
	if (pf->f_sharp && pf->f_zero && !pf->f_minus && pf->type == 'x')
		pf_buffer_add(pf, "0x");
	if (pf->f_sharp && pf->f_zero && !pf->f_minus && pf->type == 'X')
		pf_buffer_add(pf, "0X");
}

void		width(t_pf *pf, char *s)
{
	char	*w;

	if (pf->type == 'c' && ft_strlen(s) == 0)
		pf->width = ((int)pf->width - 1 > 0) ? pf->width - 1 : 0;
	else
		pf->width = ((int)pf->width - (int)ft_strlen(s) > 0)
			? pf->width - ft_strlen(s) : 0;
	w = ft_strnew(pf->width);
	if (pf->type == 'd' || pf->type == 'D' || pf->type == 'i')
		w_di(pf, w);
	else if (pf->f_zero == 1 && pf->f_minus == 0)
		ft_memset(w, '0', pf->width);
	else
		ft_memset(w, ' ', pf->width);
	w_ex(pf, s);
	pf_buffer_add(pf, w);
	ft_strdel(&w);
	pf->width = 0;
}
