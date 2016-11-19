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

static void go_out(t_pf *pf, unsigned int i)
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

static void in(t_pf *pf, unsigned int i)
{
	if (pf->status < STATUS_W
		&& (ft_isdigit(pf->input[i]) || pf->input[i] == '*'))
	{
		pf->status = (ft_isdigit(pf->input[i + 1])) ? STATUS_W : STATUS_P;
		pf->width = (pf->input[i] == '*')
			? va_arg(pf->arg, int) : ft_atoi(pf->input + i);
	}
	else if (pf->status == STATUS_W)
		pf->status = (ft_isdigit(pf->input[i + 1])) ? STATUS_W : STATUS_P;
	else if (ft_strchr(pf->list_types, pf->input[i]))
	{
		pf->type = pf->input[i];
		pf_process(pf);
		pf->status = STATUS_OUT;
	}
	else
		go_out(pf, i);
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
