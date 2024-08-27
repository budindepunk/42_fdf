#include "fdf.h"

int	*split_atoi(t_fdf *data, char *line)
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