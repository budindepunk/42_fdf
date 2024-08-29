#include "fdf.h"

// static t_pair get_sizes(t_fdf *data, t_pair *all_points)
// {
// 	t_pair sizes;
// 	t_pair hold_min;
// 	t_pair hold_max;
// 	int i;

// 	hold_min.x = INT_MAX;
// 	hold_min.y = INT_MAX;
// 	hold_max.x = INT_MIN;
// 	hold_max.y = INT_MIN;
// 	i = 0;
// 	while (i < (data->rows * data->columns))
// 	{
// 		if (all_points[i].x < hold_min.x)
// 			hold_min.x = all_points[i].x;
// 		if (all_points[i].x > hold_max.x)
// 			hold_max.x = all_points[i].x;
// 		if (all_points[i].y < hold_min.y)
// 			hold_min.y = all_points[i].y;
// 		if (all_points[i].y > hold_max.y)
// 			hold_max.y = all_points[i].y;
// 		i++;
// 	}
//     ft_printf("mins: %d in x, %d in y\n", hold_min.x, hold_min.y);
//     ft_printf("maxs: %d in x, %d in y\n", hold_max.x, hold_max.y);
// 	sizes.x = hold_max.x - hold_min.x;
// 	sizes.y = hold_max.y - hold_min.y;
//     ft_printf("this is how big: %d in x, %d in y\n", sizes.x, sizes.y);
// 	return (sizes);
// }

// static t_pair scale(t_pair sizes, t_pair point)
// {
//     t_pair scaled;

//     scaled.x = point.x * (WIDTH / sizes.x);
//     scaled.y = point.y * (HEIGHT / sizes.y);
//     return (scaled);
// }

static void paint_pixel(t_fdf *data, t_pair start, int color)
{
    int pixel;

    if (start.x > WIDTH || start.y > HEIGHT || start.x < 0 || start.y < 0)
        return ;
    pixel = (start.y * data->size_line) + (4 * start.x);
	data->buffer[pixel + 0] = (color) & 0xFF; // red
	data->buffer[pixel + 1] = (color >> 8) & 0xFF; // green
	data->buffer[pixel + 2] = (color >> 16) & 0xFF; // blue
	data->buffer[pixel + 3] = (color >> 24) & 0xFF; // alpha
}

void    draw_line(t_fdf *data, t_pair start, t_pair end)
{
    t_pair delta;
    t_pair sign;
    int err;
    int new_err;

    delta.x = abs(end.x - start.x);
    delta.y = abs(end.y - start.y);
    // these horrible assignnments are because we are not allowed to use ?
    err = ((delta.x > delta.y) * delta.x - (delta.x <= delta.y) * delta.y) / 2; // err = (dx > dy ? dx : -dy) / 2;
    sign.x = (end.x - start.x > 0) - (start.x - end.x > 0); // start.x < end.x ? 1 : -1;
    sign.y = (end.y - start.y > 0) - (start.y - end.y > 0); // start.y < end.y ? 1 : -1;

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
    mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

void	draw_all(t_fdf *data, t_pair *all_points)
{
	int i;
	int j;
	int index;
//    t_pair sizes;
    // t_pair temp;
    // t_pair temp2;

	i = 0;
//	sizes = get_sizes(data, all_points);
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