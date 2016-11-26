/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   va_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 17:20:45 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/26 18:00:49 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static	int	get_base(char c)
{
	if (c == 'd' || c == 'D' || c == 'i' || c == 'u' || c == 'U')
		return (10);
	if (c == 'o' || c == 'O')
		return (8);
	if (c == 'x' || c == 'X')
		return (16);
	return (0);
}

void	va_get(t_pf *pf, char **s)
{
	int		base;
	int		up;
	char	is_lower;
	char	*tmp_str;

	base = get_base(pf->type);
	up = (pf->type == 'X') ? 1 : 0;
	is_lower = ('a' <= pf->type && pf->type <= 'z') ? 1 : 0;
	if (pf->type == 'd' || pf->type == 'D' || pf->type == 'i')
	{
		if (pf->mod_l)
			*s = ft_itoa_base(va_arg(pf->arg, long), 10);
		else if (pf->mod_h == 1 && (pf->type == 'd' || pf->type == 'i'))
			*s = ft_itoa_base((short)va_arg(pf->arg, int), 10);
		else if (pf->mod_h == 2 && (pf->type == 'd' || pf->type == 'i'))
			*s = ft_itoa_base((char)va_arg(pf->arg, int), 10);
		else if (pf->mod_j == 1)
			*s = ft_itoa_base(va_arg(pf->arg, intmax_t), 10);
		else if (pf->mod_z == 1)
			*s = ft_itoa_base(va_arg(pf->arg, size_t), 10);
		else
			*s = (pf->type == 'd' || pf->type == 'i')
				? ft_itoa_base(va_arg(pf->arg, int), 10)
				: ft_itoa_base(va_arg(pf->arg, long), 10);
	}
	if (pf->type == 'u' || pf->type == 'U' || pf->type == 'o' || pf->type == 'O')
	{
		if (pf->mod_l)
			*s = ft_uitoa_base(va_arg(pf->arg, unsigned long), base, up);
		else if (pf->mod_h == 1 && is_lower)
			*s = ft_uitoa_base((unsigned short)va_arg(pf->arg, unsigned int), base, up);
		else if (pf->mod_h == 2 && is_lower)
			*s = ft_uitoa_base((unsigned char)va_arg(pf->arg, unsigned int), base, up);
		else if (pf->mod_h == 2 && !is_lower)
			*s = ft_uitoa_base((unsigned short)va_arg(pf->arg, unsigned int), base, up);
		else if (pf->mod_z == 1)
			*s = ft_uitoa_base(va_arg(pf->arg, size_t), base, up);
		else if (pf->mod_j == 1)
			*s = ft_uitoa_base(va_arg(pf->arg, uintmax_t), base, up);
		else
			*s = (is_lower)
				? ft_uitoa_base(va_arg(pf->arg, unsigned int), base, up)
				: ft_uitoa_base(va_arg(pf->arg, unsigned long), base, up);
	}
	if (pf->type == 'x' || pf->type == 'X')
	{
		if (pf->mod_l)
			*s = ft_uitoa_base(va_arg(pf->arg, unsigned long), 16, ((pf->type == 'x') ? 0 : 1));
		else if (pf->mod_h == 2)
			*s = ft_uitoa_base((unsigned char)va_arg(pf->arg, unsigned int), 16, ((pf->type == 'x') ? 0 : 1));
		else if (pf->mod_z)
			*s = ft_uitoa_base(va_arg(pf->arg, size_t), 16, ((pf->type == 'x') ? 0 : 1));
		else if (pf->mod_j)
			*s = ft_uitoa_base(va_arg(pf->arg, uintmax_t), 16, ((pf->type == 'x') ? 0 : 1));
		else
			*s = ft_uitoa_base(va_arg(pf->arg, unsigned int), 16, ((pf->type == 'x') ? 0 : 1));
	}
	if (pf->type == 'p')
	{
		tmp_str = ft_uitoa_base(va_arg(pf->arg, unsigned long long), 16, 0);
		*s = ft_strjoin("0x", tmp_str);
		ft_strdel(&tmp_str);
	}
}
