#include "libftprintf.h"

void	pf_buffer_add(t_pf *pf, char *str)
{
	if (str != NULL && str[0] != '\0')
	{
		if (pf->index == PF_BUFFER)
		{
			write(1, pf->buffer, PF_BUFFER);
			pf->index = 0;
			++pf->number_buffer;
		}
		if (ft_strlen(str) + pf->index <= PF_BUFFER)
		{
			ft_strcpy(pf->buffer + pf->index, str);
			pf->index += ft_strlen(str);
		}
		else
		{
			pf->buffer[pf->index] = str[0];
			++pf->index;
			pf_buffer_add(pf, str + 1);
		}
	}
}

void	pf_buffer_add_null(t_pf *pf)
{
		if (pf->index == PF_BUFFER)
		{
			write(1, pf->buffer, PF_BUFFER);
			pf->index = 0;
			++pf->number_buffer;
		}
		if (1 + pf->index <= PF_BUFFER)
		{
			ft_strcpy(pf->buffer + pf->index, "\0");
			pf->index += 1;
		}
		else
		{
			pf->buffer[pf->index] = '\0';
			++pf->index;
		}
}
