/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdos-san <mdos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:13:54 by mdos-san          #+#    #+#             */
/*   Updated: 2016/11/27 15:52:41 by mdos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define PF_BUFFER 2048
# define STATUS_OUT 0
# define STATUS_IN 1
# define STATUS_W 2
# define STATUS_W_END 3
# define STATUS_P 4
# define STATUS_P_END 5
# define SP 5
# define STATUS_P_PAR 6

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
**| width: width passed in placeholder
**| precision: precision passed in placeholder
**| f_plus:		Flag '+' status
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
	unsigned int	width;
	unsigned int	precision;
	char			p_given;
	char			f_plus;
	char			f_space;
	char			f_minus;
	char			f_zero;
	char			f_sharp;
	char			*list_mod;
	char			mod_l;
	char			mod_h;
	char			mod_j;
	char			mod_z;
	int				offset;
}					t_pf;

int					ft_printf(char *str, ...);
t_pf				pf_init(char *str, va_list ap);
void				pf_start(t_pf *pf);
void				pf_process(t_pf *pf);
void				pf_buffer_add(t_pf *pf, char *str);
void				pf_buffer_add_null(t_pf *pf);
void				pf_buffer_nadd(t_pf *pf, char *str, int n);
char				*ft_itoa_base(long long nbr, unsigned int base);
char				*ft_uitoa_base
						(unsigned long long nbr, unsigned int base, int up);
char				*get_wchar(int c);
char				*get_wstr(int *istr, unsigned int pre);
void				width(t_pf *pf, char *s);
void				va_get(t_pf *pf, char **s);
void				parse(t_pf *pf, unsigned int i);
void				width(t_pf *pf, char *s);
void				precision(t_pf *pf, char **s);
void				in_flag(t_pf *pf, unsigned int i);
void				go_out(t_pf *pf, unsigned int i);

#endif
