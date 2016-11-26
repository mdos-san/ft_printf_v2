/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:25 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/26 19:04:45 by mdos-san         ###   ########.fr       */
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

static void	go_out(t_pf *pf, unsigned int i)
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

static void	in_flag(t_pf *pf, unsigned int i)
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

static void	in_status_p(t_pf *pf, unsigned int i)
{
	if (pf->input[i] == '*')
	{
		int in;

		in = va_arg(pf->arg, int);
		pf->precision = (in < 0) ? 0 : in;
		pf->status = STATUS_P_END;
	}
	else if (ft_isdigit(pf->input[i]))
	{
		pf->precision = ft_atoi(pf->input + i);
		pf->status = (ft_isdigit(pf->input[i + 1]))
			? STATUS_P_PAR : STATUS_P_END;
	}
}

static void	in(t_pf *pf, unsigned int i)
{
	if (ft_strchr(pf->list_flags, pf->input[i]) && pf->status < STATUS_W)
		in_flag(pf, i);
	else if (pf->status < STATUS_W && (ft_isdigit(pf->input[i]) || pf->input[i] == '*'))
	{
		pf->status = (ft_isdigit(pf->input[i + 1])) ? STATUS_W : STATUS_W_END;
		pf->width = (pf->input[i] == '*')
			? va_arg(pf->arg, int) : ft_atoi(pf->input + i);
	}
	else if (pf->status == STATUS_W)
		pf->status = (ft_isdigit(pf->input[i + 1])) ? STATUS_W : STATUS_W_END;
	else if (pf->status < STATUS_P && pf->input[i] == '.')
	{
		pf->status = STATUS_P;
		pf->p_given = 1;
		if (pf->input[i + 1] != '*' && !ft_isdigit(pf->input[i + 1]))
			pf->status = STATUS_P_END;
	}
	else if (pf->status == STATUS_P)
		in_status_p(pf, i);
	else if (pf->status == STATUS_P_PAR)
		pf->status = (ft_isdigit(pf->input[i + 1])) ? STATUS_P_PAR : STATUS_P_END;
	else if (ft_strchr(pf->list_mod, pf->input[i]))
	{
		if (pf->input[i] == 'l')
			++pf->mod_l;
		if (pf->input[i] == 'h')
			++pf->mod_h;
		if (pf->input[i] == 'z')
			++pf->mod_z;
		if (pf->input[i] == 'j')
			++pf->mod_j;
	}
	else if (ft_strchr(pf->list_types, pf->input[i]))
	{
		pf->type = pf->input[i];
		pf_process(pf);
		pf->status = STATUS_OUT;
	}
	else
		go_out(pf, i);
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
			in(pf, i);
			(pf->status == STATUS_OUT) ? flag_init(pf) : 0;
		}
		++i;
	}
}
