NAME = Mini_shell

FLAGS = -lreadline

SRCS = shell.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	gcc $(OBJS) $(FLAGS) -L/ft_libft/libft.a -o $(NAME)

all:
	$(NAME)
clean:
	rm -rf $(NAME) $(OBJS)