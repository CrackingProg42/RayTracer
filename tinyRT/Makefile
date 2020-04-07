# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 16:04:23 by QFM               #+#    #+#              #
#    Updated: 2019/12/11 11:41:57 by QFM              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPPFLAGS = -fopenmp -IE:\mingw_dev_lib\include -LE:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
COMPILER = g++

NAME = TinyRt

S_RCS = main.cpp utils.cpp

SRCS = $(addprefix srcs/, $(S_RCS))

all: $(NAME)

$(NAME):
	$(COMPILER) $(SRCS) $(CPPFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all