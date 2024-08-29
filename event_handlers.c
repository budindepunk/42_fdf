#include "fdf.h"

int     mouse_handler(int button, int x, int y, void *param)
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

int     keypress_handler(int keysym, void *param)
{
        t_fdf *data;

        data = (t_fdf *)param;
        if (keysym == XK_Escape)
        {
                mlx_destroy_image(data->mlx, data->image);
                mlx_destroy_window(data->mlx, data->window);
                exit (0);
        }
        // if right arrow - draw_all
        return (0);
}

