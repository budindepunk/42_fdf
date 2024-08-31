#include "fdf.h"

static int get_offset(int size_x, int min_x, int total)
{
    int desired;
    int offset;

    desired = (total - size_x) / 2;
    offset = desired - min_x;
    return (offset);
}

t_pair center_offsets(t_fdf *data, t_pair *all_points)
{
	t_pair sizes;
	t_pair hold_min;
	t_pair hold_max;
    t_pair offsets;
	int i;

	hold_min.x = INT_MAX;
	hold_min.y = INT_MAX;
	hold_max.x = INT_MIN;
	hold_max.y = INT_MIN;
	i = 0;
	while (i < (data->rows * data->columns))
	{
		if (all_points[i].x < hold_min.x)
			hold_min.x = all_points[i].x;
		if (all_points[i].x > hold_max.x)
			hold_max.x = all_points[i].x;
		if (all_points[i].y < hold_min.y)
			hold_min.y = all_points[i].y;
		if (all_points[i].y > hold_max.y)
			hold_max.y = all_points[i].y;
		i++;
	}
	sizes.x = hold_max.x - hold_min.x;
	sizes.y = hold_max.y - hold_min.y;
    offsets.x = get_offset(sizes.x, hold_min.x, WIDTH);
    offsets.y = get_offset(sizes.y, hold_min.y, HEIGHT);
	return (offsets);
}


t_pair translate(t_pair offsets, t_pair point)
{
    t_pair offgeset;

    offgeset.x = point.x + offsets.x;
    offgeset.y = point.y + offsets.y;
    return (offgeset);
}

void    translate_all(t_pair offset, t_pair *all_points, t_fdf *data)
{
    int i;

    i = 0;
    while (i < (data->rows * data->columns))
    {
        all_points[i] = translate(offset, all_points[i]);
        i++;
    }
}