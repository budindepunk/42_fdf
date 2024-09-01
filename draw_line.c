/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 14:52:09 by csilva-r          #+#    #+#             */
/*   Updated: 2024/09/01 17:26:20 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	paint_pixel(t_fdf *data, t_pair start, int color)
{
	int	pixel;

	if (start.x > WIDTH || start.y > HEIGHT || start.x < 0 || start.y < 0)
		return ;
	pixel = (start.y * data->size_line) + (4 * start.x);
	data->buffer[pixel + 0] = (color) & 0xFF;
	data->buffer[pixel + 1] = (color >> 8) & 0xFF;
	data->buffer[pixel + 2] = (color >> 16) & 0xFF;
	data->buffer[pixel + 3] = (color >> 24) & 0xFF;
}

static t_pair	get_signs(t_pair start, t_pair end)
{
	t_pair	sign;

	sign.x = (end.x - start.x > 0) - (start.x - end.x > 0);
	sign.y = (end.y - start.y > 0) - (start.y - end.y > 0);
	return (sign);
}

void	draw_line(t_fdf *data, t_pair start, t_pair end)
{
	t_pair	delta;
	t_pair	sign;
	int		err;
	int		new_err;

	delta = (t_pair){.x = abs(end.x - start.x), .y = abs(end.y - start.y)};
	err = ((delta.x > delta.y) * delta.x - (delta.x <= delta.y) * delta.y) / 2;
	sign = get_signs(start, end);
	while (TRUE)
	{
		paint_pixel(data, start, WHITE);
		if (start.x == end.x && start.y == end.y)
			break ;
		new_err = err;
		if (new_err > -(delta.x))
		{
			err -= delta.y;
			start.x += sign.x;
		}
		if (new_err < delta.y)
		{
			err += delta.x;
			start.y += sign.y;
		}
	}
}

void	draw_all(t_fdf *data, t_pair *all_points)
{
	int		i;
	int		j;
	int		ix;
	t_pair	offsets;

	offsets = center_offsets(data, all_points);
	translate_all(offsets, all_points, data);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			ix = (i * data->cols) + j;
			if ((j + 1) < data->cols)
				draw_line(data, all_points[ix], all_points[ix + 1]);
			if ((i + 1) < data->rows)
				draw_line(data, all_points[ix], all_points[ix + data->cols]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}
