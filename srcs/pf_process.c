/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:18 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/26 18:00:37 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	flag(t_pf *pf, char **s)
{
	if (pf->type == 'd' || pf->type == 'i')
	{
		if ((*s)[0] != '-' && pf->f_plus == 1)
			(*s) = ft_strjoin("+", *s);
		if (pf->f_space == 1 && (*s)[0] != '-')
			(*s) = ft_strjoin(" ", *s);
	}
	if (pf->type == 'o' || pf->type == 'O')
	{
		if (pf->f_sharp && ft_strcmp("0", *s) != 0)
			*s = ft_strjoin("0", *s);
	}
	if (pf->type == 'x')
		if (pf->f_sharp && ft_strcmp("0", *s) != 0)
			*s = ft_strjoin("0x", *s);
	if (pf->type == 'X')
		if (pf->f_sharp && ft_strcmp("0", *s) != 0)
			*s = ft_strjoin("0X", *s);
}

static void	precision(t_pf *pf, char **s)
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
	{
		if (pf->precision >= length)
		{
			if ((*s)[0] == ' ' || (*s)[0] == '+')
				(*s)[0] = '0';
			if ((*s)[0] != '-')
			{
				str = ft_strnew(pf->precision);
				ft_memset(str, '0', pf->precision);
				str[pf->precision - length] = 0;
				*s = ft_strjoin(str, *s);
			}
			else
			{
				str = ft_strnew(pf->precision + 2);
				ft_memset(str, '0', pf->precision + 2);
				str[length] = '-';
				*s = ft_strjoin(str + length, *s + 1);
			}
			if (pf->f_plus)
				*s = ft_strjoin("+", *s);
			if (pf->f_space)
				*s = ft_strjoin(" ", *s);
		}
		else if (pf->status == STATUS_P_END && pf->precision == 0 && ft_strcmp("0", *s) == 0)
			(*s)[0] = '\0';
	}
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
	{
		if (pf->p_given && pf->precision == 0 && ft_strcmp(*s, "0") == 0)
			*s[0] = 0;
		else
		{
			if (pf->f_sharp && pf->precision > length - 2)
			{
				str = ft_strnew(pf->precision + 2);
				ft_memset(str, '0', pf->precision + 2);
				str[0] = '0';
				str[1] = pf->type;
				str[pf->precision - length + 4] = 0;
				*s = ft_strjoin(str, *s + 2);
			}
			else
			{
				str = ft_strnew(pf->precision);
				ft_memset(str, '0', pf->precision);
				*s = ft_strjoin(str + length, *s);
			}
		}
	}
	else if (pf->precision > length && pf->type != 'C' && pf->type != 'S')
	{
		str = ft_strnew(pf->precision);
		ft_memset(str, '0', pf->precision);
		*s = ft_strjoin(str + length, *s);
	}
	pf->precision = 0;
}

void		width(t_pf *pf, char *s)
{
	char	*w;

	if (pf->type == 'c' && ft_strlen(s) == 0)
		pf->width = ((int)pf->width - 1 > 0)
			? pf->width - 1  : 0;
	else
		pf->width = ((int)pf->width - (int)ft_strlen(s) > 0)
			? pf->width - ft_strlen(s)  : 0;
	w = ft_strnew(pf->width);
	if (pf->type == 'd' || pf->type == 'D' || pf->type == 'i')
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
	else if (pf->f_zero == 1 && pf->f_minus == 0)
		ft_memset(w, '0', pf->width);
	else
		ft_memset(w, ' ', pf->width);
	if (pf->f_space && pf->f_zero && (pf->type == 'd' || pf->type == 'D') && s[0] == ' ')
		pf_buffer_add(pf, " ");
	if (pf->f_zero && pf->f_plus && (pf->type == 'd' || pf->type == 'D') && s[0] == '+')
		pf_buffer_add(pf, "+");
	if (pf->f_zero && !pf->f_minus && (pf->type == 'd' || pf->type == 'D') && s[0] == '-')
		pf_buffer_add(pf, "-");
	if (pf->f_zero && pf->type == 'p')
		pf_buffer_add(pf, "0x");
	if (pf->f_sharp && pf->f_zero && !pf->f_minus && pf->type == 'x')
		pf_buffer_add(pf, "0x");
	if (pf->f_sharp && pf->f_zero && !pf->f_minus && pf->type == 'X')
		pf_buffer_add(pf, "0X");
	pf_buffer_add(pf, w);
	pf->width = 0;
}

static	int is_dioupx(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'u' || c == 'U' || c == 'o' ||
		c == 'O' || c == 'x' || c == 'X' ||c == 'p')
		return (1);
	return (0);
}

static	void get_offset(t_pf *pf, char *s)
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

void	pf_process(t_pf *pf)
{
	char	*s;

	if (pf->type == 'c')
	{
		if (pf->mod_l)
			pf->type = 'C';
		else
		{
			s = ft_strnew(1);
			s[0] = (char)va_arg(pf->arg, int);
			if (s[0] == '\0')
			{
				width(pf, s);
				pf_buffer_add_null(pf);
			}
		}
	}
	if (pf->type == 'C')
		s = (get_wchar(va_arg(pf->arg, int)));
	if (pf->type == 's')
	{
		if (pf->mod_l)
			pf->type = 'S';
		else
		{
			s = ft_strdup(va_arg(pf->arg, char *));
			s = (s == NULL) ? ft_strdup("(null)") : s;
		}
	}
	if (pf->type == 'S')
		s = get_wstr(va_arg(pf->arg, int *), pf->precision);
	(is_dioupx(pf->type)) ? va_get(pf, &s) : 0;
	flag(pf, &s);
	(pf->type != 'c') ? precision(pf, &s) : 0;
	if (pf->type != 'c' || s[0])
	{
		(pf->f_minus == 0) ? width(pf, s) : 0;
		get_offset(pf, s);
		(pf->type != 'C') ? pf_buffer_add(pf, s + pf->offset) : pf_buffer_nadd(pf, s, ft_strlen(s));
		(pf->f_minus == 1) ? width(pf, s) : 0;
	}
}
