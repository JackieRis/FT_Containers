# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/11 22:44:27 by tnguyen-          #+#    #+#              #
#    Updated: 2023/02/15 23:56:04 by tnguyen-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= Containers

HEADERS = Vector/vector.hpp \
		Stack/stack.hpp \
		Iterators/iterator.hpp \
		Iterators/reverse_iterator.hpp \
		Utils/enableIf.hpp \
		Utils/equal.hpp \
		Utils/isIntegral.hpp \
		Utils/lexicographical_compare.hpp \
		Utils/pair.hpp

SRCS	= main.cpp

OBJ	= ${SRCS:.cpp=.o}

CC = clang++

FLAGS = -fsanitize=address -Wall -Werror -Wextra -std=c++98 -I.

all: ${NAME}

%.o:%.cpp easyfind.hpp
	${CC} ${FLAGS} -c $< -o $@

${NAME}:    ${OBJ}
	$(CC) ${FLAGS} $(OBJ) -o $(NAME)

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all