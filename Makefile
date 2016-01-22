# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 23:01:54 by snicolet          #+#    #+#              #
#*   Updated: 2016/01/09 23:15:33 by snicolet         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
LIBFT=../libft
OBJ = main.o sorter.o msort.o display.o lsdir.o sizesort.o rdir.o sizetobuff.o \
	  parser.o aligner.o cleaner.o
FLAGS=-Wall -Wextra -Werror -Weverything
CC=clang

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
