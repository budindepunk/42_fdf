#include "fdf.h"

t_fdf   *init(void)
{
        t_fdf   *data;

        data = (t_fdf *)malloc(sizeof(t_fdf));
        data->mlx = mlx_init();
        data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "soquicoqui futbol club");
        data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
        data->buffer = mlx_get_data_addr(data->image, &data->bits_pixel, &data->size_line, &data->endian);

        if (!data->buffer || !data->window || !data->image || !data->mlx)
                return (NULL);
        return (data);
}

int	check_arguments(int argc, char **argv)
{
	int	l;
	char	*f;
	if (argc != 2)
	{
		ft_printf("Run ./fdf <file.fdf>\n");
		return (FALSE);
	}
	f = argv[1];
        l = ft_strlen(f);
        if (f[--l] != 'f' || f[--l] != 'd' || f[--l] != 'f' || f[--l] != '.')
	{
		ft_printf("Use a .fdf file.\n");	
               	return (FALSE);
	}
        return (TRUE);
}

int     main(int argc, char **argv)
{
        t_fdf   *data;
        t_pair  *all_points;

	if (!check_arguments(argc, argv))
		return (1);
        data = init();
        all_points = parse_map(data, argv[1]);

        mlx_key_hook(data->window, &keypress_handler, data);
        mlx_mouse_hook(data->window, &mouse_handler, data);

        draw_all(data, all_points); 

        mlx_loop(data->mlx);
        mlx_destroy_display(data->mlx);	

        return (0);
}

