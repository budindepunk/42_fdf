#include "fdf.h"

typedef struct s_thruple
{
	int		x;
	int		y;
    int     z;
}		t_thruple;

t_pair project(t_thruple vertex)
{
    t_pair flat_vertex;

    flat_vertex.x = (int)((sqrt(3) * (double)vertex.x - sqrt(3) * (double)vertex.z) / sqrt(6));
    flat_vertex.y = (int)((double)(vertex.x + 2 * vertex.y + vertex.z) / sqrt(6));
    return (flat_vertex);
}

void flatten_cube(t_fdf *data)
{
    const t_thruple a = { .x = 0, .y = 0, .z = 0 };
    const t_thruple b = { .x = 10, .y = 0, .z = 0 };
    const t_thruple c = { .x = 10, .y = 10, .z = 0 };
    const t_thruple d = { .x = 0, .y = 10, .z = 0 };
    const t_thruple e = { .x = 0, .y = 0, .z = 10 };
    const t_thruple f = { .x = 10, .y = 0, .z = 10 };
    const t_thruple g = { .x = 10, .y = 10, .z = 10 };
    const t_thruple h = { .x = 0, .y = 10, .z = 10 };
    t_thruple cube[8] = { a, b, c, d, e, f, g, h };
    t_pair flat_cube[8] = {};

    int i = 0;
    t_pair projection = { .x = 0, .y = 0 };
    while(i < 8)
    {
        projection = project(cube[i]);
        projection.x += 8;
        flat_cube[i] = projection;
//        ft_printf("vertex %d\n---------------\n", i);
//        ft_printf("vertex coordinates:\n\tx: %d\n\ty: %d\n\tz: %d\n", cube[i].x, cube[i].y, cube[i].z);
//        ft_printf("projected vertex coordinates:\n\tx: %d\n\ty: %d\n\n", projection.x, projection.y);
        i++;
    }
    draw_line(data, flat_cube[0], flat_cube[1]);
    draw_line(data, flat_cube[1], flat_cube[2]);
    draw_line(data, flat_cube[2], flat_cube[6]);
    draw_line(data, flat_cube[6], flat_cube[7]);
    draw_line(data, flat_cube[7], flat_cube[4]);
    draw_line(data, flat_cube[4], flat_cube[0]);

    draw_line(data, flat_cube[3], flat_cube[1]);
    draw_line(data, flat_cube[3], flat_cube[4]);
    draw_line(data, flat_cube[3], flat_cube[6]);
}