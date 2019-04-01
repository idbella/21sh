# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 15:42:19 by sid-bell          #+#    #+#              #
#    Updated: 2019/04/01 02:29:22 by sid-bell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=21sh
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