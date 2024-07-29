#include "fdf.h"
#include <X11/keysym.h>

void	fill_center(t_fdf *data)
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
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
}

void	fill_center2(t_fdf *data)
{
	int	pixel;
	int	color;
	int	color2 = 0xFFA22E;
	int	color1 = 0xC0C0C0;
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
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
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

int	keypress_handler(int keysym, void *param)
{
	t_fdf *data;

	data = (t_fdf *)param;
	if (keysym == XK_Escape)
	{
		ft_printf("pressed key %d\n", keysym);
		mlx_destroy_image(data->mlx, data->image);
		mlx_destroy_window(data->mlx, data->window);
		exit (0);
	}
	else if (keysym == XK_Return)
		ft_printf(":P\n");
	else
	{
		ft_printf("pressed key %d\n", keysym);
		fill_center2(data);
		// mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	}
	return (0);
}

int	mouse_handler(int button, int x, int y, void *param)
{
	if (!param)
		return (0);
	if (button == 1)
		ft_printf("left ");
	else if (button == 2)
		ft_printf("middle ");
	else if (button == 3)
		ft_printf("right ");
	ft_printf("click at (%d, %d)\n", x, y);
	return (0);
}

/*
int	handle_nothing(t_fdf *data)
{
	if (data)
		return (0);
	return (0);
}
*/

int	main(void)
{
	t_fdf	*data;

	data = init();
	fill_center(data);

	//mlx_loop_hook(data->mlx, &handle_nothing, &data);
	mlx_key_hook(data->window, &keypress_handler, data);
	mlx_mouse_hook(data->window, &mouse_handler, data);
	
	mlx_loop(data->mlx);

	//mlx_destroy_display(data->mlx);	// removing changed nothing
	return (0);
}
