#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define PF_BUFFER 1024

/*
**|
**|	Description of struct s_pf
**|
**|	input:	char * containing the str given in ft_printf
**|	buffer:	Buffer to print on stdout, size is given in define PF_BUFFER
**|	index:	index of the current last char of the buffer.
**|	number_buffer:	Is the number of buffer printed totaly
**|
*/

typedef struct		s_pf
{
	char			*input;
	char			buffer[PF_BUFFER + 1];
	unsigned int	index;
	unsigned int	number_buffer;
}					t_pf;

int		ft_printf(char *str, ...);
t_pf	pf_init(char *str);

#endif
