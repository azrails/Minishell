#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2020/11/19 19:09:10 by wsallei           #+#    #+#             *#
#*   Updated: 2020/11/19 19:09:12 by wsallei          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

.PHONY: all clean fclean

NAME = minishell

LIBFT = -L libft -lft

SRCS = src/parser/main.c \
		src/parser/toks.c \
		src/parser/tool.c

O = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	clang $(FLAG) -g -c $< -o $@

$(NAME): $(O)
		make -C libft
		clang -o $(NAME) $(O) $(LIBFT)

clean:
		make -C libft clean
		rm -f $(O)

fclean:
		make -C libft fclean
		rm -f $(O)
		rm -f $(NAME)

re: fclean all