NAME = Mini_shell

FLAGS = -lreadline -g

LIBFT = ./ft_libft/libft.a

SRCS = mini_shell.c exec_args.c parse.c prompt.c builtings.c builtings2.c redirect.c  heredoc.c simple_redi.c utils.c main_process.c quotes.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) bonus -C ft_libft
	@gcc $(OBJS) $(FLAGS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	$(MAKE) clean -C ft_libft
	rm -rf $(OBJS)

fclean:
	rm -rf $(NAME) $(OBJS)

re: fclean all clean
	