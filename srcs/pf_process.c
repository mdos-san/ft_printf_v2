#include "libftprintf.h"

void	pf_process(t_pf *pf)
{
	char	*s;

	if (pf->type == 's')
		s = va_arg(pf->arg, char *);
	if (pf->type == 'd' || pf->type == 'i')
		s = ft_itoa_base(va_arg(pf->arg, int), 10);
	if (pf->type == 'u')
		s = ft_uitoa_base(va_arg(pf->arg, int), 10);
	if (pf->type == 'o')
		s = ft_uitoa_base(va_arg(pf->arg, int), 8);
	if (pf->type == 'x')
		s = ft_uitoa_base(va_arg(pf->arg, int), 16);
	pf_buffer_add(pf, s);
}
