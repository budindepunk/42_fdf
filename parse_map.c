/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:06:22 by csilva-r          #+#    #+#             */
/*   Updated: 2024/09/01 17:07:18 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_dimensions(t_fdf *data, int fd)
{
	char	**line;

	data->rows = 0;
	data->columns = 0;
	line = ft_split(get_next_line(fd), ' ');
	while (line[data->columns])
		data->columns++;
	free(line);
	data->rows++;
	while (get_next_line(fd))
		data->rows++;
}
/*aca arriba free lo que sale de gnl // catch empty file error*/

static int	get_scale_factor(t_fdf *data)
{
	double	max_scale_x;
	double	max_scale_y;

	max_scale_x = (WIDTH / (data->columns + data->rows)) * sqrt(2);
	max_scale_y = (HEIGHT / (data->columns + data->rows)) * sqrt(3);
	if (max_scale_x < max_scale_y)
		return ((int)(max_scale_x * 0.9));
	else
		return ((int)(max_scale_y * 0.9));
}

t_pair	*flatten_map(t_fdf *data)
{
	int			i;
	int			j;
	int			scale;
	t_pair		*all_points;
	t_thruple	point;

	all_points = malloc(sizeof(t_pair) * (data->rows * data->columns));
	scale = get_scale_factor(data);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			point.x = j * scale;
			point.y = i * scale;
			point.z = data->map[i][j] * scale;
			all_points[(i * data->columns) + j] = project(point, data);
			j++;
		}
		i++;
	}
	return (all_points);
}

t_pair	*parse_map(t_fdf *data, char *file)
{
	int		fd;
	int		i;
	char	*line;
	t_pair	*all_points;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
	{
		ft_printf("Error opening file.\n");
		return (NULL);
	}
	set_dimensions(data, fd);
	data->map = malloc(sizeof(int *) * data->rows);
	close(fd);
	fd = open(file, O_RDONLY);
	i = 0;
	while (i < data->rows)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->map[i] = split_atoi(data, line);
		free(line);
		i++;
	}
	all_points = flatten_map(data);
	return (all_points);
}
