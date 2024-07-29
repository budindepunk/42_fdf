#ifndef FDF_H
# define FDF_H

# include "includes/mlx_linux/mlx.h"
# include "includes/libft/libft.h"

# define ESCAPE 9

typedef struct s_fdf
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*buffer;
	int	bits_pixel;
	int	size_line;
	int	endian;
}		t_fdf;

# define WIDTH 640
# define HEIGHT 380

#endif
