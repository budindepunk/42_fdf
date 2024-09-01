/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:10:34 by csilva-r          #+#    #+#             */
/*   Updated: 2024/09/01 17:27:31 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_offset(int size_x, int min_x, int total)
{
	int	desired;
	int	offset;

	desired = (total - size_x) / 2;
	offset = desired - min_x;
	return (offset);
}

t_pair	center_offsets(t_fdf *data, t_pair *all_points)
{
	t_pair	sizes;
	t_pair	mins;
	t_pair	maxes;
	t_pair	offsets;
	int		i;

	mins = (t_pair){.x = INT_MAX, .y = INT_MAX};
	maxes = (t_pair){.x = INT_MIN, .y = INT_MIN};
	i = 0;
	while (i < (data->rows * data->cols))
	{
		if (all_points[i].x < mins.x)
			mins.x = all_points[i].x;
		if (all_points[i].x > maxes.x)
			maxes.x = all_points[i].x;
		if (all_points[i].y < mins.y)
			mins.y = all_points[i].y;
		if (all_points[i].y > maxes.y)
			maxes.y = all_points[i].y;
		i++;
	}
	sizes = (t_pair){.x = maxes.x - mins.x, .y = maxes.y - mins.y};
	offsets.x = get_offset(sizes.x, mins.x, WIDTH);
	offsets.y = get_offset(sizes.y, mins.y, HEIGHT);
	return (offsets);
}

t_pair	translate(t_pair offsets, t_pair point)
{
	t_pair	offgeset;

	offgeset.x = point.x + offsets.x;
	offgeset.y = point.y + offsets.y;
	return (offgeset);
}

void	translate_all(t_pair offset, t_pair *all_points, t_fdf *data)
{
	int	i;

	i = 0;
	while (i < (data->rows * data->cols))
	{
		all_points[i] = translate(offset, all_points[i]);
		i++;
	}
}
