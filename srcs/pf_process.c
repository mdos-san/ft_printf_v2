#include "libftprintf.h"

static void flag(t_pf *pf, char **s)
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
}

static void precision(t_pf *pf, char **s)
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
	else if (pf->type == 'p' && pf->precision > length)
	{
		str = ft_strnew(pf->precision);
		ft_memset(str, '0', pf->precision);
		str[length - 4] = '0';
		str[length - 3] = 'x';
		*s = ft_strjoin(str + length - 4, *s + 2);
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

	pf->width = pf->width - ft_strlen(s);
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
		s = ft_strnew(1);
		s[0] = (char)va_arg(pf->arg, int);
	}
	if (pf->type == 's')
	{
		s = ft_strdup(va_arg(pf->arg, char *));
		if (s == NULL)
			s = ft_strdup("(null)");
	}
	if (pf->type == 'd' || pf->type == 'i')
		s = ft_itoa_base(va_arg(pf->arg, int), 10);
	if (pf->type == 'u')
		s = ft_uitoa_base(va_arg(pf->arg, unsigned int), 10);
	if (pf->type == 'o')
		s = ft_uitoa_base(va_arg(pf->arg, unsigned int), 8);
	if (pf->type == 'x')
		s = ft_uitoa_base(va_arg(pf->arg, unsigned int), 16);
	if (pf->type == 'p')
	{
		tmp_str = ft_uitoa_base(va_arg(pf->arg, unsigned long long), 16);
		s = ft_strjoin("0x", tmp_str);
		ft_strdel(&tmp_str);
	}
	flag(pf, &s);
	precision(pf, &s);
	(pf->f_minus == 0) ? width(pf, s) : 0;
	pf_buffer_add(pf, s);
	(pf->f_minus == 1) ? width(pf, s) : 0;
}
