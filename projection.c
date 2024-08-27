#include "fdf.h"

static int get_flat_x(t_thruple vertex, t_fdf *data)
{
    double flat_x;

    if (!data)
        return (1);
    flat_x = sqrt(3) * (double)vertex.x;
    flat_x -= sqrt(3) * (double)vertex.y;
    flat_x /= sqrt(6);
    //flat_x *= (WIDTH / data->columns);
    return ((int)flat_x);
}

static int get_flat_y(t_thruple vertex, t_fdf *data)
{
    double flat_y;

    if (!data)
        return (1);
    flat_y = sqrt(2) * (double)vertex.x;
    flat_y += sqrt(2) * (double)vertex.y;
    flat_y -= sqrt(2) * (double)vertex.z;
    flat_y /= sqrt(6);
    //flat_y *= (HEIGHT / data->rows);
    return ((int)flat_y);
}

t_pair project(t_thruple vertex, t_fdf *data)
{
    t_pair flat_vertex;
    //int offset;

    //offset = WIDTH * ((double)data->rows / (double)data->columns / 2);
    flat_vertex.x = get_flat_x(vertex, data);
    flat_vertex.y = get_flat_y(vertex, data);

    return (flat_vertex);
}