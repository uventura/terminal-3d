#include "lib/header3D.c"

int main()
{
	screen scr;
	coord3D cube[8], copy[8], center_mass;
	float angle_y = 0;

	init(&scr, 40, 40, ' ');

	/* Front */
	cube[0] = set_point(0, 0, 0);
	cube[1] = set_point(2, 0, 0);
	cube[2] = set_point(2, 3, 0);
	cube[3] = set_point(0, 3, 0);
	/* Back */
	cube[4] = set_point(0, 0, 4);
	cube[5] = set_point(2, 0, 4);
	cube[6] = set_point(2, 3, 4);
	cube[7] = set_point(0, 3, 4);

	/* Index Buffer */
	unsigned int ibo[24] = {
		0, 1,
		1, 2,
		2, 3,
		3, 0,
		0, 4,
		4, 5,
		5, 6,
		6, 7,
		7, 4,
		1, 5,
		2, 6,
		7, 3
	};

	/* Initial Transformations */
	translate(cube, 8, 10, 10, 10);

	center_mass = centerObj(cube, 8);

	translate(cube, 8, -center_mass.x, -center_mass.y, -center_mass.z);
		scale(cube, 8, 6, 3, 3);
		rotate(cube, 8, 20, 0, 0);
	translate(cube, 8, center_mass.x, center_mass.y, center_mass.z);

	copy_array(cube, copy, 8);

	ortographic(cube, 8);

	/* Resultant Matrix */
		int size_r;
		coord3D *result;
	/* ---------------- */

	clock_t ti = clock();
	double delta_t;

	while(1)
	{
		delta_t = (double)(clock() - ti) / CLOCKS_PER_SEC;
		if(delta_t >= 0.01)
		{
			translate(cube, 8, -center_mass.x, -center_mass.y, -center_mass.z);
				rotate(cube, 8, 0, angle_y, 0);
			translate(cube, 8, center_mass.x, center_mass.y, center_mass.z);

			ortographic(cube, 8);

			result = build_lines(cube, ibo, 24, &size_r);
			ortographic(result, size_r);

			clr_scr(&scr);
				point_to_scr(&scr, result, size_r);
			show_scr(scr);

			copy_array(copy, cube, 8);

			angle_y++;
			ti = clock();
		}
	}
}