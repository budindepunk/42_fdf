#include "fdf.h"

static int	*split_atoi(t_fdf *data, char *line)
{
	int	*row;
	char **temp;
	int i;

	temp = ft_split(line, ' ');
	row = malloc(sizeof(int) * data->columns);
	i = 0;
	while (temp[i])
	{
		row[i] = ft_atoi(temp[i]);
		i++;
	}
	free(temp);
	return (row);
}

static void set_dimensions(t_fdf *data, int fd)
{
	char **line;

	data->rows = 0;
	data->columns = 0;
	line = ft_split(get_next_line(fd), ' ');
	// todo: catch empty file error case
	while (line[data->columns])
		data->columns++;
	free(line);
	data->rows++;
	while (get_next_line(fd)) // todo: maybe the result of gnl will have to be freed
		data->rows++;
}

// instead of print, create a thruple for each value in the grid
t_pair *flatten_map(t_fdf *data)
{
	int i;
	int j;
	t_pair *all_points;
	t_thruple point;

	all_points = malloc(sizeof(t_pair) * (data->rows * data->columns));
	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			point.x = j * 30;
			point.y = i * 30;
			point.z = data->map[i][j] * 2;
			all_points[(i * data->columns) + j] = project(point, data);
			j++;
		}
		i++;
	}
	return (all_points);
}

t_pair*	parse_map(t_fdf *data, char *file)
{
	int		fd;
	int 	i;
	char 	*line;
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
/*
all_points = { [x, y], [x, y], [x, y], [x, y], [x, y], ... x 25 }
*/
void	draw_all(t_fdf *data, t_pair *all_points)
{
	int i = 0;
	int j;
	int index;

	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			index = (i * data->columns) + j;
			if ((j + 1) < data->columns)
				draw_line(data, all_points[index], all_points[index + 1]);
			if ((i + 1) < data->rows)
				draw_line(data, all_points[index], all_points[index + data->columns]);
			j++;
		}
		i++;
	}
}
