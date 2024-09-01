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
	char	*temp;

	data->rows = 0;
	data->cols = 0;
	temp = get_next_line(fd);
	line = ft_split(temp, ' ');
	free(temp);
	while (line[data->cols])
	{
		free(line[data->cols]);
		data->cols++;
	}
	free(line);
	data->rows++;
	temp = get_next_line(fd);
	while (temp)
	{
		data->rows++;
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
}
/*aca arriba free lo que sale de gnl // catch empty file error*/

static int	get_scale_factor(t_fdf *data)
{
	double	max_scale_x;
	double	max_scale_y;

	max_scale_x = (WIDTH / (data->cols + data->rows)) * sqrt(2);
	max_scale_y = (HEIGHT / (data->cols + data->rows)) * sqrt(3);
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

	all_points = malloc(sizeof(t_pair) * (data->rows * data->cols));
	scale = get_scale_factor(data);
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->cols)
		{
			point.x = j * scale;
			point.y = i * scale;
			point.z = data->map[i][j] * scale;
			all_points[(i * data->cols) + j] = project(point, data);
			j++;
		}
		i++;
	}
	return (all_points);
}

static t_pair	*error_and_return(void)
{
	ft_putendl_fd("Error opening file.", 2);
	return (NULL);
}

t_pair	*parse_map(t_fdf *data, char *file)
{
	int		fd;
	int		i;
	char	*line;
	t_pair	*all_points;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (error_and_return());
	set_dimensions(data, fd);
	close(fd);
	data->map = malloc(sizeof(int *) * data->rows);
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
