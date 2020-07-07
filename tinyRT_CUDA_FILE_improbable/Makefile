COMPILER = nvcc

NAME = TinyRt

S_RCS = main.cu utils.cu render.cu

SRCS = $(addprefix srcs/, $(S_RCS))

all: $(NAME)

$(NAME):
	$(COMPILER) $(SRCS) -o $(NAME) -arch=sm_35 -rdc=true

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all