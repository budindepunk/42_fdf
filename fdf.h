/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:46:51 by csilva-r          #+#    #+#             */
/*   Updated: 2024/09/01 14:47:08 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "includes/mlx_linux/mlx.h"
# include "includes/libft/libft.h"
# include <X11/keysym.h>
# include <X11/X.h>
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
# define BLACK 0x000000

/* structs */
typedef struct s_pair
{
	int		x;
	int		y;
}		t_pair;

typedef struct s_thruple
{
	int	x;
	int	y;
	int	z;
}		t_thruple;

typedef struct s_fdf
{
	t_pair	*proj;
	void	*mlx;
	void	*window;
	void	*image;
	char	*buffer;
	int		bits_pixel;
	int		size_line;
	int		endian;
	int		cols;
	int		rows;
	int		**map;
}		t_fdf;

/* utils */
int		*split_atoi(t_fdf *data, char *line);

/* events */
int		mouse_handler(int button, int x, int y, void *param);
int		keypress_handler(int keysym, void *param);
int		close_handler(void *param);
void	cleanup_exit(t_fdf *data, int error);

/* map */
void	parse_map(t_fdf *data, char *file);

/* draw */
t_pair	project(t_thruple vertex, t_fdf *data);
t_pair	center_offsets(t_fdf *data);
t_pair	translate(t_pair offsets, t_pair point);
void	translate_all(t_pair offset, t_fdf *data);
void	draw_all(t_fdf *data, int to_center);
void	draw_line(t_fdf *data, t_pair start, t_pair end);
void	clear_window(t_fdf *data);

#endif
