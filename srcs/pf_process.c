/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:18 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/30 16:59:11 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	flag(t_pf *pf, char **s)
{
	if (pf->type == 'd' || pf->type == 'i')
	{
		if ((*s)[0] != '-' && pf->f_plus == 1)
			(*s) = ft_strjoin_del("+", *s, 2);
		if (pf->f_space == 1 && (*s)[0] != '-')
			(*s) = ft_strjoin_del(" ", *s, 2);
	}
	if (pf->type == 'o' || pf->type == 'O')
	{
		if (pf->f_sharp && ft_strcmp("0", *s) != 0)
			*s = ft_strjoin_del("0", *s, 2);
	}
	if (pf->type == 'x' && pf->f_sharp && ft_strcmp("0", *s) != 0)
		*s = ft_strjoin_del("0x", *s, 2);
	if (pf->type == 'X' && pf->f_sharp && ft_strcmp("0", *s) != 0)
		*s = ft_strjoin_del("0X", *s, 2);
}

static int	is_dioupx(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'u' || c == 'U' || c == 'o' ||
			c == 'O' || c == 'x' || c == 'X' || c == 'p')
		return (1);
	return (0);
}

static void	get_offset(t_pf *pf, char *s)
{
	pf->offset = 0;
	if (pf->f_zero && !pf->f_minus
			&& (pf->type == 'd' || pf->type == 'D') && s[0] == '-')
		pf->offset = 1;
	else if (pf->f_zero && pf->f_plus
			&& (pf->type == 'd' || pf->type == 'D') && s[0] == '+')
		pf->offset = 1;
	else if (pf->f_space && pf->f_zero
			&& (pf->type == 'd' || pf->type == 'D') && s[0] == ' ')
		pf->offset = 1;
	else if (!pf->f_minus && pf->f_sharp
			&& pf->f_zero && (pf->type == 'x' || pf->type == 'X'))
		pf->offset = 2;
	else if (pf->f_zero && pf->type == 'p')
		pf->offset = 2;
}

static void	check_cs(t_pf *pf, char **s)
{
	if (pf->type == 'c')
	{
		if (pf->mod_l)
			pf->type = 'C';
		else
		{
			*s = ft_strnew(1);
			(*s)[0] = (char)va_arg(pf->arg, int);
			if ((*s)[0] == '\0')
			{
				width(pf, *s);
				pf_buffer_add_null(pf);
			}
		}
	}
	else if (pf->type == 's')
	{
		if (pf->mod_l)
			pf->type = 'S';
		else
		{
			*s = ft_strdup(va_arg(pf->arg, char *));
			*s = (*s == NULL) ? ft_strdup("(null)") : *s;
		}
	}
}

void		pf_process(t_pf *pf)
{
	char	*s;

	check_cs(pf, &s);
	if (pf->type == 'C')
		s = get_wchar(va_arg(pf->arg, int));
	else if (pf->type == 'S')
		s = get_wstr(va_arg(pf->arg, int *), pf->precision);
	(is_dioupx(pf->type)) ? va_get(pf, &s) : 0;
	flag(pf, &s);
	(pf->type != 'c') ? precision(pf, &s) : 0;
	pf->precision = 0;
	if (pf->type != 'c' || s[0])
	{
		(pf->f_minus == 0) ? width(pf, s) : 0;
		get_offset(pf, s);
		(pf->type != 'C') ? pf_buffer_add(pf, s + pf->offset)
			: pf_buffer_nadd(pf, s, ft_strlen(s));
		(pf->f_minus == 1) ? width(pf, s) : 0;
	}
	ft_strdel(&s);
}
