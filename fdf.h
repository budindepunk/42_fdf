#ifndef FDF_H
# define FDF_H

# include "includes/mlx_linux/mlx.h"
# include "includes/libft/libft.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define ESCAPE 9
# define WIDTH 1280
# define HEIGHT 960
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

typedef struct s_thruple
{
	int		x;
	int		y;
    int     z;
}		t_thruple;

/* utils */
int		*split_atoi(t_fdf *data, char *line);

/* events */
int     mouse_handler(int button, int x, int y, void *param);
int     keypress_handler(int keysym, void *param);

/* map */
t_pair	*parse_map(t_fdf *data, char *file);

/* draw */
t_pair	project(t_thruple vertex, t_fdf *data);
t_pair 	get_offsets(t_fdf *data, t_pair *all_points);
t_pair	translate(t_pair offsets, t_pair point);
void	flatten_cube(t_fdf *data);
void	draw_all(t_fdf *data, t_pair *all_points);
void    draw_line(t_fdf *data, t_pair start, t_pair end);

#endif