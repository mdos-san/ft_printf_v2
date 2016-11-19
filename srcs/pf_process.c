#include "libftprintf.h"

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
		s = va_arg(pf->arg, char *);
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
	width(pf, s);
	pf_buffer_add(pf, s);
}
