COMPILER = g++

NAME = TinyRt

S_RCS = main.cpp utils.cpp render.cpp

SRCS = $(addprefix srcs/, $(S_RCS))

all: $(NAME)

$(NAME):
	$(COMPILER) $(SRCS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all