# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 23:01:54 by snicolet          #+#    #+#              #
#    Updated: 2016/01/07 23:08:23 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

all: $(NAME)

$(NAME):
	$(CC) -Wall -Wextra -Werror main.c -o $(NAME) -I ../libft/ -L../libft -lft

clean:
	rm -f main.o

re: fclean all

fclean: clean
	rm -f $(NAME)
