# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: QFM <quentin.feuillade33@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/10 16:04:23 by QFM               #+#    #+#              #
#    Updated: 2019/12/11 16:39:59 by QFM              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPPFLAGS = -lSDL2
COMPILER = clang++

NAME = RayTracer

S_MAT =	Material.cpp
S_OBJ = Obj_group.cpp Obj.cpp Polygon.cpp
S_VEC = Vector.cpp
S_CAM = Camera.cpp
S_HIT = Hit.cpp
S_RAY = Ray.cpp
S_RCS = windows_test.cpp material_parser.cpp

SMAT = $(addprefix Material/, $(S_MAT))
SOBJ = $(addprefix OBJ/, $(S_OBJ))
SVEC = $(addprefix Vector/, $(S_VEC))
SCAM = $(addprefix Camera/, $(S_CAM))
SHIT = $(addprefix Hit/, $(S_HIT))
SRAY = $(addprefix Ray/, $(S_RAY))

SRCS = $(addprefix srcs/, $(SMAT) $(SOBJ) $(SVEC) $(SCAM) $(SHIT) $(SRAY) $(S_RCS))

all: $(NAME)

$(NAME):
	$(COMPILER) $(CPPFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all