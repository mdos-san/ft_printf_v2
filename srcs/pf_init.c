#include "libftprintf.h"

t_pf	pf_init(char *str)
{
	t_pf	pf;

	pf.input = str;
	pf.index = 0;
	pf.number_buffer = 0;
	return (pf);
}
