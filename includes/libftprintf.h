#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define PF_BUFFER 1024
# define STATUS_OUT 0
# define STATUS_IN 1

/*
**|
**|	Description of struct s_pf
**|
**|	input:	char * containing the str given in ft_printf
**|	buffer:	Buffer to print on stdout, size is given in define PF_BUFFER
**|	index:	index of the current last char of the buffer.
**|	number_buffer:	Is the number of buffer printed totaly
**|	arg:	va_list
**|	status:	Actual Status of printf (ex: in flag, out, ..)
**| list_flags: char *, each char is a flag managed.
**| list_types: char *, each char is a type managed.
**|	type: actual type
*/

typedef struct		s_pf
{
	char			*input;
	char			buffer[PF_BUFFER + 1];
	unsigned int	index;
	unsigned int	number_buffer;
	va_list			arg;
	char			status;
	char			*list_flags;
	char			*list_types;
	char			type;
}					t_pf;

int		ft_printf(char *str, ...);
t_pf	pf_init(char *str, va_list ap);
void	pf_start(t_pf *pf);
void	pf_process(t_pf *pf);
void	pf_buffer_add(t_pf *pf, char *str);
char	*ft_itoa_base(int nbr, unsigned int base);
char	*ft_uitoa_base(unsigned int nbr, unsigned int base);

#endif
