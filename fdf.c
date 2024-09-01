/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::   	  */
/*   fdf.c											  :+:	  :+:	:+:   	  */
/*													+:+ +:+		 +:+	 	  */
/*   By: csilva-r <csilva-r@student.42berlin.de>	+#+  +:+	   +#+		  */
/*												+#+#+#+#+#+   +#+		   	  */
/*   Created: 2024/09/01 14:42:43 by csilva-r		  #+#	#+#			 	  */
/*   Updated: 2024/09/01 14:42:45 by csilva-r		 ###   ########.fr	   	  */
/*																			  */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*init(void)
{
	t_fdf	*data;
	int		*bitpix;
	int		*sizel;

	data = (t_fdf *)malloc(sizeof(t_fdf));
	data->mlx = mlx_init();
	bitpix = &data->bits_pixel;
	sizel = &data->size_line;
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fdf");
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->buffer = mlx_get_data_addr(data->image, bitpix, sizel, &data->endian);
	if (!data->buffer || !data->window || !data->image || !data->mlx)
		return (NULL);
	return (data);
}

int	check_arguments(int argc, char **argv)
{
	int		l;
	char	*f;

	if (argc != 2)
	{
		ft_putendl_fd("Run ./fdf <file.fdf>", 2);
		return (FALSE);
	}
	f = argv[1];
	l = ft_strlen(f);
	if (f[--l] != 'f' || f[--l] != 'd' || f[--l] != 'f' || f[--l] != '.')
	{
		ft_putendl_fd("Use a .fdf file.", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_fdf	*data;
	t_pair	*all_points;

	if (!check_arguments(argc, argv))
		return (1);
	data = init();
	all_points = parse_map(data, argv[1]);
	if (!all_points)
		return (1);
	mlx_key_hook(data->window, &keypress_handler, data);
	mlx_mouse_hook(data->window, &mouse_handler, data);
	mlx_hook(data->window, DestroyNotify, None, &close_handler, data);
	draw_all(data, all_points);
	mlx_loop(data->mlx);
	return (0);
}
