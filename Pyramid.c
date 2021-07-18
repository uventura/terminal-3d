#include "lib/header3D.c"

int main()
{
	screen scr;
	coord3D pyramid[5], copy[5], center_mass;

	clock_t initial_time;
	double delta_t;

	init(&scr, 40, 20, ' ');

	/* Square */
	pyramid[0] = set_point(0, 0, 0);
	pyramid[1] = set_point(2, 0, 0);
	pyramid[2] = set_point(2, 0, 2);
	pyramid[3] = set_point(0, 0, 2);
	pyramid[4] = set_point(1, 2, 1);

	/* Index Buffer */
	int elements = 16;
	unsigned int ibo[16] = 
	{
		0, 1,
		1, 2,
		2, 3,
		3, 0,
		0, 4,
		1, 4,
		2, 4,
		3, 4
	};

	/* Initial Transformations */
	translate(pyramid, 5, 10, 10, 10);

	center_mass = centerObj(pyramid, 4);
	translate(pyramid, 5, -center_mass.x, -center_mass.y, -center_mass.z);
		rotate(pyramid, 5, 20, 20, 0);
		scale(pyramid, 5, 6, 4, 4);
	translate(pyramid, 5, center_mass.x, center_mass.y, center_mass.z);

	copy_array(pyramid, copy, 5);

	ortographic(pyramid, 5);

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
			translate(pyramid, 5, -center_mass.x, -center_mass.y, -center_mass.z);
				rotate(pyramid, 5, 0, angle, 0);
			translate(pyramid, 5, center_mass.x, center_mass.y, center_mass.z);

			ortographic(pyramid, 5);

			result = build_lines(pyramid, ibo, elements, &size_r);
			ortographic(result, size_r);

			clr_scr(&scr);
				point_to_scr(&scr, result, size_r);
			show_scr(scr);

			copy_array(copy, pyramid, 5);

			angle++;
			initial_time = clock();
		}
	}
}