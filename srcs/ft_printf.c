#include "libftprintf.h"

int	ft_printf(char *str, ...)
{
	t_pf			pf;
	va_list			ap;

	if (str == NULL)
		return (-1);
	va_start(ap, str);
	pf = pf_init(str, ap);
	pf_start(&pf);
	if (pf.index > 0)
		write(1, pf.buffer, pf.index);
	return (pf.number_buffer * PF_BUFFER + pf.index);
}
