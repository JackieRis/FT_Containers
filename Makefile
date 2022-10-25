# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:26:21 by tnguyen-          #+#    #+#              #
#    Updated: 2022/10/19 00:27:30 by tnguyen-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Containers

SRCS	= main.cpp

OBJ	= ${SRCS:.cpp=.o}

CC = c++

FLAGS = -fsanitize=address -g3 -Wall -Werror -Wextra -std=c++98 -I.

all: ${NAME}

%.o:%.cpp vector.hpp iterator.hpp isIntegral.hpp enableIf.hpp equal.hpp stack.hpp Makefile
	${CC} ${FLAGS} -c $< -o $@

${NAME}:    ${OBJ}
	$(CC) ${FLAGS} $(OBJ) -o $(NAME)

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all
