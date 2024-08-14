#ifndef FDF_H
# define FDF_H

# include "includes/mlx_linux/mlx.h"
# include "includes/libft/libft.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

# define ESCAPE 9
# define WIDTH 640
# define HEIGHT 480
# define TRUE 1
# define FALSE 0

/* colors */
# define WHITE 0xFFFFFF

/* structs */
typedef struct s_fdf
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*buffer;
	int	bits_pixel;
	int	size_line;
	int	endian;
	int	columns;
	int	rows;
	int **map;
}		t_fdf;

typedef struct s_pair
{
	int		x;
	int		y;
}		t_pair;

/* events */
int     mouse_handler(int button, int x, int y, void *param);
int     keypress_handler(int keysym, void *param);
/* map */
void	parse_map(t_fdf *data, char *file);
void    draw_line(t_fdf *data, t_pair start, t_pair end);

#endif
