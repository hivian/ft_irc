# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hivian <hivian@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/07 17:08:16 by hivian            #+#    #+#              #
#    Updated: 2017/02/13 16:33:21 by hivian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_strlen.c\
	  ft_strwlen.c\
	  ft_nbrlen.c\
      ft_bzero.c\
      ft_memcpy.c\
      ft_memccpy.c\
      ft_memset.c\
      ft_memchr.c\
      ft_memcmp.c\
      ft_memmove.c\
      ft_strdup.c\
      ft_strndup.c\
      ft_strcpy.c\
      ft_putchar.c\
	  ft_putwchar.c\
      ft_putstr.c\
	  ft_putwstr.c\
      ft_tolower.c\
      ft_toupper.c\
      ft_isalpha.c\
      ft_isdigit.c\
      ft_isalnum.c\
      ft_strchr.c\
      ft_strrchr.c\
      ft_putnbr.c\
	  ft_putnbr_base.c\
      ft_strcmp.c\
      ft_strdel.c\
      ft_putendl.c\
      ft_strclr.c\
      ft_memdel.c\
      ft_putnbr_fd.c\
      ft_putchar_fd.c\
      ft_putstr_fd.c\
      ft_putendl_fd.c\
      ft_strncpy.c\
      ft_atoi.c\
      ft_isascii.c\
      ft_isprint.c\
      ft_isspace.c\
      ft_strstr.c\
      ft_strncat.c\
      ft_strcat.c\
      ft_strlcat.c\
      ft_strnstr.c\
      ft_strncmp.c\
      ft_strnequ.c\
      ft_strequ.c\
      ft_memalloc.c\
	  ft_realloc.c\
      ft_strtrim.c\
      ft_strnew.c\
      ft_striter.c\
      ft_striteri.c\
      ft_strmap.c\
      ft_strmapi.c\
      ft_strjoin.c\
	  ft_pathjoin.c\
      ft_strsub.c\
      ft_itoa.c\
	  ft_litoa.c\
	  ft_llitoa.c\
	  ft_uitoa.c\
	  ft_ulitoa.c\
      ft_strsplit.c\
	  ft_strsplit_to_int.c\
	  ft_strrev.c\
      ft_lstnew.c\
      ft_lstdelone.c\
      ft_lstdel.c\
      ft_lstadd.c\
      ft_lstiter.c\
      ft_lstmap.c\
	  ft_swap.c\
	  ft_strswap.c\
      get_next_line.c\
	  ft_printf.c\
	  istype.c\
	  count_format.c\
	  opt_cdisu.c\
	  opt_char.c\
	  opt_invalid.c\
	  opt_long.c\
	  opt_mega_long.c\
	  opt_pxxo.c\
	  opt_short.c\
	  opt_wide.c\
	  flags.c\
	  precision.c\
	  width.c\
	  ft_conv_base.c\
	  ft_set_unicode.c\
	  ft_atoi_dot.c\
	  ft_itoa_ndash.c\
	  ft_arrdup.c\
	  ft_arrlen.c\
	  ft_arrdel.c

OBJ = $(SRC:%.c=objs/%.o)

CC = gcc -c -Wall -Wextra -Werror
AR = ar -rc

SRC_DIR =		./srcs/
INCLUDE_DIR =	./incs/

WHITE       =   \033[0m
GREEN       =   \033[32m
BLUE        =   \033[1;34m
BLUE2       =   \033[36m
RED         =   \033[31m
GREY        =   \033[1;30m
YELLOW      =   \033[33m

all: objs $(NAME)

objs:
	@mkdir objs

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@ranlib $(NAME)

objs/%.o: $(SRC_DIR)/%.c
	@$(CC) -I $(INCLUDE_DIR) -o $@ -c $<

clean:
	@rm -rf objs

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm :
	@norminette $(SRC_DIR) $(INCLUDE_DIR)

.PHONY: all clean fclean re
