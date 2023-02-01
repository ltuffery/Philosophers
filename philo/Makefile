# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltuffery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 16:17:10 by ltuffery          #+#    #+#              #
#    Updated: 2023/02/01 18:40:14 by ltuffery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -g

NAME	=	philo

SRCS	=	main.c

OBJS	=	$(SRCS:.c=.o)

%.o:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $^ ../libft/libft.a -lpthread -o $@

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(NAME)

re:		fclean all

.PHONY:	re all clean fclean
