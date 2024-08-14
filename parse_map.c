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

void print_map(t_fdf *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->columns)
		{
			ft_printf("%d ", data->map[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	parse_map(t_fdf *data, char *file)
{
	int		fd;
	int 	i;
	char 	*line;

	fd = open(file, O_RDONLY);
    if (fd <= 0)
	{
		ft_printf("Error opening file.\n");
		return ;
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
	print_map(data);
}
