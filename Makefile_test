SRCS	= test.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= test
CC	= cc
CFLAGS	= -g -Wall -Wextra -Werror -I.

# libft
LIBFT = includes/libft/libft.a

# linker flags
LIBFT_FLAGS = -Lincludes/libft -lft
MLX_FLAGS = -Lincludes/mlx_linux -lmlx_Linux -Iincludes/mlx_linux
SYS_FLAGS = -L/usr/lib -lXext -lX11 -lm -lz
LFLAGS	=  $(MLX_FLAGS) $(SYS_FLAGS) $(LIBFT_FLAGS)

all:	$(NAME)

$(LIBFT):
	$(info Building libft...)
	@make -s -C includes/libft

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	$(info Done!)

%.o: %.c
	$(info Building fdf...)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $@ -c $<

clean:
	@rm $(OBJS)
	@make -s -C includes/libft clean
	$(info Removed!)
fclean: clean
	@rm $(NAME)
	@make -s -C includes/libft fclean

re:	fclean all

#	-L + directory where to look for libraries (*.o, *.a)
#		-l + name of library file (without prefix "lib"). i.g., -lft gets (lib)ft, -lmlx gets (lib)mlx
#	-I + directory where to look for header files
