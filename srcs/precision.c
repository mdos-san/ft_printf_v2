/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:19:37 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/27 15:26:18 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	p_d(t_pf *pf, char **s, char **str, unsigned int length)
{
	if (pf->precision >= length)
	{
		if ((*s)[0] == ' ' || (*s)[0] == '+')
			(*s)[0] = '0';
		if ((*s)[0] != '-')
		{
			*str = ft_strnew(pf->precision);
			ft_memset(*str, '0', pf->precision);
			(*str)[pf->precision - length] = 0;
			*s = ft_strjoin(*str, *s);
		}
		else
		{
			*str = ft_strnew(pf->precision + 2);
			ft_memset(*str, '0', pf->precision + 2);
			(*str)[length] = '-';
			*s = ft_strjoin(*str + length, *s + 1);
		}
		if (pf->f_plus)
			*s = ft_strjoin("+", *s);
		if (pf->f_space)
			*s = ft_strjoin(" ", *s);
	}
	else if (pf->status == SP && pf->precision == 0 && ft_strcmp("0", *s) == 0)
		(*s)[0] = '\0';
}

static void	p_x(t_pf *pf, char **s, char **str, unsigned int length)
{
	if (pf->p_given && pf->precision == 0 && ft_strcmp(*s, "0") == 0)
		(*s)[0] = 0;
	else
	{
		if (pf->f_sharp && pf->precision > length - 2)
		{
			*str = ft_strnew(pf->precision + 2);
			ft_memset(*str, '0', pf->precision + 2);
			(*str)[0] = '0';
			(*str)[1] = pf->type;
			(*str)[pf->precision - length + 4] = 0;
			*s = ft_strjoin(*str, *s + 2);
		}
		else
		{
			*str = ft_strnew(pf->precision);
			ft_memset(*str, '0', pf->precision);
			*s = ft_strjoin(*str + length, *s);
		}
	}
}

void		precision(t_pf *pf, char **s)
{
	unsigned int	length;
	char			*str;

	length = ft_strlen(*s);
	if (pf->type == 's' || pf->type == 'S')
	{
		if (0 < pf->precision && pf->precision < length)
			(*s)[pf->precision] = '\0';
		if (pf->status == STATUS_P_END && pf->precision == 0)
			(*s)[0] = '\0';
	}
	else if (pf->type == 'p')
	{
		if (pf->p_given && pf->precision == 0 && ft_strcmp(*s, "0x0") == 0)
			(*s)[2] = 0;
		else if (pf->precision > length - 2)
		{
			str = ft_strnew(pf->precision + 2);
			ft_memset(str, '0', pf->precision + 2);
			str[0] = '0';
			str[1] = 'x';
			str[pf->precision - length + 4] = 0;
			*s = ft_strjoin(str, *s + 2);
		}
	}
	else if ((pf->type == 'd' || pf->type == 'D' || pf->type == 'i'))
		p_d(pf, s, &str, length);
	else if (pf->type == 'u' || pf->type == 'o' || pf->type == 'O')
	{
		if (pf->p_given && pf->precision == 0 && ft_strcmp(*s, "0") == 0 && !pf->f_sharp)
			(*s)[0] = 0;
		else if (pf->precision > length)
		{
			str = ft_strnew(pf->precision);
			ft_memset(str, '0', pf->precision);
			*s = ft_strjoin(str + length, *s);
		}
	}
	else if (pf->type == 'x' || pf->type == 'X')
		p_x(pf, s, &str, length);
	else if (pf->precision > length && pf->type != 'C' && pf->type != 'S')
	{
		str = ft_strnew(pf->precision);
		ft_memset(str, '0', pf->precision);
		*s = ft_strjoin(str + length, *s);
	}
	pf->precision = 0;
}
