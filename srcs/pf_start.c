#include "libftprintf.h"

static void	out(t_pf *pf, unsigned int i)
{
	if (pf->input[i] == '%')
		pf->status = STATUS_IN;
	else
	{
		pf->buffer[pf->index] = pf->input[i];
		++pf->index;
		if (pf->index == PF_BUFFER)
		{
			write(1, pf->buffer, PF_BUFFER);
			pf->index = 0;
			++pf->number_buffer;
		}
	}
}

static void in(t_pf *pf, unsigned int i)
{
	if (ft_strchr(pf->list_types, pf->input[i]))
	{
		pf->type = pf->input[i];
		pf_process(pf);
		pf->status = STATUS_OUT;
	}
	else
	{
		pf->status = STATUS_OUT;
		pf->buffer[pf->index] = pf->input[i];
		++pf->index;
		if (pf->index == PF_BUFFER)
		{
			write(1, pf->buffer, PF_BUFFER);
			pf->index = 0;
			++pf->number_buffer;
		}
	}
}

void		pf_start(t_pf *pf)
{
	unsigned int	i;

	i = 0;
	while (pf->input[i])
	{
		if (pf->status == STATUS_OUT)
			out(pf, i);
		else if (pf->status > 0)
			in(pf, i);
		++i;
	}
}
