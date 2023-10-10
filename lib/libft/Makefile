# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 18:20:14 by rpinchas          #+#    #+#              #
#    Updated: 2023/10/10 13:18:39 by rpinchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=  libft.a
SRC := ft_atoi.c\
	ft_bzero.c\
	ft_calloc.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_itoa.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_putstr_fd.c\
	ft_split.c\
	ft_strchr.c\
	ft_strdup.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strmapi.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strtrim.c\
	ft_substr.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_lstnew.c\
	ft_lstadd_front.c\
	ft_lstsize.c\
	ft_lstlast.c\
	ft_lstadd_back.c\
	ft_lstdelone.c\
	ft_lstclear.c

PRINTF := ft_printf.c\
	ft_printf_utils.c

INC := -I./ -I/usr/include
OBJ := $(SRC:.c=.o)
OBJ_PRINTF := $(PRINTF:.c=.o)
CFLAGS := -Wall -Werror -Wextra
CC := cc
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_PRINTF)
	ar -rcs $(NAME) $(OBJ) $(OBJ_PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_PRINTF)

fclean: clean
	rm -f $(NAME) 
	rm -f *.so a.out

re: fclean all

bonus: $(OBJ) $(OBJ_PRINTF)
	ar -rcs $(NAME) $(OBJ) $(OBJ_PRINTF)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ)
