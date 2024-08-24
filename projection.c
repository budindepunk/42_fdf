#include "fdf.h"

static int get_flat_x(t_thruple vertex)
{
    double flat_x;

    flat_x = sqrt(3) * (double)vertex.x;
    flat_x -= sqrt(3) * (double)vertex.y;
    flat_x /= sqrt(6);
    return ((int)flat_x);
}

static int get_flat_y(t_thruple vertex)
{
    double flat_y;

    flat_y = sqrt(2) * (double)vertex.x;
    flat_y += sqrt(2) * (double)vertex.y;
    flat_y -= sqrt(2) * (double)vertex.z;
    flat_y /= sqrt(6);
    return ((int)flat_y);
}

t_pair project(t_thruple vertex)
{
    t_pair flat_vertex;

    //flat_vertex.x = (int)((sqrt(3) * (double)vertex.x - sqrt(3) * (double)vertex.y) / sqrt(6)) + 300;
    //flat_vertex.y = (int)((sqrt(2) * (double)vertex.x + sqrt(2) * (double)vertex.y - sqrt(2) * (double)vertex.z) / sqrt(6));    
    flat_vertex.x = get_flat_x(vertex);
    flat_vertex.y = get_flat_y(vertex);

    return (flat_vertex);
}