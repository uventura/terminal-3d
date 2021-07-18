#include "lib/header3D.c"

int main()
{
	screen scr;
	coord3D square[4], copy[4], center_mass;

	clock_t initial_time;
	double delta_t;

	init(&scr, 40, 20, '.');

	/* Square */
	square[0] = set_point(0, 0, 0);
	square[1] = set_point(2, 0, 0);
	square[2] = set_point(2, 2, 0);
	square[3] = set_point(0, 2, 0);

	/* Index Buffer */
	int elements = 8;
	unsigned int ibo[8] = 
	{
		0, 1,
		1, 2,
		2, 3,
		3, 0
	};

	/* Initial Transformations */
	translate(square, 4, 10, 10, 10);

	center_mass = centerObj(square, 4);
	translate(square, 4, -center_mass.x, -center_mass.y, -center_mass.z);
		scale(square, 4, 4, 4, 4);
	translate(square, 4, center_mass.x, center_mass.y, center_mass.z);

	copy_array(square, copy, 4);

	ortographic(square, 4);

	/* Resultant Matrix */
	int size_r;
	coord3D *result;

	/*----------*/
	initial_time = clock();
	float angle = 0;

	while(1)
	{
		delta_t = (double)(clock() - initial_time) / CLOCKS_PER_SEC;
		if(delta_t >= 0.01)
		{
			translate(square, 4, -center_mass.x, -center_mass.y, -center_mass.z);
				rotate(square, 4, 0, 0, angle);
			translate(square, 4, center_mass.x, center_mass.y, center_mass.z);

			ortographic(square, 4);

			result = build_lines(square, ibo, elements, &size_r);
			ortographic(result, size_r);

			clr_scr(&scr);
				point_to_scr(&scr, result, size_r);
			show_scr(scr);

			copy_array(copy, square, 4);

			angle++;
			initial_time = clock();
		}
	}
}