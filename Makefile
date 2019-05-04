# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 15:42:19 by sid-bell          #+#    #+#              #
#    Updated: 2019/04/25 22:22:18 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=21sh
FLAGS= -Wall -Wextra -Werror
all:$(NAME)
$(NAME):
		make -C libft
		gcc $(FLAGS) -g -c *.c env/*.c builtins/*.c tools/*.c autocomplete/*.c history/*.c redirections/*.c parser/*.c term_cap/*.c exec/*.c
		gcc $(FLAGS) -g *.o libft/libft.a -o $(NAME) -l termcap
clean:
		make -C libft/ clean
		rm -rf *.o
fclean: clean
		make -C libft/ fclean
		rm -rf $(NAME)
re:fclean
		make all
		make clean
