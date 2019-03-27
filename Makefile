# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 15:42:19 by sid-bell          #+#    #+#              #
#    Updated: 2019/03/26 11:14:06 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=shell
FLAGS= -Wall -Wextra -Werror
all:$(NAME)
$(NAME):
		@make -C libft
		@gcc $(FLAGS) -c *.c env/*.c builtins/*.c tools/*.c termcap/*.c
		@gcc $(FLAGS) *.o libft/libft.a -o $(NAME) -ltermcap
clean:
		@make -C libft/ clean
		@rm -rf *.o
fclean: clean
		@make -C libft/ fclean
		@rm -rf $(NAME)
re:fclean
		@make all