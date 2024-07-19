#include "fdf.h"

void	fill_image(t_fdf *data)
{
	int	pixel;
	int	color;
	int	color1 = 0xFFA22E;
	int	color2 = 0xC0C0C0;
	int	x;
	int	y = 0;

	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if ((x > WIDTH/3 && x < (2 * WIDTH/3)) && (y > HEIGHT/3 && y < (2 * HEIGHT/3)))
				color = color1;
			else
				color = color2;
			pixel = (y * data->size_line) + (4 * x);
			data->buffer[pixel + 0] = (color) & 0xFF;
			data->buffer[pixel + 1] = (color >> 8) & 0xFF;
			data->buffer[pixel + 2] = (color >> 16) & 0xFF;
			data->buffer[pixel + 3] = (color >> 24) & 0xFF;
			x++;
		}
		y++;
	}
}

t_fdf	*init(void)
{
	t_fdf	*data;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "hello");
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->buffer = mlx_get_data_addr(data->image, &data->bits_pixel, &data->size_line, &data->endian);

	if (!data->buffer || !data->window || !data->image || !data->mlx)
		return (NULL);
	return (data);
}

int	main(void)
{
	t_fdf	*data;

	data = init();
	fill_image(data);
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	
	mlx_loop(data->mlx);
	return (0);
}
