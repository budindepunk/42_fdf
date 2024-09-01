#include "fdf.h"

/* write about how i did the cube. 
created thruples for the coordinates in the "real world", then found the equations in wikiepdia isometric projection to "flatten them" into 2D coordinates in porject().
then iterated through all throuples (8), and saved the flattened vertices in an array. then manually decided which ones to join with a line. show the cube*/
/*Then write about main porject. in parse_map() i get useful info like rows and columns, open the file, etc. then in
flatten_map() i create an array of pairs to save coords of all points of the grid. i iterate through them and make each a temporary thruple so i can flatten it and put it in the array.
then in draw_all i take the array of coords. the loop has some conditions in it to draw it efficiently i think.my projection is rotated and idk why, i think its related to my grid point 0,0. the projection seems to want to keep that point at the top left. ill look into it.
/// seems the thing is ok but from the wrong OCTANT. the sample 42 map can look good (screenshot) but its clear its the wrong point of view. next step is figuring out what "inverting and rotating the matrix' is".*/

void flatten_cube(t_fdf *data)
{
	int number = 10;

	const t_thruple a = { .x = 0, .y = 0, .z = 0 };
	const t_thruple b = { .x = number, .y = 0, .z = 0 };
	const t_thruple c = { .x = number, .y = number, .z = 0 };
	const t_thruple d = { .x = 0, .y = number, .z = 0 };
	const t_thruple e = { .x = 0, .y = 0, .z = number };
	const t_thruple f = { .x = number, .y = 0, .z = number };
	const t_thruple g = { .x = number, .y = number, .z = number };
	const t_thruple h = { .x = 0, .y = number, .z = number };
	t_thruple cube[8] = { a, b, c, d, e, f, g, h };
	t_pair flat_cube[8] = {};

	int i = 0;
	t_pair projection = { .x = 0, .y = 0 };
	while(i < 8)
	{
		projection = project(cube[i]);
		projection.x += 200;
		projection.y += 100;
		flat_cube[i] = projection;
//		ft_printf("vertex %d\n---------------\n", i);
//		ft_printf("vertex coordinates:\n\tx: %d\n\ty: %d\n\tz: %d\n", cube[i].x, cube[i].y, cube[i].z);
//		ft_printf("projected vertex coordinates:\n\tx: %d\n\ty: %d\n\n", projection.x, projection.y);
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

/*
0 0 0 0 0 0 0 0 0 0 --> x
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
|
y
*/