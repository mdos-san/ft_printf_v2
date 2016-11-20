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
	pf.list_flags = "+ -0#";
	pf.list_types = "csdDiuUoOxXp";
	va_copy(pf.arg, ap);
	return (pf);
}
