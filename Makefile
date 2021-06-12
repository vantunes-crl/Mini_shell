NAME = Mini_shell

FLAGS = -lreadline

LIBFT = ./ft_libft/libft.a

SRCS = mini_shell.c exec_args.c parse.c prompet.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) bonus -C ft_libft
	@gcc $(OBJS) $(FLAGS) $(LIBFT) -o $(NAME)

all:
	$(NAME)
clean:
	rm -rf $(NAME) $(OBJS)