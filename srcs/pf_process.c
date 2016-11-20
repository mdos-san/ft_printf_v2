/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:18 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/20 10:07:18 by mdos-san         ###   ########.fr       */
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
	if (pf->type == 'o')
	{
		if (pf->f_sharp && ft_strcmp("0", *s) != 0)
			*s = ft_strjoin("0", *s);
	}
	if (pf->type == 'x')
	{
		if (pf->f_sharp && ft_strcmp("0", *s) != 0)
			*s = ft_strjoin("0x", *s);
	}
}

static void	precision(t_pf *pf, char **s)
{
	unsigned int	length;
	char			*str;

	length = ft_strlen(*s);
	if (pf->type == 's')
	{
		if (0 < pf->precision && pf->precision < length)
			(*s)[pf->precision] = '\0';
		if (pf->status == STATUS_P_END && pf->precision == 0)
			(*s)[0] = '\0';
	}
	else if (pf->type == 'p' && pf->precision > length - 2)
	{
		str = ft_strnew(pf->precision + 2);
		ft_memset(str, '0', pf->precision + 2);
		str[0] = '0';
		str[1] = 'x';
		str[pf->precision - length + 4] = 0;
		*s = ft_strjoin(str, *s + 2);
	}
	else if ((pf->type == 'd' || pf->type == 'i'))
	{
		if (pf->precision >= length)
		{
			if ((*s)[0] != '-')
			{
				str = ft_strnew(pf->precision);
				ft_memset(str, '0', pf->precision);
				*s = ft_strjoin(str + length, *s);
			}
			else
			{
				str = ft_strnew(pf->precision + 2);
				ft_memset(str, '0', pf->precision + 2);
				str[length] = '-';
				*s = ft_strjoin(str + length, *s + 1);
			}
		}
		else if (pf->status == STATUS_P_END && pf->precision == 0 && ft_strcmp("0", *s) == 0)
			(*s)[0] = '\0';
	}
	else if (pf->type == 'x')
	{
		if (pf->f_sharp && pf->precision > length - 2)
		{
			str = ft_strnew(pf->precision + 2);
			ft_memset(str, '0', pf->precision + 2);
			str[0] = '0';
			str[1] = 'x';
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
	else if (pf->precision > length)
	{
		str = ft_strnew(pf->precision);
		ft_memset(str, '0', pf->precision);
		*s = ft_strjoin(str + length, *s);
	}
	pf->precision = 0;
}

static void	width(t_pf *pf, char *s)
{
	char	*w;

	pf->width = ((int)pf->width - (int)ft_strlen(s) > 0)
		? pf->width - ft_strlen(s)  : 0;
	w = ft_strnew(pf->width);
	ft_memset(w, ' ', pf->width);
	pf_buffer_add(pf, w);
	pf->width = 0;
}

void	pf_process(t_pf *pf)
{
	char	*s;
	char	*tmp_str;

	if (pf->type == 'c')
	{
		if (pf->mod_l)
			pf->type = 'C';
		else
		{
			s = ft_strnew(1);
			s[0] = (char)va_arg(pf->arg, int);
			if (s[0] == '\0')
				pf_buffer_add_null(pf);
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
		s = get_wstr(va_arg(pf->arg, int *));
	if (pf->type == 'd' || pf->type == 'D' || pf->type == 'i')
	{
		if (pf->mod_l)
			s = ft_itoa_base(va_arg(pf->arg, long), 10);
		else if (pf->mod_h == 2 && (pf->type == 'd' || pf->type == 'i'))
			s = ft_itoa_base((char)va_arg(pf->arg, int), 10);
		else if (pf->mod_j == 1)
			s = ft_itoa_base(va_arg(pf->arg, intmax_t), 10);
		else if (pf->mod_z == 1)
			s = ft_itoa_base(va_arg(pf->arg, size_t), 10);
		else
			s = (pf->type == 'd' || pf->type == 'i')
				? ft_itoa_base(va_arg(pf->arg, int), 10)
				: ft_itoa_base(va_arg(pf->arg, long), 10);
	}
	if (pf->type == 'u' || pf->type == 'U')
	{
		if (pf->mod_l)
			s = ft_uitoa_base(va_arg(pf->arg, unsigned long), 10, 0);
		else if (pf->mod_h == 2 && pf->type == 'u')
			s = ft_uitoa_base((unsigned char)va_arg(pf->arg, unsigned int), 10, 0);
		else if (pf->mod_h == 2 && pf->type == 'U')
			s = ft_uitoa_base((unsigned short)va_arg(pf->arg, unsigned int), 10, 0);
		else if (pf->mod_z == 1)
			s = ft_uitoa_base(va_arg(pf->arg, size_t), 10, 0);
		else if (pf->mod_j == 1)
			s = ft_uitoa_base(va_arg(pf->arg, uintmax_t), 10, 0);
		else
			s = (pf->type == 'u')
				? ft_uitoa_base(va_arg(pf->arg, unsigned int), 10, 0)
				: ft_uitoa_base(va_arg(pf->arg, unsigned long), 10, 0);
	}
	if (pf->type == 'o' || pf->type == 'O')
	{
		if (pf->mod_l)
			s = ft_uitoa_base(va_arg(pf->arg, unsigned long), 8, 0);
		else if (pf->mod_h == 2 && pf->type == 'o')
			s = ft_uitoa_base((unsigned char)va_arg(pf->arg, unsigned int), 8, 0);
		else if (pf->mod_h == 2 && pf->type == 'O')
			s = ft_uitoa_base((unsigned short)va_arg(pf->arg, unsigned int), 8, 0);
		else if (pf->mod_z == 1)
			s = ft_uitoa_base(va_arg(pf->arg, size_t), 8, 0);
		else if (pf->mod_j == 1)
			s = ft_uitoa_base(va_arg(pf->arg, uintmax_t), 8, 0);
		else
			s = (pf->type == 'o')
				? ft_uitoa_base(va_arg(pf->arg, unsigned int), 8, 0)
				: ft_uitoa_base(va_arg(pf->arg, unsigned long), 8, 0);
	}
	if (pf->type == 'x' || pf->type == 'X')
	{
		if (pf->mod_l)
			s = ft_uitoa_base(va_arg(pf->arg, unsigned long), 16, ((pf->type == 'x') ? 0 : 1));
		else if (pf->mod_h == 2)
			s = ft_uitoa_base((unsigned char)va_arg(pf->arg, unsigned int), 16, ((pf->type == 'x') ? 0 : 1));
		else if (pf->mod_z)
			s = ft_uitoa_base(va_arg(pf->arg, size_t), 16, ((pf->type == 'x') ? 0 : 1));
		else if (pf->mod_j)
			s = ft_uitoa_base(va_arg(pf->arg, uintmax_t), 16, ((pf->type == 'x') ? 0 : 1));
		else
			s = ft_uitoa_base(va_arg(pf->arg, unsigned int), 16, ((pf->type == 'x') ? 0 : 1));
	}
	if (pf->type == 'p')
	{
		tmp_str = ft_uitoa_base(va_arg(pf->arg, unsigned long long), 16, 0);
		s = ft_strjoin("0x", tmp_str);
		ft_strdel(&tmp_str);
	}
	flag(pf, &s);
	precision(pf, &s);
	(pf->f_minus == 0) ? width(pf, s) : 0;
	(pf->type != 'C') ? pf_buffer_add(pf, s) : pf_buffer_nadd(pf, s, ft_strlen(s));
	(pf->f_minus == 1) ? width(pf, s) : 0;
}
