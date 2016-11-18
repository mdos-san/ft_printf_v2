#include "libftprintf.h"

void	pf_process(t_pf *pf)
{
	char	*s;
	if (pf->type == 's')
	{
		s = va_arg(pf->arg, char *);
		pf_buffer_add(pf, s);
	}
}
