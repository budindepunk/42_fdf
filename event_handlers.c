/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:08:52 by csilva-r          #+#    #+#             */
/*   Updated: 2024/09/01 17:09:14 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_handler(int button, int x, int y, void *param)
{
	if (!button || !x || !y || !param)
		return  (0);
	return (0);
}

int	keypress_handler(int keysym, void *param)
{
	t_fdf	*data;
	int		i;

	data = (t_fdf *)param;
	if (keysym == XK_Escape)
	{
		i = 0;
		while(i < data->rows)
			free(data->map[i++]);
		free(data->map);
		mlx_destroy_image(data->mlx, data->image);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		exit (0);
	}
	return (0);
}
/*
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
*/
int	close_handler(void *param)
{
	t_fdf	*data;
	int		i;

	data = (t_fdf *)param;
	mlx_destroy_image(data->mlx, data->image);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	i = 0;
	while(++i <= data->rows)
		free(data->map[i]);
	exit (0);
}
