# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdos-san <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 12:59:09 by mdos-san          #+#    #+#              #
#    Updated: 2016/11/30 15:57:48 by mdos-san         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

COMPILER=	gcc
FLAGS=		-Wall -Wextra -Werror -c
INCLUDES=	-I ./includes

TMP_C=		ft_memset.c		ft_bzero.c		ft_memcpy.c\
			ft_memccpy.c	ft_memmove.c	ft_memchr.c\
			ft_memcmp.c		ft_strlen.c		ft_strcpy.c\
			ft_strncpy.c	ft_strcat.c		ft_strncat.c\
			ft_strlcat.c	ft_strchr.c		ft_strrchr.c\
			ft_strstr.c		ft_strnstr.c	ft_strcmp.c\
			ft_strncmp.c	ft_isalpha.c	ft_isdigit.c\
			ft_isalnum.c	ft_isascii.c	ft_isprint.c\
			ft_toupper.c	ft_tolower.c	ft_atoi.c\
			ft_memalloc.c	ft_memdel.c		ft_strnew.c\
			ft_strdel.c		ft_strclr.c		ft_striter.c\
			ft_striteri.c	ft_strmap.c		ft_strmapi.c\
			ft_strequ.c		ft_strnequ.c	ft_strdup.c\
			ft_strsub.c		ft_strjoin.c	ft_strtrim.c\
			ft_putchar.c	ft_putchar_fd.c	ft_putstr.c\
			ft_putstr_fd.c	ft_putendl.c	ft_putendl_fd.c\
			ft_strsplit.c	ft_putnbr.c		ft_putnbr_fd.c\
			ft_itoa.c		ft_lstnew.c		ft_lstdelone.c\
			ft_lstdel.c		ft_lstadd.c		ft_lstiter.c\
			ft_lstmap.c		ft_lstnew_cpy.c	get_next_line.c\
			ft_strjoin_del.c\
			str_array_new.c\
			str_array_count.c\
			str_array_dup.c\
			str_array_del.c\
			str_array_add.c\
			str_array_sub.c\
			str_array_find.c\
			ft_putnbrl.c
SRC_C=$(TMP_C:%=libft/%)
SRC_O=$(SRC_C:.c=.o)
DEL_1=$(TMP_C:.c=.o)

TMP_C_2 = \
		 	ft_printf.c\
			pf_init.c\
			pf_start.c\
			pf_process.c\
			pf_buffer_add.c\
			ft_itoa_base.c\
			get_wchar.c\
			get_wstr.c\
			va_get.c\
			parse.c\
			parse_fct.c\
			width.c\
			precision.c
SRC_C_2=$(TMP_C_2:%=srcs/%)
SRC_O_2=$(SRC_C_2:.c=.o)
DEL_2=$(TMP_C_2:.c=.o)

.PHONY: all clean norm

all: $(NAME)

$(NAME): includes/libft.h $(DEL_1) $(DEL_2)
	@echo "Creating libftprintf.a..."
	@ar rc $(NAME) $(DEL_1) $(DEL_2)
	@ranlib $(NAME)
	@echo "Done !"

includes/libft.h:
	cp libft/includes/libft.h includes

%.o: libft/%.c
	@echo "Compiling $<"
	@$(COMPILER) $(FLAGS) $(INCLUDES) $<

%.o: srcs/%.c
	@echo "Compiling $<"
	@$(COMPILER) $(FLAGS) $(INCLUDES) $<

clean: 
	@echo "Removing *.o"
	@rm -rf $(DEL_1) $(DEL_2)
	@echo "Done"

fclean: clean
	@echo "Removing libftprintf.a"
	@rm -rf libftprintf.a
	@echo "Done"

re: fclean all

norm	:
	@norminette srcs includes
