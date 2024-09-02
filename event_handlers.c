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

void	cleanup_exit(t_fdf *data, int error)
{
	int	i;

	i = 0;
	while (i < data->rows)
		free(data->map[i++]);
	free(data->map);
	free(data->proj);
	mlx_destroy_image(data->mlx, data->image);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	if (error)
		exit (1);
	exit (0);
}

int	mouse_handler(int button, int x, int y, void *param)
{
	if (!button || !x || !y || !param)
		return (0);
	return (0);
}

int	keypress_handler(int keysym, void *param)
{
	t_fdf	*data;
	t_pair	move;
	int		center;

	center = FALSE;
	move = (t_pair){.x = 0, .y = 0};
	data = (t_fdf *)param;
	if (keysym == XK_Escape)
		cleanup_exit(data, FALSE);
	else if (keysym == XK_Right)
		move.x = 10;
	else if (keysym == XK_Up)
		move.y = -10;
	else if (keysym == XK_Left)
		move.x = -10;
	else if (keysym == XK_Down)
		move.y = 10;
	else if (keysym == XK_space)
		center = TRUE;
	translate_all(move, data);
	clear_window(data);
	draw_all(data, center);
	return (0);
}

int	close_handler(void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	cleanup_exit(data, FALSE);
	return (0);
}
