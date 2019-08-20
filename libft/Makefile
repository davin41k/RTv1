# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dshereme <dshereme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/25 17:40:20 by dshereme          #+#    #+#              #
#    Updated: 2019/03/08 20:59:12 by dshereme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re


NAME	:=	libft.a

CC		:=	gcc

FLAGS	:=	-Wall -Werror -Wextra

INCLUDES = ./

SRC		:=	ft_strlen.c\
			ft_strcpy.c\
			ft_memset.c\
			ft_strdup.c\
			ft_strncpy.c\
			ft_strcat.c\
			ft_strncat.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memchr.c\
			ft_memccpy.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isalpha.c\
			ft_isprint.c\
			ft_isalnum.c\
			ft_atoi.c\
			ft_strcmp.c\
			ft_strncmp.c\
			ft_strstr.c\
			ft_strchr.c\
			ft_memcmp.c\
			ft_strrchr.c\
			ft_memmove.c\
			ft_strlcat.c\
			ft_strnstr.c\
			\
			ft_memalloc.c\
			ft_memdel.c\
			ft_strnew.c\
			ft_strdel.c\
			ft_strclr.c\
			ft_striter.c\
			ft_striteri.c\
			ft_strmap.c\
			ft_strmapi.c\
			ft_strequ.c\
			ft_strnequ.c\
			ft_strsub.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_putchar.c\
			ft_putstr.c\
			ft_putendl.c\
			ft_putnbr.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_itoa.c\
			ft_strsplit.c\
			\
			ft_lstnew.c\
			ft_lstdelone.c\
			ft_lstadd.c\
			ft_lstiter.c\
			ft_lstmap.c\
			ft_lstdel.c\
			\
			ft_swap.c\
			ft_lstcount.c\
			ft_iscase.c\
			ft_countdigit.c\
			ft_lstcount.c\
			ft_lstgetlast.c\
			ft_getnbr.c\
			\
			get_next_line.c\
			clean_text.c

OBJ		:= $(SRC:.c=.o)	

$(NAME):
	@$(CC) -c $(FLAGS) $(SRC) -I $(INCLUDES)
	@ar rc $(NAME) $(OBJ)

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
