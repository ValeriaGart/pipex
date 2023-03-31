LIBFT = ./libft/libft.a

NAME = pipex

SRCS =	src/pipex.c		\
		src/utils.c

SRCSB =	src/pipex_bonus.c				\
		src/utils_bonus.c				\
		src/free_bonus.c		\
		get_next_line/get_next_line.c	\
		get_next_line/get_next_line_utils.c

CC = cc

CFLAGS = -Wextra -Werror -Wall

INCL = -I ./incl

OBJS = $(SRCS:.c=.o)

OBJSB = $(SRCSB:.c=.o)

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT)

all:	$(NAME)

bonus: $(OBJSB)
	$(MAKE) -C ./libft
	$(CC) -o pipex_bonus $(CFLAGS) $(OBJSB) $(LIBFT)

clean:
	$(MAKE) clean -C ./libft
	rm -rf $(OBJS)
	rm -rf $(OBJSB)

fclean:	clean
	rm -rf $(NAME)
	rm -rf $(bonus)
	rm -rf pipex_bonus

re: fclean all

.PHONY: all clean fclean bonus re
