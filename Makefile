SRCS	= test.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= test
CC	= cc
CFLAGS	= -g -Wall -Wextra -Werror -I.
LFLAGS	= -Lincludes/mlx_linux -lmlx_Linux -Iincludes/mlx_linux -L/usr/lib -lXext -lX11 -lm -lz -Lincludes/libft -lft

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ -c $<

clean:
	rm $(OBJS)
fclean: clean
	rm $(NAME)
re:	fclean all
