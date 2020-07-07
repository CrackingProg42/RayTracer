CPPFLAGS = -IE:\mingw_dev_lib\include -LE:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2
COMPILER = g++

NAME = TinyRt

S_RCS = main.cpp utils.cpp render.cpp

SRCS = $(addprefix srcs/, $(S_RCS))

all: $(NAME)

$(NAME):
	$(COMPILER) $(SRCS) $(CPPFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all