# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 23:01:54 by snicolet          #+#    #+#              #
#    Updated: 2016/01/08 16:40:19 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
LIBFT=../libft
OBJ = main.o sorter.o display.o lsdir.o
FLAGS=-Wall -Wextra -Werror -Weverything

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -I $(LIBFT)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L../libft -lft

clean:
	rm -f $(OBJ)

re: fclean all

fclean: clean
	rm -f $(NAME)
