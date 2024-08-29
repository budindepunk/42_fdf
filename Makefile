SRCS	= fdf.c event_handlers.c parse_map.c draw_line.c projection.c utils.c translate.c
OBJS	= $(SRCS:%.c=%.o)
NAME	= fdf
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
	$(info Linking $(NAME)...)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	$(info Done!)

%.o: %.c
	$(info Building $@...)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@make -s -C includes/libft clean
	$(info Removed!)
fclean: clean
	@rm -f $(NAME)
	@make -s -C includes/libft fclean

re:	fclean all

#	-L + directory where to look for libraries (*.o, *.a)
#		-l + name of library file (without prefix "lib"). i.g., -lft gets (lib)ft, -lmlx gets (lib)mlx
#	-I + directory where to look for header files
