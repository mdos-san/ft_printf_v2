/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 14:57:42 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/27 15:45:26 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	in_status_p(t_pf *pf, unsigned int i)
{
	int in;

	if (pf->input[i] == '*')
	{
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

static void	in_mod(t_pf *pf, unsigned int i)
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

static void	in_pre(t_pf *pf, unsigned int i)
{
	pf->status = STATUS_P;
	pf->p_given = 1;
	if (pf->input[i + 1] != '*' && !ft_isdigit(pf->input[i + 1]))
		pf->status = STATUS_P_END;
}

static void	in_pro(t_pf *pf, unsigned int i)
{
	pf->type = pf->input[i];
	pf_process(pf);
	pf->status = STATUS_OUT;
}

void		parse(t_pf *pf, unsigned int i)
{
	if (ft_strchr(pf->list_flags, pf->input[i]) && pf->status < STATUS_W)
		in_flag(pf, i);
	else if (pf->status < STATUS_W
			&& (ft_isdigit(pf->input[i]) || pf->input[i] == '*'))
	{
		pf->status = (ft_isdigit(pf->input[i + 1])) ? STATUS_W : STATUS_W_END;
		pf->width = (pf->input[i] == '*')
			? va_arg(pf->arg, int) : ft_atoi(pf->input + i);
	}
	else if (pf->status == STATUS_W)
		pf->status = (ft_isdigit(pf->input[i + 1])) ? STATUS_W : STATUS_W_END;
	else if (pf->status < STATUS_P && pf->input[i] == '.')
		in_pre(pf, i);
	else if (pf->status == STATUS_P)
		in_status_p(pf, i);
	else if (pf->status == STATUS_P_PAR)
		pf->status = (ft_isdigit(pf->input[i + 1]))
			? STATUS_P_PAR : STATUS_P_END;
	else if (ft_strchr(pf->list_mod, pf->input[i]))
		in_mod(pf, i);
	else if (ft_strchr(pf->list_types, pf->input[i]))
		in_pro(pf, i);
	else
		go_out(pf, i);
}
