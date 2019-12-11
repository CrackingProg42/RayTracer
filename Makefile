# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 16:04:23 by QFM               #+#    #+#              #
#    Updated: 2019/12/10 17:08:06 by QFM              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPPFLAGS = -lSDL2
COMPILER = clang++

NAME = RayTracer

S_MAT =	Material.cpp
S_OBJ = Obj_group.cpp Obj.cpp Polygon.cpp
S_VEC = Vector.cpp
S_RCS = windows_test.cpp

SMAT = $(addprefix Material/, $(S_MAT))
SOBJ = $(addprefix OBJ/, $(S_OBJ))
SVEC = $(addprefix Vector/, $(S_VEC))

SRCS = $(addprefix srcs/, $(SMAT) $(SOBJ) $(SVEC) $(S_RCS))

all: $(NAME)

$(NAME):
	$(COMPILER) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all