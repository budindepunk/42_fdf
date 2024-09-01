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
	t_fdf	*data;

	data = (t_fdf *)param;
	if (!param && !x && !y)
		return (0);
	if (button == 17)
	{
		mlx_destroy_image(data->mlx, data->image);
		mlx_destroy_window(data->mlx, data->window);
		exit (0);
	}
	return (0);
}

int	keypress_handler(int keysym, void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(data->mlx, data->image);
		mlx_destroy_window(data->mlx, data->window);
		exit (0);
	}
	return (0);
}
