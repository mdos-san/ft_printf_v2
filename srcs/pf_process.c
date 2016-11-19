#include "libftprintf.h"

void	pf_process(t_pf *pf)
{
	char	*s;

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
		pf_buffer_add(pf, "0x");
		s = ft_uitoa_base(va_arg(pf->arg, unsigned long long), 16);
	}
	pf_buffer_add(pf, s);
}
