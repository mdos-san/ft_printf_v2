/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:09:10 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/21 12:42:29 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_pf	pf_init(char *str, va_list ap)
{
	t_pf	pf;

	pf.input = str;
	pf.index = 0;
	pf.number_buffer = 0;
	pf.status = 0;
	pf.width = 0;
	pf.precision = 0;
	pf.f_zero = 0;
	pf.width = 0;
	pf.precision = 0;
	pf.list_flags = "+ -0#";
	pf.list_types = "cCsSdDiuUoOxXp";
	pf.list_mod = "lhjz";
	va_copy(pf.arg, ap);
	return (pf);
}
