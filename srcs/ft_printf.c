#include "libftprintf.h"

int	ft_printf(char *str, ...)
{
	t_pf			pf;
	unsigned int	i;

	pf = pf_init(str);
	i = 0;
	while (pf.input[i])
	{
		pf.buffer[pf.index] = pf.input[i];
		++pf.index;
		if (pf.index == PF_BUFFER)
		{
			write(1, pf.buffer, PF_BUFFER);
			pf.index = 0;
			++pf.number_buffer;
		}
		++i;
	}
	if (pf.index > 0)
		write(1, pf.buffer, pf.index);
	return (pf.number_buffer * PF_BUFFER + pf.index);
}
