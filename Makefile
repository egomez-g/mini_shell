CC = cc
CFLAGS = -Wall -Werror -Wextra 

NAME = mini_shell

SRCS =	main.c 				\
		parse/parse.c		\
		parse/list_cmd.c	\
		parse/file_finder.c	\

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(OBJS) -o $(NAME) -Llibft/ -lft -lreadline

libft/libft.a:
	make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean $(NAME)
	make -C libft/ re

.PHONY: clean fclean re

del:
	@./a.out