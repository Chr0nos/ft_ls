# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/07 23:01:54 by snicolet          #+#    #+#              #
#    Updated: 2016/04/28 19:24:23 by snicolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls
LIBFT=./libft/
OBJ = main.o sorter.o display.o lsdir.o sizesort.o rdir.o sizetobuff.o \
	  parser.o cleaner.o posix.o file.o timeloader.o path.o display_inode.o \
	  ltsort.o display_file.o params_sort.o
FLAGS=-Wall -Wextra -Werror -Weverything
CC=clang

all: $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -I $(LIBFT)

$(LIBFT)libft.a:
	make -C $(LIBFT) BTREE=""

$(NAME): $(LIBFT)libft.a $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -L../libft -lft

clean:
	rm -f $(OBJ)

re: fclean all

fclean: clean
	rm -f $(NAME)
